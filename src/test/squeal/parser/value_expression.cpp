#include "squeal/parser.hpp"
#include "squeal/parser.hpp"

#define BOOST_TEST_MODULE squeal parser
#include <boost/test/unit_test.hpp>

#include <iostream>

using namespace squeal::parser::ast;

namespace // anonymous
{
}
// namespace anonymous

BOOST_AUTO_TEST_CASE( bool0 )
{
    std::string src("TRUE");
    node_ptr p = squeal::parser::literal(src);
    BOOST_REQUIRE_EQUAL(p != NULL, true);
    std::string res = p->json();
    BOOST_REQUIRE_EQUAL(res, R"x({"": [{"squeal::grammar::boolean_literal": "TRUE"}]})x");
}

BOOST_AUTO_TEST_CASE( bool1 )
{
    std::string src("FALSE");
    node_ptr p = squeal::parser::literal(src);
    BOOST_REQUIRE_EQUAL(p != NULL, true);
    std::string res = p->json();
    BOOST_REQUIRE_EQUAL(res, R"x({"": [{"squeal::grammar::boolean_literal": "FALSE"}]})x");
}

BOOST_AUTO_TEST_CASE( bool2 )
{
    std::string src("UNKNOWN");
    node_ptr p = squeal::parser::literal(src);
    BOOST_REQUIRE_EQUAL(p != NULL, true);
    std::string res = p->json();
    BOOST_REQUIRE_EQUAL(res, R"x({"": [{"squeal::grammar::boolean_literal": "UNKNOWN"}]})x");
}

BOOST_AUTO_TEST_CASE( chrstr0 )
{
    std::string src("'a'");
    node_ptr p = squeal::parser::literal(src);
    BOOST_REQUIRE_EQUAL(p != NULL, true);
    std::string res = p->json();
    BOOST_REQUIRE_EQUAL(res, R"x({"": [{"squeal::grammar::character_string_literal": [{"squeal::grammar::character_string_literal_part": "'a'"}]}]})x");
}

BOOST_AUTO_TEST_CASE( chrstr1 )
{
    std::string src("'a' 'b'");
    node_ptr p = squeal::parser::literal(src);
    BOOST_REQUIRE_EQUAL(p != NULL, true);
    std::string res = p->json();
    BOOST_REQUIRE_EQUAL(res, R"x({"": [{"squeal::grammar::character_string_literal": [{"squeal::grammar::character_string_literal_part": "'a'"}, {"squeal::grammar::character_string_literal_continuation": [{"squeal::grammar::character_string_literal_part": "'b'"}]}]}]})x");
}

BOOST_AUTO_TEST_CASE( chrstr2 )
{
    std::string src("'a''b'");
    node_ptr p = squeal::parser::literal(src);
    BOOST_REQUIRE_EQUAL(p != NULL, true);
    std::string res = p->json();
    BOOST_REQUIRE_EQUAL(res, R"x({"": [{"squeal::grammar::character_string_literal": [{"squeal::grammar::character_string_literal_part": "'a''b'"}]}]})x");
}

BOOST_AUTO_TEST_CASE( chrstr3 )
{
    std::string src("_LATIN1'a'");
    node_ptr p = squeal::parser::literal(src);
    BOOST_REQUIRE_EQUAL(p != NULL, true);
    std::string res = p->json();
    BOOST_REQUIRE_EQUAL(res, R"x({"": [{"squeal::grammar::character_string_literal": [{"squeal::grammar::standard_character_set_name": [{"squeal::grammar::SQL_language_identifier": "LATIN1"}]}, {"squeal::grammar::character_string_literal_part": "'a'"}]}]})x");
}

BOOST_AUTO_TEST_CASE( select0 )
{
    std::string src(" SELECT * FROM foo");
    node_ptr p = squeal::parser::query_specification(src);
    BOOST_REQUIRE_EQUAL(p != NULL, true);
    std::string res = p->json();
    BOOST_REQUIRE_EQUAL(res, R"x({"": [{"squeal::grammar::query_specification": [{"squeal::grammar::select_list": [{"squeal::grammar::asterisk": "*"}]}, {"squeal::grammar::table_expression": [{"squeal::grammar::from_clause": [{"squeal::grammar::table_reference_list": [{"squeal::grammar::table_primary": [{"squeal::grammar::table_name": [{"squeal::grammar::qualified_identifier": "foo"}]}]}]}]}]}]}]})x");
}

BOOST_AUTO_TEST_CASE( select1 )
{
    std::string src(" SELECT * FROM foo WHERE bar = baz");
    node_ptr p = squeal::parser::query_specification(src);
    BOOST_REQUIRE_EQUAL(p != NULL, true);
    std::string res = p->json();
    BOOST_REQUIRE_EQUAL(res, R"x({"": [{"squeal::grammar::query_specification": [{"squeal::grammar::select_list": [{"squeal::grammar::asterisk": "*"}]}, {"squeal::grammar::table_expression": [{"squeal::grammar::from_clause": [{"squeal::grammar::table_reference_list": [{"squeal::grammar::table_primary": [{"squeal::grammar::table_name": [{"squeal::grammar::qualified_identifier": "foo"}]}]}]}]}, {"squeal::grammar::where_clause": [{"squeal::grammar::search_condition": [{"squeal::grammar::boolean_term": [{"squeal::grammar::boolean_factor": [{"squeal::grammar::boolean_test": [{"squeal::grammar::comparison_predicate": [{"squeal::grammar::general_value_specification": [{"squeal::grammar::SQL_parameter_reference": [{"squeal::grammar::identifier": "bar"}]}]}, {"squeal::grammar::equals_operator": "="}, {"squeal::grammar::general_value_specification": [{"squeal::grammar::SQL_parameter_reference": [{"squeal::grammar::identifier": "baz"}]}]}]}]}]}]}]}]}]}]}]})x");
}

