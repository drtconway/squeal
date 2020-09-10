#include "squeal/grammar.hpp"

#define BOOST_TEST_MODULE squeal grammar
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE( initial_alphabetic_character0 )
{
    tao::pegtl::string_input in(u8"a", "string");
    bool result = tao::pegtl::parse<squeal::grammar::initial_alphabetic_character>(in);
    BOOST_CHECK_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE( initial_alphabetic_character1 )
{
    tao::pegtl::string_input in(u8"π", "string");
    bool result = tao::pegtl::parse<squeal::grammar::initial_alphabetic_character>(in);
    BOOST_CHECK_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE( initial_alphabetic_character2 )
{
    tao::pegtl::string_input in(u8"1", "string");
    bool result = tao::pegtl::parse<squeal::grammar::initial_alphabetic_character>(in);
    BOOST_CHECK_EQUAL(result, false);
}

BOOST_AUTO_TEST_CASE( initial_alphabetic_character3 )
{
    tao::pegtl::string_input in(u8"೬", "string");
    bool result = tao::pegtl::parse<squeal::grammar::initial_alphabetic_character>(in);
    BOOST_CHECK_EQUAL(result, false);
}

BOOST_AUTO_TEST_CASE( initial_alphabetic_character4 )
{
    tao::pegtl::string_input in(u8"_", "string");
    bool result = tao::pegtl::parse<squeal::grammar::initial_alphabetic_character>(in);
    BOOST_CHECK_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE( initial_alphabetic_character5 )
{
    tao::pegtl::string_input in(u8"︴", "string");
    bool result = tao::pegtl::parse<squeal::grammar::initial_alphabetic_character>(in);
    BOOST_CHECK_EQUAL(result, false);
}

BOOST_AUTO_TEST_CASE( ideographic_character0 )
{
    tao::pegtl::string_input in(u8"次", "string");
    bool result = tao::pegtl::parse<squeal::grammar::ideographic_character>(in);
    BOOST_CHECK_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE( alternate_underscore0 )
{
    tao::pegtl::string_input in(u8"︴", "string");
    bool result = tao::pegtl::parse<squeal::grammar::alternate_underscore>(in);
    BOOST_CHECK_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE( non_combining0 )
{
    tao::pegtl::string_input in(u8"a", "string");
    bool result = tao::pegtl::parse<squeal::grammar::non_combining>(in);
    BOOST_CHECK_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE( non_combining1 )
{
    tao::pegtl::string_input in(u8"\u0306", "string");
    bool result = tao::pegtl::parse<squeal::grammar::non_combining>(in);
    BOOST_CHECK_EQUAL(result, false);
}

BOOST_AUTO_TEST_CASE( combining0 )
{
    tao::pegtl::string_input in(u8"a", "string");
    bool result = tao::pegtl::parse<squeal::grammar::combining>(in);
    BOOST_CHECK_EQUAL(result, false);
}

BOOST_AUTO_TEST_CASE( combining1 )
{
    tao::pegtl::string_input in(u8"\u0306", "string");
    bool result = tao::pegtl::parse<squeal::grammar::combining>(in);
    BOOST_CHECK_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE( combining_character0 )
{
    tao::pegtl::string_input in(u8"\u0304", "string");
    bool result = tao::pegtl::parse<squeal::grammar::combining_character>(in);
    BOOST_CHECK_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE( regular_identifier0 )
{
    tao::pegtl::string_input in(u8"foo", "string");
    bool result = tao::pegtl::parse<squeal::grammar::regular_identifier>(in);
    BOOST_CHECK_EQUAL(result, true);
}

