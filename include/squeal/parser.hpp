#ifndef SQUEAL_PARSER_HPP
#define SQUEAL_PARSER_HPP

#ifndef SQUEAL_PARSER_AST_HPP
#include "squeal/parser/ast.hpp"
#endif

namespace squeal
{
    namespace parser
    {
        squeal::parser::ast::node_ptr literal(const std::string& p_src);

        squeal::parser::ast::node_ptr query_specification(const std::string& p_src, bool p_trace = false);

        squeal::parser::ast::node_ptr value_expression(const std::string& p_src);
    }
    // namespace parser
}
// namespace squeal

#endif // SQUEAL_PARSER_HPP
