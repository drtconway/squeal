#ifndef SQUEAL_UTIL_META_GRAMMAR_HPP
#define SQUEAL_UTIL_META_GRAMMAR_HPP

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/icu/utf8.hpp>

#include <deque>
#include <set>
#include <variant>

#include <boost/format.hpp>

#ifndef SQUEAL_UTIL_UTF8_HPP
#include "squeal/util/utf8.hpp"
#endif

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


        //
        // Here's the actual grammar:
        //

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
        struct colon : pegtl::ascii::one<':'> {};

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

        struct hexit : pegtl::utf8::ranges<'0', '9', 'a', 'f', 'A', 'F'> {};

        struct special : pegtl::seq<pegtl::ascii::string<'!', '!'>, pegtl::star<pegtl::ascii::any>, pegtl::eof> {};

        struct disj;

        struct brac : seq<lbrac, disj, rbrac> {};

        struct brace : seq<lbrace, disj, rbrace> {};

        struct simple_escape_sequence : pegtl::utf8::one<')', '\\', '-', ':'> {};

        struct unicode_quad : pegtl::seq<hexit, hexit, hexit, hexit> {};

        struct unicode_oct : pegtl::seq<hexit, hexit, hexit, hexit, hexit, hexit, hexit, hexit> {};

        struct escape_sequence
            : pegtl::sor<
                simple_escape_sequence,
                pegtl::seq<pegtl::utf8::one<'u'>, unicode_quad>,
                pegtl::seq<pegtl::utf8::one<'U'>, unicode_oct>
            >
        {};

        struct escaped_rchar : pegtl::if_must<pegtl::utf8::one<'\\'>, escape_sequence> {};

        struct unescaped_rchar : pegtl::utf8::not_one<'\\', ')', '-', ':'> {};

        struct rchar : pegtl::sor<escaped_rchar, unescaped_rchar> {};

        struct crang_range : pegtl::seq<dash, rchar> {};

        struct crang_single : rchar {};

        struct crangs_cont : pegtl::sor<crang_range, crang_single> {};

        struct crangs : pegtl::seq<rchar, pegtl::star<crangs_cont>> {};

        struct crang : pegtl::seq<lparen, crangs, rparen> {};

        struct cclass_name
            : pegtl::plus<
                pegtl::sor<pegtl::ascii::alnum, pegtl::ascii::one<'_'>>
            >
        {};

        struct cclass : pegtl::seq<lparen, colon, cclass_name, colon, rparen> {};

        struct atom : pegtl::sor<name, word, brac, brace, cclass, crang> {};

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


        //
        // Syntax tree nodes and parser state
        //

        struct cpp
        {
            static std::string esc_name(const std::string& p_str)
            {
                std::string s(p_str.begin()+1, p_str.end()-1);
                std::replace(s.begin(), s.end(), ' ', '_');
                std::replace(s.begin(), s.end(), '-', '_');
                std::replace(s.begin(), s.end(), '/', '_');
                return s;
            }

            static std::string esc_char(char p_ch)
            {
                std::string s;
                switch (p_ch)
                {
                    case '\'':
                    case '\\':
                        s.push_back('\\');
                }
                s.push_back(p_ch);
                return s;
            }

            static std::string esc_word(const std::string& p_word)
            {
                std::string s(p_word);
                if (p_word == "TRUE" || p_word == "FALSE" || p_word == "NULL")
                {
                    s.push_back('_');
                }
                return s;
            }

        };

        struct context
        {
            const std::set<std::string> keywords;

            std::ostream& out;
            int ind;

            void indent()
            {
                for (int i = 0; i < ind; ++i)
                {
                    out << "    ";
                }
            }
        };

        struct scope
        {
            scope(context& p_ctxt)
                : ctxt(p_ctxt)
            {
                ctxt.ind += 1;
            }

            ~scope()
            {
                ctxt.ind -= 1;
            }

            context& ctxt;
        };

        struct node
        {
            virtual ~node() {}

            virtual void render(context& p_ctxt) const = 0;

            // For debugging
            //
            virtual std::string dump() const = 0;
        };
        using node_ptr = std::shared_ptr<node>;

        struct state
        {
            std::vector<node_ptr> nodes;

            void dump(std::ostream& p_out) const
            {
                int i = 0;
                for (auto itr = nodes.rbegin(); itr != nodes.rend(); ++itr, ++i)
                {
                    p_out << i << '\t' << (*itr)->dump() << std::endl;
                }
            }
        };

        template<typename Rule>
        struct build_ast : tao::pegtl::nothing<Rule> {};

        struct name_node : node
        {
            std::string name;

            name_node(const std::string& p_name)
                : name(p_name)
            {
            }

            virtual void render(context& p_ctxt) const
            {
                p_ctxt.indent();
                p_ctxt.out << cpp::esc_name(name);
            }

            virtual std::string dump() const { return name; }
        };
        using name_node_ptr = std::shared_ptr<name_node>;

        struct word_node : node
        {
            std::string word;

            word_node(const std::string& p_word)
                : word(p_word)
            {
            }

            virtual void render(context& p_ctxt) const
            {
                if (p_ctxt.keywords.count(word))
                {
                    p_ctxt.indent();
                    p_ctxt.out << "keywords::" << cpp::esc_word(word);
                    return;
                }

                if (word.size() == 1)
                {
                    p_ctxt.indent();
                    p_ctxt.out << "tao::pegt::utf8::one<'" << cpp::esc_char(word[0]) << "'>";
                    return;
                }

                p_ctxt.out << "tao::pegt::utf8::string<";
                for (auto itr = word.begin(); itr != word.end(); ++itr)
                {
                    if (itr != word.begin())
                    {
                        p_ctxt.out << ",";
                    }
                    p_ctxt.out << "'" << cpp::esc_char(*itr) << "'";
                }
                p_ctxt.out << ">";
            }

            virtual std::string dump() const { return word; }
        };
        using word_node_ptr = std::shared_ptr<word_node>;

        struct special_node : node
        {
            std::string word;

            special_node(const std::string& p_word)
                : word(p_word)
            {
            }

            virtual void render(context& p_ctxt) const
            {
                p_ctxt.indent();
                p_ctxt.out << word;
            }

            virtual std::string dump() const { return word; }
        };
        using special_node_ptr = std::shared_ptr<special_node>;

        struct opt_node : node
        {
            node_ptr child;

            opt_node(const node_ptr& p_child)
                : child(p_child)
            {}

            virtual void render(context& p_ctxt) const
            {
                p_ctxt.indent();
                p_ctxt.out << "tao::pegtl::opt<\n";
                {
                    scope S(p_ctxt);
                    child->render(p_ctxt);
                }
                p_ctxt.out << ">";
            }

            virtual std::string dump() const { return std::string("(") + child->dump() + std::string(")?"); }
        };
        using opt_node_ptr = std::shared_ptr<opt_node>;

        struct plus_node : node
        {
            node_ptr child;

            plus_node(const node_ptr& p_child)
                : child(p_child)
            {}

            virtual void render(context& p_ctxt) const
            {
                p_ctxt.indent();
                p_ctxt.out << "tao::pegtl::plus<\n";
                {
                    scope S(p_ctxt);
                    child->render(p_ctxt);
                }
                p_ctxt.out << ">";
            }

            virtual std::string dump() const { return std::string("(") + child->dump() + std::string(")+"); }
        };
        using plus_node_ptr = std::shared_ptr<plus_node>;

        struct star_node : node
        {
            node_ptr child;

            star_node(const node_ptr& p_child)
                : child(p_child)
            {}

            virtual void render(context& p_ctxt) const
            {
                p_ctxt.indent();
                p_ctxt.out << "tao::pegtl::star<\n";
                {
                    scope S(p_ctxt);
                    child->render(p_ctxt);
                }
                p_ctxt.out << ">";
            }

            virtual std::string dump() const { return std::string("(") + child->dump() + std::string(")*"); }
        };
        using star_node_ptr = std::shared_ptr<star_node>;

        struct crang_node : node
        {
            using single = char32_t;
            using range = std::pair<char32_t,char32_t>;
            using single_or_range = std::variant<single,range>;

            std::vector<single_or_range> parts;

            virtual void render(context& p_ctxt) const
            {
                std::vector<char32_t> singles;
                std::vector<range> ranges;
                for (size_t i = 0; i < parts.size(); ++i)
                {
                    switch (parts[i].index())
                    {
                        case 0:
                        {
                            singles.push_back(std::get<0>(parts[i]));
                            break;
                        }
                        case 1:
                        {
                            ranges.push_back(std::get<1>(parts[i]));
                            break;
                        }
                    }
                }
                //std::sort(singles.begin(), singles.end());
                //std::sort(ranges.begin(), ranges.end());
                if (singles.size() > 0 && ranges.size() == 0)
                {
                    renderSingles(p_ctxt, singles);
                }
                else if (singles.size() == 0 && ranges.size() > 0)
                {
                    renderRanges(p_ctxt, ranges);
                }
                else
                {
                    p_ctxt.indent();
                    p_ctxt.out << "pegtl::utf8::one<";
                    {
                        scope S(p_ctxt);
                        renderSingles(p_ctxt, singles);
                        p_ctxt.out << ",\n";
                        renderRanges(p_ctxt, ranges);
                        p_ctxt.out << "\n";
                    }
                    p_ctxt.out << ">";
                }
            }

            static void renderSingles(context& p_ctxt, const std::vector<char32_t>& p_singles)
            {
                using namespace boost;

                p_ctxt.indent();
                p_ctxt.out << "pegtl::utf8::one<";
                for (size_t i = 0; i < p_singles.size(); ++i)
                {
                    if (i > 0)
                    {
                        p_ctxt.out << ", ";
                    }
                    p_ctxt.out << str(format("0x%04x") % p_singles[i]);
                }
                p_ctxt.out << ">";
            }

            static void renderRanges(context& p_ctxt, const std::vector<range>& p_ranges)
            {
                using namespace boost;

                p_ctxt.indent();
                p_ctxt.out << "pegtl::utf8::ranges<";
                for (size_t i = 0; i < p_ranges.size(); ++i)
                {
                    if (i > 0)
                    {
                        p_ctxt.out << ", ";
                    }
                    p_ctxt.out << str(format("0x%04x, 0x%04x") % p_ranges[i].first % p_ranges[i].second);
                }
                p_ctxt.out << ">";
            }

            virtual std::string dump() const
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

            crang_part_node(char32_t p_ch)
                : part(p_ch)
            {}

            crang_part_node(char32_t p_fst, char32_t p_lst)
                : part(crang_node::range(p_fst, p_lst))
            {}

            virtual void render(context& p_ctxt) const
            {
                throw std::logic_error("cannot render partial character ranges");
            }

            virtual std::string dump() const
            {
                std::string s;
                s += "<<";
                switch (part.index())
                {
                    case 0:
                    {
                        s += std::to_string(std::get<0>(part));
                        break;
                    }
                    case 1:
                    {
                        s += std::to_string(std::get<1>(part).first);
                        s += "-";
                        s += std::to_string(std::get<1>(part).second);
                        break;
                    }
                }
                s += ">>";
                return s;
            }
        };
        using crang_part_node_ptr = std::shared_ptr<crang_part_node>;

        struct cclass_node : node
        {
            std::string name;

            cclass_node(const std::string& p_name)
                : name(p_name)
            {}

            virtual void render(context& p_ctxt) const
            {
                p_ctxt.indent();
                p_ctxt.out << "pegtl::utf8::icu::" << name;
            }

            virtual std::string dump() const
            {
                std::string s;
                s += "(:";
                s += name;
                s += ":)";
                return s;
            }
        };
        using cclass_node_ptr = std::shared_ptr<cclass_node>;

        struct conj_node : node
        {
            std::deque<node_ptr> nodes;

            virtual void render(context& p_ctxt) const
            {
                p_ctxt.indent();
                p_ctxt.out << "pegtl::seq<\n";
                for (auto itr = nodes.begin(); itr != nodes.end(); ++itr)
                {
                    scope S(p_ctxt);
                    if (itr != nodes.begin())
                    {
                        p_ctxt.out << ",\n";
                    }
                    (*itr)->render(p_ctxt);
                }
                p_ctxt.out << "\n";
                p_ctxt.indent();
                p_ctxt.out << ">";
            }

            virtual std::string dump() const {
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

            virtual void render(context& p_ctxt) const
            {
                p_ctxt.indent();
                p_ctxt.out << "pegtl::sor<\n";
                for (auto itr = nodes.begin(); itr != nodes.end(); ++itr)
                {
                    scope S(p_ctxt);
                    if (itr != nodes.begin())
                    {
                        p_ctxt.out << ",\n";
                    }
                    (*itr)->render(p_ctxt);
                }
                p_ctxt.out << "\n";
                p_ctxt.indent();
                p_ctxt.out << ">";
            }

            virtual std::string dump() const {
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
            virtual void render(context& p_ctxt) const
            {
                p_ctxt.indent();
                p_ctxt.out << cpp::esc_name(name) << " :\n";
                {
                    scope S(p_ctxt);
                    defn->render(p_ctxt);
                }
                p_ctxt.out << "\n";
                p_ctxt.indent();
                p_ctxt.out << "{};\n";
            }

            std::string dump() const
            {
                std::string s;
                s += name;
                s += " ::= ";
                s += defn->dump();
                return s;
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
        struct build_ast<unescaped_rchar>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                std::vector<char32_t> cs;
                squeal::util::utf8::decoder::decode(p_in.string(), cs);
                if (cs.size() != 1)
                {
                    throw std::logic_error("bad escaped character");
                }
                node_ptr p(new crang_part_node(cs.front()));
                p_state.nodes.push_back(p);
            }
        };

        template<>
        struct build_ast<simple_escape_sequence>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                std::vector<char32_t> cs;
                squeal::util::utf8::decoder::decode(p_in.string(), cs);
                if (cs.size() != 1)
                {
                    throw std::logic_error("bad escaped character");
                }
                node_ptr p(new crang_part_node(cs.front()));
                p_state.nodes.push_back(p);
            }
        };

        template<>
        struct build_ast<unicode_quad>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                char32_t ch = 0;
                std::string x = p_in.string();
                for (size_t i = 0; i < x.size(); ++i)
                {
                    if ('0' <= x[i] && x[i] <= '9')
                    {
                        ch = (ch << 4) + (x[i] - '0');
                    }
                    else if ('a' <= x[i] && x[i] <= 'f')
                    {
                        ch = (ch << 4) + (x[i] - 'a' + 10);
                    }
                    else if ('A' <= x[i] && x[i] <= 'F')
                    {
                        ch = (ch << 4) + (x[i] - 'A' + 10);
                    }
                    else
                    {
                        throw std::logic_error("bad hexit character");
                    }
                }

                node_ptr p(new crang_part_node(ch));
                p_state.nodes.push_back(p);
            }
        };

        template<>
        struct build_ast<unicode_oct>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                char32_t ch = 0;
                std::string x = p_in.string();
                for (size_t i = 0; i < x.size(); ++i)
                {
                    if ('0' <= x[i] && x[i] <= '9')
                    {
                        ch = (ch << 4) + (x[i] - '0');
                    }
                    else if ('a' <= x[i] && x[i] <= 'f')
                    {
                        ch = (ch << 4) + (x[i] - 'a' + 10);
                    }
                    else if ('A' <= x[i] && x[i] <= 'F')
                    {
                        ch = (ch << 4) + (x[i] - 'A' + 10);
                    }
                    else
                    {
                        throw std::logic_error("bad hexit character");
                    }
                }

                node_ptr p(new crang_part_node(ch));
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

        template <>
        struct build_ast<cclass_name>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                node_ptr p(new cclass_node(p_in.string()));
                p_state.nodes.push_back(p);
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
