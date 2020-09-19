#include "squeal/parser.hpp"
#include "squeal/parser.hpp"

#define BOOST_TEST_MODULE squeal parser
#include <boost/test/unit_test.hpp>

#include <iostream>

BOOST_AUTO_TEST_CASE( bool0 )
{
    std::string src("TRUE");
    squeal::parser::ast::node_ptr p = squeal::parser::value_expression(src);
    squeal::parser::ast::boolean_literal_node_ptr q = std::dynamic_pointer_cast<squeal::parser::ast::boolean_literal_node>(p);
    BOOST_REQUIRE_EQUAL(q != NULL, true);
    BOOST_CHECK_EQUAL(q->value, "TRUE");
}

BOOST_AUTO_TEST_CASE( bool1 )
{
    std::string src("FALSE");
    squeal::parser::ast::node_ptr p = squeal::parser::value_expression(src);
    squeal::parser::ast::boolean_literal_node_ptr q = std::dynamic_pointer_cast<squeal::parser::ast::boolean_literal_node>(p);
    BOOST_REQUIRE_EQUAL(q != NULL, true);
    BOOST_CHECK_EQUAL(q->value, "FALSE");
}

BOOST_AUTO_TEST_CASE( bool2 )
{
    std::string src("UNKNOWN");
    squeal::parser::ast::node_ptr p = squeal::parser::value_expression(src);
    squeal::parser::ast::boolean_literal_node_ptr q = std::dynamic_pointer_cast<squeal::parser::ast::boolean_literal_node>(p);
    BOOST_REQUIRE_EQUAL(q != NULL, true);
    BOOST_CHECK_EQUAL(q->value, "UNKNOWN");
}

BOOST_AUTO_TEST_CASE( chrstr0 )
{
    std::string src("'a'");
    squeal::parser::ast::node_ptr p = squeal::parser::value_expression(src);
    squeal::parser::ast::character_string_literal_node_ptr q = std::dynamic_pointer_cast<squeal::parser::ast::character_string_literal_node>(p);
    BOOST_REQUIRE_EQUAL(q != NULL, true);
    BOOST_CHECK_EQUAL(q->value, "a");
}

BOOST_AUTO_TEST_CASE( chrstr1 )
{
    std::string src("'a' 'b'");
    squeal::parser::ast::node_ptr p = squeal::parser::value_expression(src);
    squeal::parser::ast::character_string_literal_node_ptr q = std::dynamic_pointer_cast<squeal::parser::ast::character_string_literal_node>(p);
    BOOST_REQUIRE_EQUAL(q != NULL, true);
    BOOST_CHECK_EQUAL(q->value, "ab");
}

BOOST_AUTO_TEST_CASE( chrstr2 )
{
    std::string src("'a''b'");
    squeal::parser::ast::node_ptr p = squeal::parser::value_expression(src);
    squeal::parser::ast::character_string_literal_node_ptr q = std::dynamic_pointer_cast<squeal::parser::ast::character_string_literal_node>(p);
    BOOST_REQUIRE_EQUAL(q != NULL, true);
    BOOST_CHECK_EQUAL(q->value, "a'b");
}

