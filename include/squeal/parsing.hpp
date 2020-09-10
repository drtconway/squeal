#ifndef SQUEAL_PARSING_HPP
#define SQUEAL_PARSING_HPP

#ifndef SQUEAL_GRAMMAR_HPP
#include "squeal/grammar.hpp"
#endif

#include <memory>
#include <string>
#include <vector>

namespace squeal
{
    namespace parsing
    {
        struct node
        {
            virtual ~node() {}
        };
        using node_ptr = std::shared_ptr<node>;

        struct identifier_node : node
        {
            std::string name;

            identifier_node(const std::string& p_name)
                : name(p_name)
            {}
        };
        using identifier_node_ptr = std::shared_ptr<identifier_node>;

        struct state
        {
            std::vector<node_ptr> nodes;
        };

        template<typename Rule>
        struct build_ast : tao::pegtl::nothing<Rule> {};

        template<>
        struct build_ast<squeal::grammar::identifier>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& in, state& p_state)
            {
                node_ptr n(new identifier_node(in.string()));
                p_state.nodes.push_back(n);
            }
        };
    }
    // namespace parsing
}
// namespace squeal

#endif // SQUEAL_PARSING_HPP
