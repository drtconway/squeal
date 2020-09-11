#ifndef SQUEAL_PARSING_HPP
#define SQUEAL_PARSING_HPP

#ifndef SQUEAL_GRAMMAR_HPP
#include "squeal/grammar.hpp"
#endif

#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

namespace squeal
{
    namespace parsing
    {
        struct node
        {
            virtual ~node() {}

            virtual std::string kind()
            {
                return typeid(this).name();
            }
        };
        using node_ptr = std::shared_ptr<node>;

        template <typename Tag>
        struct basic_node : node
        {
            using tag_type = Tag;

            std::string text;

            basic_node(const std::string& p_text)
                : text(p_text)
            {}

            virtual std::string kind()
            {
                return typeid(this).name();
            }
        };

        struct state
        {
            std::vector<node_ptr> nodes;

            template<typename NodeType>
            std::shared_ptr<NodeType> top()
            {
                node_ptr p = nodes.back();
                std::shared_ptr<NodeType> q = std::dynamic_pointer_cast<NodeType>(p);
                return q;
            }

            template<typename NodeType>
            std::shared_ptr<NodeType> pop()
            {
                std::shared_ptr<NodeType> p = top<NodeType>();
                nodes.pop_back();
                return p;
            }

            node_ptr pop_node()
            {
                node_ptr p = nodes.back();
                nodes.pop_back();
                return p;
            }
        };

        template<typename Rule>
        struct build_ast : tao::pegtl::nothing<Rule> {};

        template<typename Tag>
        struct build_ast_basic
        {
            using node_type = basic_node<Tag>;

            template<typename ActionInput>
            static void apply(const ActionInput& in, state& p_state)
            {
                node_ptr n(new node_type(in.string()));
                p_state.nodes.push_back(n);
            }
        };

        template <typename T, typename U>
        node_ptr cons(node_ptr p)
        {
            std::shared_ptr<U> q = std::dynamic_pointer_cast<U>(p);
            if (q)
            {
                return node_ptr(new T(*q));
            }
            throw std::logic_error("no valid type cast");
        }
        template <typename T, typename U, typename V, typename... Us>
        node_ptr cons(node_ptr p)
        {
            std::shared_ptr<U> q = std::dynamic_pointer_cast<U>(p);
            if (q)
            {
                return node_ptr(new T(*q));
            }
            return cons<T, V, Us...>(p);
        }

        using identifier_node = basic_node<squeal::grammar::identifier>;
        using identifier_node_ptr = std::shared_ptr<identifier_node>;
        template<>
        struct build_ast<squeal::grammar::identifier>
            : build_ast_basic<squeal::grammar::identifier> {};

        using unsigned_integer_node = basic_node<squeal::grammar::unsigned_integer>;
        using unsigned_integer_node_ptr = std::shared_ptr<unsigned_integer_node>;
        template<>
        struct build_ast<squeal::grammar::unsigned_integer>
            : build_ast_basic<squeal::grammar::unsigned_integer> {};

        using opt_sign_node = basic_node<squeal::grammar::opt_sign>;
        using opt_sign_node_ptr = std::shared_ptr<opt_sign_node>;
        template<>
        struct build_ast<squeal::grammar::opt_sign>
            : build_ast_basic<squeal::grammar::opt_sign> {};

        using signed_integer_node = basic_node<squeal::grammar::signed_integer>;
        using signed_integer_node_ptr = std::shared_ptr<signed_integer_node>;
        template<>
        struct build_ast<squeal::grammar::signed_integer>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& in, state& p_state)
            {
                unsigned_integer_node_ptr x = p_state.pop<unsigned_integer_node>();
                opt_sign_node_ptr s = p_state.pop<opt_sign_node>();

                node_ptr n = node_ptr(new signed_integer_node(s->text + x->text));
                p_state.nodes.push_back(n);
            }
        };

        using exact_numeric_literal_node = basic_node<squeal::grammar::exact_numeric_literal>;
        using exact_numeric_literal_node_pr = std::shared_ptr<exact_numeric_literal_node>;
        template<>
        struct build_ast<squeal::grammar::exact_numeric_literal>
            : build_ast_basic<squeal::grammar::exact_numeric_literal> {};

        using approximate_numeric_literal_node = basic_node<squeal::grammar::approximate_numeric_literal>;
        using approximate_numeric_literal_node_ptr = std::shared_ptr<approximate_numeric_literal_node>;
        template<>
        struct build_ast<squeal::grammar::approximate_numeric_literal>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& in, state& p_state)
            {
                signed_integer_node_ptr x = p_state.pop<signed_integer_node>();
                exact_numeric_literal_node_pr m = p_state.pop<exact_numeric_literal_node>();

                node_ptr n = node_ptr(new approximate_numeric_literal_node(m->text + "e" + x->text));
                p_state.nodes.push_back(n);
            }
        };

        struct unsigned_numeric_literal_node : basic_node<squeal::grammar::unsigned_numeric_literal>
        {
            unsigned_numeric_literal_node(const exact_numeric_literal_node& p_node)
                : basic_node<squeal::grammar::unsigned_numeric_literal>(p_node.text)
            {
            }

            unsigned_numeric_literal_node(const approximate_numeric_literal_node& p_node)
                : basic_node<squeal::grammar::unsigned_numeric_literal>(p_node.text)
            {
            }

        };
        using unsigned_numeric_literal_node_ptr = std::shared_ptr<unsigned_numeric_literal_node>;
        template<>
        struct build_ast<squeal::grammar::unsigned_numeric_literal>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& in, state& p_state)
            {

                node_ptr p = p_state.pop_node();
                node_ptr q = cons<unsigned_numeric_literal_node,
                                  exact_numeric_literal_node,
                                  approximate_numeric_literal_node>(p);
                p_state.nodes.push_back(q);
            }
        };

        using signed_numeric_literal_node = basic_node<squeal::grammar::signed_numeric_literal>;
        using signed_numeric_literal_node_ptr = std::shared_ptr<signed_numeric_literal_node>;
        template<>
        struct build_ast<squeal::grammar::signed_numeric_literal>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& in, state& p_state)
            {

                unsigned_numeric_literal_node_ptr x = p_state.pop<unsigned_numeric_literal_node>();
                opt_sign_node_ptr s = p_state.pop<opt_sign_node>();

                node_ptr n = node_ptr(new signed_numeric_literal_node(s->text + x->text));
                p_state.nodes.push_back(n);
            }
        };
    }
    // namespace parsing
}
// namespace squeal

#endif // SQUEAL_PARSING_HPP
