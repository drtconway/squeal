#include "squeal/util/meta_grammar.hpp"

#define BOOST_TEST_MODULE squeal meta grammar
#include <boost/test/unit_test.hpp>

#include <iostream>

BOOST_AUTO_TEST_CASE( name0 )
{
    std::string src("<a>");

    tao::pegtl::string_input in(src, "string");

    squeal::meta_grammar::state S;

    bool result = tao::pegtl::parse<squeal::meta_grammar::name, squeal::meta_grammar::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_REQUIRE_EQUAL(S.nodes.size(), 1);
    squeal::meta_grammar::name_node_ptr p = std::dynamic_pointer_cast<squeal::meta_grammar::name_node>(S.nodes[0]);
    BOOST_REQUIRE_EQUAL(p.get() != NULL, true);
}

BOOST_AUTO_TEST_CASE( name1 )
{
    std::string src("<SQL object identifier>");

    tao::pegtl::string_input in(src, "string");

    squeal::meta_grammar::state S;

    bool result = tao::pegtl::parse<squeal::meta_grammar::name, squeal::meta_grammar::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_REQUIRE_EQUAL(S.nodes.size(), 1);
    squeal::meta_grammar::name_node_ptr p = std::dynamic_pointer_cast<squeal::meta_grammar::name_node>(S.nodes[0]);
    BOOST_REQUIRE_EQUAL(p.get() != NULL, true);
}

BOOST_AUTO_TEST_CASE( crang0 )
{
    std::string src("(a-z)");

    tao::pegtl::string_input in(src, "string");

    squeal::meta_grammar::state S;

    bool result = tao::pegtl::parse<squeal::meta_grammar::crang, squeal::meta_grammar::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_REQUIRE_EQUAL(S.nodes.size(), 1);
    squeal::meta_grammar::crang_node_ptr p = std::dynamic_pointer_cast<squeal::meta_grammar::crang_node>(S.nodes[0]);
    BOOST_REQUIRE_EQUAL(p.get() != NULL, true);
    BOOST_REQUIRE_EQUAL(p->parts.size(), 1);
}

BOOST_AUTO_TEST_CASE( crang1 )
{
    std::string src("(_)");

    tao::pegtl::string_input in(src, "string");

    squeal::meta_grammar::state S;

    bool result = tao::pegtl::parse<squeal::meta_grammar::crang, squeal::meta_grammar::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_REQUIRE_EQUAL(S.nodes.size(), 1);
    squeal::meta_grammar::crang_node_ptr p = std::dynamic_pointer_cast<squeal::meta_grammar::crang_node>(S.nodes[0]);
    BOOST_REQUIRE_EQUAL(p.get() != NULL, true);
    BOOST_REQUIRE_EQUAL(p->parts.size(), 1);
}

BOOST_AUTO_TEST_CASE( crang2 )
{
    std::string src("(a-zA-Z_)");

    tao::pegtl::string_input in(src, "string");

    squeal::meta_grammar::state S;

    bool result = tao::pegtl::parse<squeal::meta_grammar::crang, squeal::meta_grammar::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_REQUIRE_EQUAL(S.nodes.size(), 1);
    squeal::meta_grammar::crang_node_ptr p = std::dynamic_pointer_cast<squeal::meta_grammar::crang_node>(S.nodes[0]);
    BOOST_REQUIRE_EQUAL(p.get() != NULL, true);
    BOOST_REQUIRE_EQUAL(p->parts.size(), 3);
}

BOOST_AUTO_TEST_CASE( conj0 )
{
    std::string src("<a> <b> <c> <d>");

    tao::pegtl::string_input in(src, "string");

    squeal::meta_grammar::state S;

    bool result = tao::pegtl::parse<squeal::meta_grammar::conj, squeal::meta_grammar::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_REQUIRE_EQUAL(S.nodes.size(), 1);
    squeal::meta_grammar::conj_node_ptr p = std::dynamic_pointer_cast<squeal::meta_grammar::conj_node>(S.nodes[0]);
    BOOST_REQUIRE_EQUAL(p.get() != NULL, true);
    BOOST_REQUIRE_EQUAL(p->nodes.size(), 4);
}

BOOST_AUTO_TEST_CASE( conj1 )
{
    std::string src("<temporary table declaration> <module contents>...");

    tao::pegtl::string_input in(src, "string");

    squeal::meta_grammar::state S;

    bool result = tao::pegtl::parse<squeal::meta_grammar::conj, squeal::meta_grammar::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_REQUIRE_EQUAL(S.nodes.size(), 1);
    squeal::meta_grammar::conj_node_ptr p = std::dynamic_pointer_cast<squeal::meta_grammar::conj_node>(S.nodes[0]);
    BOOST_REQUIRE_EQUAL(p.get() != NULL, true);
    BOOST_REQUIRE_EQUAL(p->nodes.size(), 2);
}

BOOST_AUTO_TEST_CASE( disj0 )
{
    std::string src("<a>  | <b>  | <c>  | <d>");

    tao::pegtl::string_input in(src, "string");

    squeal::meta_grammar::state S;

    bool result = tao::pegtl::parse<squeal::meta_grammar::disj, squeal::meta_grammar::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_REQUIRE_EQUAL(S.nodes.size(), 1);
    squeal::meta_grammar::disj_node_ptr p = std::dynamic_pointer_cast<squeal::meta_grammar::disj_node>(S.nodes[0]);
    BOOST_REQUIRE_EQUAL(p.get() != NULL, true);
    BOOST_REQUIRE_EQUAL(p->nodes.size(), 4);
}

BOOST_AUTO_TEST_CASE( plus0 )
{
    std::string src("<a>...");

    tao::pegtl::string_input in(src, "string");

    squeal::meta_grammar::state S;

    bool result = tao::pegtl::parse<squeal::meta_grammar::conj, squeal::meta_grammar::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_REQUIRE_EQUAL(S.nodes.size(), 1);
    squeal::meta_grammar::plus_node_ptr p = std::dynamic_pointer_cast<squeal::meta_grammar::plus_node>(S.nodes[0]);
    BOOST_REQUIRE_EQUAL(p.get() != NULL, true);
}

BOOST_AUTO_TEST_CASE( opt0 )
{
    std::string src("[ <a> ]");

    tao::pegtl::string_input in(src, "string");

    squeal::meta_grammar::state S;

    bool result = tao::pegtl::parse<squeal::meta_grammar::brac, squeal::meta_grammar::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_REQUIRE_EQUAL(S.nodes.size(), 1);
    squeal::meta_grammar::opt_node_ptr p = std::dynamic_pointer_cast<squeal::meta_grammar::opt_node>(S.nodes[0]);
    BOOST_REQUIRE_EQUAL(p.get() != NULL, true);
}

BOOST_AUTO_TEST_CASE( opt1 )
{
    std::string src("[ <a>... ]");

    tao::pegtl::string_input in(src, "string");

    squeal::meta_grammar::state S;

    bool result = tao::pegtl::parse<squeal::meta_grammar::brac, squeal::meta_grammar::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_REQUIRE_EQUAL(S.nodes.size(), 1);
    squeal::meta_grammar::star_node_ptr p = std::dynamic_pointer_cast<squeal::meta_grammar::star_node>(S.nodes[0]);
    BOOST_REQUIRE_EQUAL(p.get() != NULL, true);
}

BOOST_AUTO_TEST_CASE( exprn0 )
{
    std::string src("<module name clause> <language clause> <module authorization clause> [ <module path specification> ] [ <module transform group specification> ] [ <temporary table declaration>... ] <module contents>...");

    tao::pegtl::string_input in(src, "string");

    squeal::meta_grammar::state S;

    bool result = tao::pegtl::parse<squeal::meta_grammar::expression, squeal::meta_grammar::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_REQUIRE_EQUAL(S.nodes.size(), 1);
    squeal::meta_grammar::conj_node_ptr p = std::dynamic_pointer_cast<squeal::meta_grammar::conj_node>(S.nodes[0]);
    BOOST_REQUIRE_EQUAL(p.get() != NULL, true);
    BOOST_REQUIRE_EQUAL(p->nodes.size(), 7);
}

BOOST_AUTO_TEST_CASE( defn0 )
{
    std::string src("<a> ::= b <c>");

    tao::pegtl::string_input in(src, "string");

    squeal::meta_grammar::state S;

    bool result = tao::pegtl::parse<squeal::meta_grammar::definition, squeal::meta_grammar::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_REQUIRE_EQUAL(S.nodes.size(), 1);
    squeal::meta_grammar::defn_node_ptr p = std::dynamic_pointer_cast<squeal::meta_grammar::defn_node>(S.nodes[0]);
    BOOST_REQUIRE_EQUAL(p.get() != NULL, true);
}

BOOST_AUTO_TEST_CASE( defn1 )
{
    std::string src("<SQL object identifier> ::= <SQL provenance> <SQL variant>");

    tao::pegtl::string_input in(src, "string");

    squeal::meta_grammar::state S;

    bool result = tao::pegtl::parse<squeal::meta_grammar::definition, squeal::meta_grammar::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_REQUIRE_EQUAL(S.nodes.size(), 1);
    squeal::meta_grammar::defn_node_ptr p = std::dynamic_pointer_cast<squeal::meta_grammar::defn_node>(S.nodes[0]);
    BOOST_REQUIRE_EQUAL(p.get() != NULL, true);
}

BOOST_AUTO_TEST_CASE( defn2 )
{
    std::string src("<SQL-client module definition> ::= <module name clause> <language clause> <module authorization clause> [ <module path specification> ] [ <module transform group specification> ] [ <temporary table declaration>... ] <module contents>...");

    tao::pegtl::string_input in(src, "string");

    squeal::meta_grammar::state S;

    bool result = tao::pegtl::parse<squeal::meta_grammar::definition, squeal::meta_grammar::build_ast>(in, S);
    BOOST_CHECK_EQUAL(result, true);

    BOOST_REQUIRE_EQUAL(S.nodes.size(), 1);
    squeal::meta_grammar::defn_node_ptr p = std::dynamic_pointer_cast<squeal::meta_grammar::defn_node>(S.nodes[0]);
    BOOST_REQUIRE_EQUAL(p.get() != NULL, true);
}
