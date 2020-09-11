#include "squeal/parsing.hpp"

#define BOOST_TEST_MODULE squeal parsing
#include <boost/test/unit_test.hpp>

#include <iostream>

BOOST_AUTO_TEST_CASE( identifier0 )
{
    std::string src(u8"a");

    tao::pegtl::string_input in(src, "string");

    squeal::parsing::state S;
    bool result = tao::pegtl::parse<squeal::grammar::identifier, squeal::parsing::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_CHECK_EQUAL(S.nodes.size(), 1);
    squeal::parsing::identifier_node_ptr p = std::dynamic_pointer_cast<squeal::parsing::identifier_node>(S.nodes[0]);
    BOOST_CHECK_EQUAL(p.get() != NULL, true);
    BOOST_CHECK_EQUAL(p->text, src);
}

BOOST_AUTO_TEST_CASE( identifier1 )
{
    std::string src(u8"f0o");

    tao::pegtl::string_input in(src, "string");

    squeal::parsing::state S;
    bool result = tao::pegtl::parse<squeal::grammar::identifier, squeal::parsing::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_CHECK_EQUAL(S.nodes.size(), 1);
    squeal::parsing::identifier_node_ptr p = std::dynamic_pointer_cast<squeal::parsing::identifier_node>(S.nodes[0]);
    BOOST_CHECK_EQUAL(p.get() != NULL, true);
    BOOST_CHECK_EQUAL(p->text, src);
}

BOOST_AUTO_TEST_CASE( identifier2 )
{
    std::string src(u8"κόσμε");

    tao::pegtl::string_input in(src, "string");

    squeal::parsing::state S;
    bool result = tao::pegtl::parse<squeal::grammar::identifier, squeal::parsing::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_CHECK_EQUAL(S.nodes.size(), 1);
    squeal::parsing::identifier_node_ptr p = std::dynamic_pointer_cast<squeal::parsing::identifier_node>(S.nodes[0]);
    BOOST_CHECK_EQUAL(p.get() != NULL, true);
    BOOST_CHECK_EQUAL(p->text, src);
}

BOOST_AUTO_TEST_CASE( identifier3 )
{
    std::string src(u8"łódź");

    tao::pegtl::string_input in(src, "string");

    squeal::parsing::state S;
    bool result = tao::pegtl::parse<squeal::grammar::identifier, squeal::parsing::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_CHECK_EQUAL(S.nodes.size(), 1);
    squeal::parsing::identifier_node_ptr p = std::dynamic_pointer_cast<squeal::parsing::identifier_node>(S.nodes[0]);
    BOOST_CHECK_EQUAL(p.get() != NULL, true);
    BOOST_CHECK_EQUAL(p->text, src);
}

BOOST_AUTO_TEST_CASE( identifier4 )
{
    //std::string src(u8"Glāžšķūņa");
    std::string src(u8"\u0061\u0304");

    tao::pegtl::string_input in(src, "string");

    squeal::parsing::state S;
    bool result = tao::pegtl::parse<squeal::grammar::identifier, squeal::parsing::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_CHECK_EQUAL(S.nodes.size(), 1);
    squeal::parsing::identifier_node_ptr p = std::dynamic_pointer_cast<squeal::parsing::identifier_node>(S.nodes[0]);
    BOOST_CHECK_EQUAL(p.get() != NULL, true);
    BOOST_CHECK_EQUAL(p->text, src);
}

BOOST_AUTO_TEST_CASE( exact_numeric_literal0 )
{
    std::string src(u8"123");

    tao::pegtl::string_input in(src, "string");

    squeal::parsing::state S;
    bool result = tao::pegtl::parse<squeal::grammar::exact_numeric_literal, squeal::parsing::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_CHECK_EQUAL(S.nodes.size(), 1);
    squeal::parsing::exact_numeric_literal_node_pr p = std::dynamic_pointer_cast<squeal::parsing::exact_numeric_literal_node>(S.nodes[0]);
    BOOST_CHECK_EQUAL(p.get() != NULL, true);
    BOOST_CHECK_EQUAL(p->text, src);
}

BOOST_AUTO_TEST_CASE( exact_numeric_literal1 )
{
    std::string src(u8"123.");

    tao::pegtl::string_input in(src, "string");

    squeal::parsing::state S;
    bool result = tao::pegtl::parse<squeal::grammar::exact_numeric_literal, squeal::parsing::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_CHECK_EQUAL(S.nodes.size(), 1);
    squeal::parsing::exact_numeric_literal_node_pr p = std::dynamic_pointer_cast<squeal::parsing::exact_numeric_literal_node>(S.nodes[0]);
    BOOST_CHECK_EQUAL(p.get() != NULL, true);
    BOOST_CHECK_EQUAL(p->text, src);
}

BOOST_AUTO_TEST_CASE( exact_numeric_literal2 )
{
    std::string src(u8"123.456");

    tao::pegtl::string_input in(src, "string");

    squeal::parsing::state S;
    bool result = tao::pegtl::parse<squeal::grammar::exact_numeric_literal, squeal::parsing::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_CHECK_EQUAL(S.nodes.size(), 1);
    squeal::parsing::exact_numeric_literal_node_pr p = std::dynamic_pointer_cast<squeal::parsing::exact_numeric_literal_node>(S.nodes[0]);
    BOOST_CHECK_EQUAL(p.get() != NULL, true);
    BOOST_CHECK_EQUAL(p->text, src);
}

BOOST_AUTO_TEST_CASE( exact_numeric_literal3 )
{
    std::string src(u8".456");

    tao::pegtl::string_input in(src, "string");

    squeal::parsing::state S;
    bool result = tao::pegtl::parse<squeal::grammar::exact_numeric_literal, squeal::parsing::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_CHECK_EQUAL(S.nodes.size(), 1);
    squeal::parsing::exact_numeric_literal_node_pr p = std::dynamic_pointer_cast<squeal::parsing::exact_numeric_literal_node>(S.nodes[0]);
    BOOST_CHECK_EQUAL(p.get() != NULL, true);
    BOOST_CHECK_EQUAL(p->text, src);
}

BOOST_AUTO_TEST_CASE( signed_numeric_literal0 )
{
    std::string src(u8"456");

    tao::pegtl::string_input in(src, "string");

    squeal::parsing::state S;
    bool result = tao::pegtl::parse<squeal::grammar::signed_numeric_literal, squeal::parsing::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_CHECK_EQUAL(S.nodes.size(), 1);
    squeal::parsing::signed_numeric_literal_node_ptr p = std::dynamic_pointer_cast<squeal::parsing::signed_numeric_literal_node>(S.nodes[0]);
    BOOST_CHECK_EQUAL(p.get() != NULL, true);
    BOOST_CHECK_EQUAL(p->text, src);
}
