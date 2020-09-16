#include "squeal/util/utf8.hpp"

#define BOOST_TEST_MODULE squeal utf8 decoder
#include <boost/test/unit_test.hpp>

#include <iostream>

BOOST_AUTO_TEST_CASE( str0 )
{
    std::string s(u8"a");
    squeal::util::utf8::decoder dec(s);

    auto b = dec.begin();
    auto e = dec.end();
    BOOST_CHECK_EQUAL(b != e, true);
    BOOST_CHECK_EQUAL(*b, static_cast<char32_t>('a'));
    ++b;
    BOOST_CHECK_EQUAL(b == e, true);
}

BOOST_AUTO_TEST_CASE( str1 )
{
    std::string s(u8"abc");
    squeal::util::utf8::decoder dec(s);

    auto b = dec.begin();
    auto e = dec.end();
    BOOST_CHECK_EQUAL(b != e, true);
    BOOST_CHECK_EQUAL(*b, static_cast<char32_t>('a'));
    ++b;
    BOOST_CHECK_EQUAL(b != e, true);
    BOOST_CHECK_EQUAL(*b, static_cast<char32_t>('b'));
    ++b;
    BOOST_CHECK_EQUAL(b != e, true);
    BOOST_CHECK_EQUAL(*b, static_cast<char32_t>('c'));
    ++b;
    BOOST_CHECK_EQUAL(b == e, true);
}

BOOST_AUTO_TEST_CASE( str2 )
{
    std::string s(u8"\u0061\u0304");
    BOOST_CHECK_EQUAL(s.size(), 3);
    squeal::util::utf8::decoder dec(s);

    auto b = dec.begin();
    auto e = dec.end();
    BOOST_CHECK_EQUAL(b != e, true);
    BOOST_CHECK_EQUAL(*b, 0x61);
    ++b;
    BOOST_CHECK_EQUAL(b != e, true);
    BOOST_CHECK_EQUAL(*b, 0x304);
    ++b;
    BOOST_CHECK_EQUAL(b == e, true);
}

BOOST_AUTO_TEST_CASE( str3 )
{
    std::string s(u8"\u0024");
    BOOST_CHECK_EQUAL(s.size(), 1);
    squeal::util::utf8::decoder dec(s);

    auto b = dec.begin();
    auto e = dec.end();
    BOOST_CHECK_EQUAL(b != e, true);
    BOOST_CHECK_EQUAL(*b, 0x24);
    ++b;
    BOOST_CHECK_EQUAL(b == e, true);
}

BOOST_AUTO_TEST_CASE( str4 )
{
    std::string s(u8"\u00A2");
    BOOST_CHECK_EQUAL(s.size(), 2);
    squeal::util::utf8::decoder dec(s);

    auto b = dec.begin();
    auto e = dec.end();
    BOOST_CHECK_EQUAL(b != e, true);
    BOOST_CHECK_EQUAL(*b, 0xA2);
    ++b;
    BOOST_CHECK_EQUAL(b == e, true);
}

BOOST_AUTO_TEST_CASE( str5 )
{
    std::string s(u8"\u0939");
    BOOST_CHECK_EQUAL(s.size(), 3);
    squeal::util::utf8::decoder dec(s);

    auto b = dec.begin();
    auto e = dec.end();
    BOOST_CHECK_EQUAL(b != e, true);
    BOOST_CHECK_EQUAL(*b, 0x939);
    ++b;
    BOOST_CHECK_EQUAL(b == e, true);
}

BOOST_AUTO_TEST_CASE( str6 )
{
    std::string s(u8"\U00010348");
    BOOST_CHECK_EQUAL(s.size(), 4);
    BOOST_CHECK_EQUAL(static_cast<uint8_t>(s[0]), 0xF0);
    BOOST_CHECK_EQUAL(static_cast<uint8_t>(s[1]), 0x90);
    BOOST_CHECK_EQUAL(static_cast<uint8_t>(s[2]), 0x8D);
    BOOST_CHECK_EQUAL(static_cast<uint8_t>(s[3]), 0x88);
    squeal::util::utf8::decoder dec(s);

    auto b = dec.begin();
    auto e = dec.end();
    BOOST_CHECK_EQUAL(b != e, true);
    BOOST_CHECK_EQUAL(*b, 0x10348);
    ++b;
    BOOST_CHECK_EQUAL(b == e, true);
}
