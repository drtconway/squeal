#ifndef SQUEAL_UTIL_META_GRAMMAR_HPP
#define SQUEAL_UTIL_META_GRAMMAR_HPP

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/icu/utf8.hpp>
#include <deque>
#include <variant>

namespace squeal
{
    namespace meta_grammar
    {
        namespace pegtl = tao::pegtl;

        namespace detail
        {
            template <typename Separator, typename... Rules>
            struct interleaved;

            template <typename Separator, typename Rule0, typename... RulesRest>
            struct interleaved<Separator, Rule0, RulesRest...>
                : pegtl::seq<Separator, Rule0, interleaved<Separator, RulesRest...>> {};

            template <typename Separator, typename Rule0>
            struct interleaved<Separator, Rule0>
                : pegtl::seq<Separator, Rule0> {};

        }
        // namespace detail

        struct sep : pegtl::star<pegtl::ascii::space> {};

        template<typename... Rules>
        using seq = detail::interleaved<sep, Rules...>;

        template<typename... Rules>
        using star = pegtl::star<seq<Rules...>>;

        template<typename... Rules>
        using opt = pegtl::opt<seq<Rules...>>;

        struct langle : pegtl::ascii::one<'<'> {};
        struct rangle : pegtl::ascii::one<'>'> {};

        struct lbrac : pegtl::ascii::one<'['> {};
        struct rbrac : pegtl::ascii::one<']'> {};

        struct lbrace : pegtl::ascii::one<'{'> {};
        struct rbrace : pegtl::ascii::one<'}'> {};

        struct lparen : pegtl::ascii::one<'('> {};
        struct rparen : pegtl::ascii::one<')'> {};

        struct bar : pegtl::ascii::one<'|'> {};

        struct dash : pegtl::ascii::one<'-'> {};

        struct assigns : pegtl::ascii::string<':', ':', '='> {};

        struct dots : pegtl::ascii::string<'.', '.', '.'> {};

        struct word : pegtl::plus<pegtl::sor<pegtl::alnum, pegtl::ascii::one<'_', '-'>>> {};

        struct name_char : pegtl::seq<pegtl::not_at<rangle>, pegtl::ascii::any> {};

        struct name : pegtl::seq<langle, pegtl::plus<name_char>, rangle> {};

        struct single : pegtl::seq<
                            pegtl::sor<
                                pegtl::ascii::string<'|', '|'>,
                                pegtl::ascii::string<'-', '>'>,
                                pegtl::ascii::any>,
                            pegtl::eof> {};

        struct special : pegtl::seq<pegtl::ascii::string<'!', '!'>, pegtl::star<pegtl::ascii::any>, pegtl::eof> {};

        struct disj;

        struct brac : seq<lbrac, disj, rbrac> {};

        struct brace : seq<lbrace, disj, rbrace> {};

        struct simple_escape_sequence : pegtl::utf8::one<')', '\\', '-'> {};

        struct escape_sequence : simple_escape_sequence {};

        struct escaped_rchar : pegtl::if_must<pegtl::utf8::one<'\\'>, escape_sequence> {};

        struct unescaped_rchar : pegtl::utf8::not_one<'\\', ')', '-'> {};

        struct rchar : pegtl::sor<escaped_rchar, unescaped_rchar> {};

        struct crang_range : pegtl::seq<dash, rchar> {};

        struct crang_single : rchar {};

        struct crangs_cont : pegtl::sor<crang_range, crang_single> {};

        struct crangs : pegtl::seq<rchar, pegtl::star<crangs_cont>> {};

        struct crang : pegtl::seq<lparen, crangs, rparen> {};

        struct atom : pegtl::sor<name, word, brac, brace, crang> {};

        struct conj_cont;

        struct dots_conj_cont : seq<dots, opt<conj_cont>> {};
        struct atom_conj_cont : seq<atom, opt<conj_cont>> {};

        struct conj_cont : pegtl::sor<dots_conj_cont, atom_conj_cont> {};

        struct conj : seq<atom, opt<conj_cont>> {};

        struct disj_part : seq<bar, conj> {};

        struct disj : seq<conj, pegtl::star<disj_part>> {};

        struct expression : pegtl::sor<disj, single, special> {};

        struct definition
            : seq<name, assigns, expression> {};

        struct node
        {
            virtual ~node() {}
            virtual std::string dump() { return std::string("*"); }
        };
        using node_ptr = std::shared_ptr<node>;

        template<typename Rule>
        struct build_ast : tao::pegtl::nothing<Rule> {};

        struct state
        {
            std::vector<node_ptr> nodes;

            void dump(std::ostream& p_out)
            {
                int i = 0;
                for (auto itr = nodes.rbegin(); itr != nodes.rend(); ++itr, ++i)
                {
                    p_out << i << '\t' << (*itr)->dump() << std::endl;
                }
            }
        };

        struct name_node : node
        {
            std::string name;

            name_node(const std::string& p_name)
                : name(p_name)
            {
            }
            virtual std::string dump() { return name; }
        };
        using name_node_ptr = std::shared_ptr<name_node>;

        struct word_node : node
        {
            std::string word;

            word_node(const std::string& p_word)
                : word(p_word)
            {
            }
            virtual std::string dump() { return word; }
        };
        using word_node_ptr = std::shared_ptr<word_node>;

        struct special_node : node
        {
            std::string word;

            special_node(const std::string& p_word)
                : word(p_word)
            {
            }
            virtual std::string dump() { return word; }
        };
        using special_node_ptr = std::shared_ptr<special_node>;

        struct opt_node : node
        {
            node_ptr child;

            opt_node(const node_ptr& p_child)
                : child(p_child)
            {}
            virtual std::string dump() { return std::string("(") + child->dump() + std::string(")?"); }
        };
        using opt_node_ptr = std::shared_ptr<opt_node>;

        struct plus_node : node
        {
            node_ptr child;

            plus_node(const node_ptr& p_child)
                : child(p_child)
            {}
            virtual std::string dump() { return std::string("(") + child->dump() + std::string(")+"); }
        };
        using plus_node_ptr = std::shared_ptr<plus_node>;

        struct star_node : node
        {
            node_ptr child;

            star_node(const node_ptr& p_child)
                : child(p_child)
            {}
            virtual std::string dump() { return std::string("(") + child->dump() + std::string(")*"); }
        };
        using star_node_ptr = std::shared_ptr<star_node>;

        struct crang_node : node
        {
            using single = std::string;
            using range = std::pair<std::string,std::string>;
            using single_or_range = std::variant<single,range>;

            std::vector<single_or_range> parts;

            virtual std::string dump()
            {
                std::string s;
                s += "(";
                for (size_t i = 0; i < parts.size(); ++i)
                {
                    switch (parts[i].index())
                    {
                        case 0:
                        {
                            s += std::get<0>(parts[i]);
                            break;
                        }
                        case 1:
                        {
                            s += std::get<1>(parts[i]).first;
                            s += "-";
                            s += std::get<1>(parts[i]).second;
                            break;
                        }
                    }
                }
                s += ")";
                return s;
            }
        };
        using crang_node_ptr = std::shared_ptr<crang_node>;

        struct crang_part_node : node
        {
            crang_node::single_or_range part;

            crang_part_node(const std::string& p_ch)
                : part(p_ch)
            {}

            crang_part_node(const std::string& p_fst, const std::string& p_lst)
                : part(crang_node::range(p_fst, p_lst))
            {}

            virtual std::string dump()
            {
                std::string s;
                s += "<<";
                switch (part.index())
                {
                    case 0:
                    {
                        s += std::get<0>(part);
                        break;
                    }
                    case 1:
                    {
                        s += std::get<1>(part).first;
                        s += "-";
                        s += std::get<1>(part).second;
                        break;
                    }
                }
                s += ">>";
                return s;
            }
        };
        using crang_part_node_ptr = std::shared_ptr<crang_part_node>;

        struct conj_node : node
        {
            std::deque<node_ptr> nodes;
            virtual std::string dump() {
                std::string s;
                s += "(";
                for (size_t i = 0; i < nodes.size(); ++i)
                {
                    if (i > 0)
                    {
                        s += " ";
                    }
                    s += nodes[i]->dump();
                }
                s += ")";
                return s;
            }
        };
        using conj_node_ptr = std::shared_ptr<conj_node>;

        struct disj_node : node
        {
            std::vector<node_ptr> nodes;
            virtual std::string dump() {
                std::string s;
                s += "{";
                for (size_t i = 0; i < nodes.size(); ++i)
                {
                    if (i > 0)
                    {
                        s += " | ";
                    }
                    s += nodes[i]->dump();
                }
                s += "}";
                return s;
            }
        };
        using disj_node_ptr = std::shared_ptr<disj_node>;

        struct defn_node : node
        {
            std::string name;
            node_ptr defn;

            defn_node(const std::string& p_name, node_ptr p_defn)
                : name(p_name), defn(p_defn)
            {
            }
        };
        using defn_node_ptr = std::shared_ptr<defn_node>;

        template<>
        struct build_ast<name>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                node_ptr p(new name_node(p_in.string()));
                p_state.nodes.push_back(p);
            }
        };

        template<>
        struct build_ast<word>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                node_ptr p(new word_node(p_in.string()));
                p_state.nodes.push_back(p);
            }
        };

        template<>
        struct build_ast<single>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                node_ptr p(new word_node(p_in.string()));
                p_state.nodes.push_back(p);
            }
        };

        template<>
        struct build_ast<special>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                node_ptr p(new special_node(p_in.string()));
                p_state.nodes.push_back(p);
            }
        };

        template<>
        struct build_ast<brac>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                node_ptr p = p_state.nodes.back();
                p_state.nodes.pop_back();
                plus_node_ptr q = std::dynamic_pointer_cast<plus_node>(p);
                if (q)
                {
                    node_ptr r(new star_node(q->child));
                    p_state.nodes.push_back(r);
                }
                else
                {
                    node_ptr r(new opt_node(p));
                    p_state.nodes.push_back(r);
                }
            }
        };

        template<>
        struct build_ast<simple_escape_sequence>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                node_ptr p(new crang_part_node(p_in.string()));
                p_state.nodes.push_back(p);
            }
        };

        template<>
        struct build_ast<unescaped_rchar>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                node_ptr p(new crang_part_node(p_in.string()));
                p_state.nodes.push_back(p);
            }
        };

        template<>
        struct build_ast<crang_range>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                node_ptr q0 = p_state.nodes.back();
                p_state.nodes.pop_back();
                crang_part_node_ptr q = std::dynamic_pointer_cast<crang_part_node>(q0);
                node_ptr p0 = p_state.nodes.back();
                p_state.nodes.pop_back();
                crang_part_node_ptr p = std::dynamic_pointer_cast<crang_part_node>(p0);

                node_ptr r(new crang_part_node(std::get<0>(p->part), std::get<0>(q->part)));
                p_state.nodes.push_back(r);
            }
        };

        template<>
        struct build_ast<crang>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                crang_node_ptr r(new crang_node);
                while (p_state.nodes.size()
                       && std::dynamic_pointer_cast<crang_part_node>(p_state.nodes.back()))
                {
                    node_ptr p0 = p_state.nodes.back();
                    p_state.nodes.pop_back();
                    crang_part_node_ptr p = std::dynamic_pointer_cast<crang_part_node>(p0);
                    r->parts.push_back(p->part);
                }
                p_state.nodes.push_back(std::static_pointer_cast<node>(r));
            }
        };

        template<>
        struct build_ast<dots_conj_cont>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                node_ptr p = p_state.nodes.back();
                p_state.nodes.pop_back();
                node_ptr q(new plus_node(p));
                p_state.nodes.push_back(q);
            }
        };

        template<>
        struct build_ast<atom_conj_cont>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                node_ptr p = p_state.nodes.back();
                p_state.nodes.pop_back();
                node_ptr q = p_state.nodes.back();
                p_state.nodes.pop_back();

                conj_node_ptr c = std::dynamic_pointer_cast<conj_node>(p);
                if (c)
                {
                    c->nodes.push_front(q);
                }
                else
                {
                    c = conj_node_ptr(new conj_node);
                    c->nodes.push_back(q);
                    c->nodes.push_back(p);
                }
                p_state.nodes.push_back(std::static_pointer_cast<node>(c));
            }
        };

        template<>
        struct build_ast<disj_part>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                node_ptr p = p_state.nodes.back();
                p_state.nodes.pop_back();
                node_ptr q = p_state.nodes.back();
                p_state.nodes.pop_back();

                disj_node_ptr c = std::dynamic_pointer_cast<disj_node>(q);
                if (c)
                {
                    c->nodes.push_back(p);
                }
                else
                {
                    c = disj_node_ptr(new disj_node);
                    c->nodes.push_back(q);
                    c->nodes.push_back(p);
                }
                p_state.nodes.push_back(std::static_pointer_cast<node>(c));
            }
        };

        template<>
        struct build_ast<definition>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                node_ptr p = p_state.nodes.back();
                p_state.nodes.pop_back();
                node_ptr q = p_state.nodes.back();
                p_state.nodes.pop_back();
                name_node_ptr n = std::dynamic_pointer_cast<name_node>(q);
                node_ptr r(new defn_node(n->name, p));
                p_state.nodes.push_back(r);
            }
        };
    }
    // namespace meta_grammar
}
// namespace squeal

#endif // SQUEAL_UTIL_META_GRAMMAR_HPP
