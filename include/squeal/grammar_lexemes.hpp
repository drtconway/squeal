#ifndef SQUEAL_GRAMMAR_LEXEMES_HPP
#define SQUEAL_GRAMMAR_LEXEMES_HPP

namespace squeal
{
    namespace grammar
    {
        //
        // Single characters
        //

        struct double_quote : tao::pegtl::utf8::one<'"'> {};
        struct percent : tao::pegtl::utf8::one<'%'> {};
        struct ampersand : tao::pegtl::utf8::one<'&'> {};
        struct quote : tao::pegtl::utf8::one<'\''> {};
        struct left_paren : tao::pegtl::utf8::one<'('> {};
        struct right_paren : tao::pegtl::utf8::one<')'> {};
        struct asterisk : tao::pegtl::utf8::one<'*'> {};
        struct plus_sign : tao::pegtl::utf8::one<'+'> {};
        struct comma : tao::pegtl::utf8::one<','> {};
        struct minus_sign : tao::pegtl::utf8::one<'-'> {};
        struct period : tao::pegtl::utf8::one<'.'> {};
        struct solidus : tao::pegtl::utf8::one<'/'> {};
        struct colon : tao::pegtl::utf8::one<':'> {};
        struct semicolon : tao::pegtl::utf8::one<';'> {};
        struct less_than_operator : tao::pegtl::utf8::one<'<'> {};
        struct equals_operator : tao::pegtl::utf8::one<'='> {};
        struct greater_than_operator : tao::pegtl::utf8::one<'>'> {};
        struct question_mark : tao::pegtl::utf8::one<'?'> {};
        struct left_bracket : tao::pegtl::utf8::one<'['> {};
        struct right_bracket : tao::pegtl::utf8::one<']'> {};
        struct circumflex : tao::pegtl::utf8::one<'^'> {};
        struct underscore : tao::pegtl::utf8::one<'_'> {};
        struct vertical_bar : tao::pegtl::utf8::one<'|'> {};
        struct left_brace : tao::pegtl::utf8::one<'{'> {};
        struct right_brace : tao::pegtl::utf8::one<'}'> {};

        //
        // Character classes
        //

        using alphabetic = tao::pegtl::utf8::icu::alphabetic;
        using ideographic = tao::pegtl::utf8::icu::ideographic;
        using decimal_digit = tao::pegtl::utf8::icu::numeric_type<U_NT_DECIMAL>;

        using u_decimal = tao::pegtl::utf8::icu::numeric_type<U_NT_DECIMAL>;
        using u_digit = tao::pegtl::utf8::icu::numeric_type<U_NT_DIGIT>;
        using u_numeric = tao::pegtl::utf8::icu::numeric_type<U_NT_NUMERIC>;

        struct numeric_character
            : tao::pegtl::sor<u_decimal, u_digit, u_numeric>
        {};

        using non_combining_canonical = tao::pegtl::utf8::icu::canonical_combining_class<0>;
        using non_combining_lead = tao::pegtl::utf8::icu::lead_canonical_combining_class<0>;
        using non_combining_trail = tao::pegtl::utf8::icu::trail_canonical_combining_class<0>;
        struct non_combining
            : tao::pegtl::sor<non_combining_canonical,non_combining_lead,non_combining_trail>
        {};

        struct combining
            : tao::pegtl::seq<tao::pegtl::not_at<non_combining>, tao::pegtl::utf8::any>
        {};

        using excluded_combining = tao::pegtl::utf8::one<0x06DD, 0x06DE, 0x20DD, 0x20DE, 0x20DF, 0x20E0>;

        struct combining_character
            : tao::pegtl::seq<tao::pegtl::not_at<excluded_combining>, combining>
        {};

        struct alternate_underscore
            : tao::pegtl::utf8::one<0xFE33, 0xFE34, 0xFE4D, 0xFE4E, 0xFE4F, 0xFF3F>
        {};

        struct extender_character
            : tao::pegtl::sor<
                tao::pegtl::utf8::one<0x00B7, 0x02D0, 0x02D1, 0x0640, 0x0E46, 0x0EC6, 0x3005>,
                tao::pegtl::utf8::range<0x3031, 0x3035>,
                tao::pegtl::utf8::range<0x309B, 0x309E>,
                tao::pegtl::utf8::range<0x30FC, 0x30FE>,
                tao::pegtl::utf8::one<0xFF70, 0xFF9E, 0xFF9F>>
        {};

        struct connector_character : tao::pegtl::utf8::one<0x203F, 0x2040> {};

        struct identifier_ignorable_character
            : tao::pegtl::sor<
                tao::pegtl::utf8::range<0x200C, 0x200F>,
                tao::pegtl::utf8::range<0x202A, 0x202E>,
                tao::pegtl::utf8::range<0x206A, 0x206FC>,
                tao::pegtl::utf8::one<0xFEFF>>
        {};

        struct initial_alphabetic_character
            : tao::pegtl::sor<alphabetic, underscore>
        {};

        struct ideographic_character : ideographic
        {};

        struct identifier_start
            : tao::pegtl::sor<initial_alphabetic_character, ideographic_character>
        {};

        struct identifier_part
            : tao::pegtl::sor<alphabetic,
                              ideographic_character,
                              decimal_digit,
                              underscore,
                              alternate_underscore,
                              combining_character,
                              extender_character,
                              identifier_ignorable_character,
                              connector_character>
        {};

        struct identifier_body
            : tao::pegtl::seq<identifier_start,
                              tao::pegtl::star<identifier_part>>
        {};

        struct regular_identifier : identifier_body {};

        struct doublequote : tao::pegtl::utf8::one<'"'> {};

        struct non_doublequote_character
            : tao::pegtl::seq<tao::pegtl::not_at<doublequote>, tao::pegtl::utf8::any>
        {};

        struct delimited_identifier_part
            : tao::pegtl::sor<
                non_doublequote_character,
                tao::pegtl::seq<doublequote,doublequote>>
        {};

        struct delimited_identifier
            : tao::pegtl::seq<
                doublequote,
                tao::pegtl::plus<delimited_identifier_part>,
                doublequote>
        {};

        struct actual_identifier
            : tao::pegtl::sor<regular_identifier, delimited_identifier>
        {};

        struct identifier : actual_identifier {};

        struct simple_comment_introducer
            : tao::pegtl::seq<
                tao::pegtl::utf8::one<'-'>,
                tao::pegtl::utf8::one<'-'>>
        {};

        struct nl : tao::pegtl::utf8::one<'\n'> {};
        struct crlf : tao::pegtl::seq<tao::pegtl::utf8::one<'\r'>, tao::pegtl::utf8::one<'\n'>> {};
        struct eolf : tao::pegtl::sor<nl, crlf, tao::pegtl::eof> {};

        struct simple_comment
            : tao::pegtl::seq<
                simple_comment_introducer,
                tao::pegtl::until<eolf>>
        {};

        struct bracketed_comment_introducer
            : tao::pegtl::seq<
                tao::pegtl::utf8::one<'/'>,
                tao::pegtl::utf8::one<'*'>>
        {};

        struct bracketed_comment_terminator
            : tao::pegtl::seq<
                tao::pegtl::utf8::one<'*'>,
                tao::pegtl::utf8::one<'/'>>
        {};

        struct separator;
        struct bracketed_comment_contents
            : tao::pegtl::star<tao::pegtl::sor<separator, tao::pegtl::utf8::any>>
        {};

        struct bracketed_comment
            : tao::pegtl::seq<
                bracketed_comment_introducer,
                bracketed_comment_contents,
                bracketed_comment_terminator>
        {};

        struct comment : tao::pegtl::sor<simple_comment, bracketed_comment> {};

        struct white_space : tao::pegtl::utf8::icu::white_space {};

        struct separator : tao::pegtl::sor<comment, white_space> {};
        struct separators : tao::pegtl::plus<separator> {};

        //
        // Literals
        //

        struct simple_digit : tao::pegtl::utf8::range<'0', '9'> {};

        struct sign : tao::pegtl::sor<plus_sign, minus_sign> {};

        struct unsigned_integer
            : tao::pegtl::plus<simple_digit> {};

        struct signed_integer : tao::pegtl::seq<tao::pegtl::opt<sign>, unsigned_integer> {};

        struct opt_period_opt_unsigned_integer
            : tao::pegtl::opt<tao::pegtl::seq<period, tao::pegtl::opt<unsigned_integer>>> {};

        struct period_unsigned_integer : tao::pegtl::seq<period, unsigned_integer> {};

        struct exact_numeric_literal
            : tao::pegtl::sor<
                tao::pegtl::seq<unsigned_integer, opt_period_opt_unsigned_integer>,
                period_unsigned_integer>
        {};

        struct mantissa : exact_numeric_literal {};

        struct exponent : signed_integer {};

        struct approximate_numeric_literal
            : tao::pegtl::seq<mantissa,
                              tao::pegtl::utf8::one<'E'>,
                              exponent>
        {};

        struct unsigned_numeric_literal : tao::pegtl::sor<exact_numeric_literal, approximate_numeric_literal> {};

        struct signed_numeric_literal
            : tao::pegtl::seq<tao::pegtl::opt<sign>, unsigned_numeric_literal>
        {};

        struct general_literal
            : tao::pegtl::sor<
                character_string_literal,
                national_character_string_literal,
                bit_string_literal,
                hex_string_literal,
                binary_string_literal,
                datetime_literal,
                interval_literal,
                boolean_literal>
        {};

        struct character_string_literal_part
            : tao::pegtl::seq<quote, tao::pegtl::star<character_representation>, quote> {};

        struct character_string_literal
            : tao::pegtl::seq<
                tao::pegtl::opt<introducer, character_set_specification>,
                character_string_literal_part,
                tao::pegtl::star<separator, character_string_literal_part>>
        {};

        struct introducer : underscore {};

        struct character_representation : tao::pegtl::sor<nonquote_character, quote_symbol> {};

        struct nonquote_character : tao::pegtl::seq<tao::pegtl::not_at<quote>, tao::pegtl::utf8::any> {};

        struct quote_symbol : tao::pegtl::seq<quote, quote> {};

        struct literal : tao::pegtl::sor<signed_numeric_literal, general_literal> {};

        struct national_character_string_literal_part
            : tao::pegtl::seq<quote, tao::pegtl::star<character_representation>, quote> {};

        struct national_character_string_literal
            : tao::pegtl::seq<
                tao::pegtl::utf8::one<'N'>,
                national_character_string_literal_part,
                tao::pegtl::star<separator, national_character_string_literal_part>>
        {};

        struct bit_string_literal_part 
            : tao::pegtl::seq<quote, tao::pegtl::star<bit>, quote> {};

        struct bit_string_literal
            : tao::pegtl::seq<
                tao::pegtl::utf8::one<'B'>,
                bit_string_literal_part,
                tao::pegtl::star<separator, bit_string_literal_part>>
        {};

        struct bit : tao::pegtl::utf8::one<'0', '1'> {};

        struct hex_string_literal_part 
            : tao::pegtl::seq<quote, tao::pegtl::star<hexit>, quote> {};

        struct hex_string_literal
            : tao::pegtl::seq<
                tao::pegtl::utf8::one<'X'>,
                hex_string_literal_part,
                tao::pegtl::star<separator, hex_string_literal_part>>
        {};

        struct hexit : tao::pegtl::utf8::ranges<'0', '9', 'A', 'F', 'a', 'f'> {};

        struct binary_string_literal_part 
            : tao::pegtl::seq<quote, tao::pegtl::star<hexit, hexit>, quote> {};

        struct binary_string_literal
            : tao::pegtl::seq<
                tao::pegtl::utf8::one<'X'>,
                binary_string_literal_part,
                tao::pegtl::star<separator, binary_string_literal_part>>
        {};

        struct datetime_literal
            : tao::pegtl::sor<date_literal, time_literal, timestamp_literal>
        {};

        struct date_literal : sseq<keywords::DATE, date_string> {};

        struct date_string : tao::pegtl::seq<quote, unquoted_date_string, quote> {};

        struct date_value
            : tao::pegtl::seq<years_value, minus_sign, months_value, minus_sign, days_value> {};

        struct unquoted_date_string : date_value {};

        struct datetime_value : unsigned_integer {};

        struct years_value : datetime_value {};

        struct months_value : datetime_value {};

        struct days_value : datetime_value {};

        struct time_literal : tao::pegtl::seq<keywords::TIME, time_string> {};

        struct time_string : tao::pegtl::seq<quote, unquoted_time_string, quote> {};

        struct unquoted_time_string : tao::pegtl::seq<time_value, tao::pegtl::opt<time_zone_interval>> {};

        struct time_value : tao::pegtl::seq<hours_value, colon, minutes_value, colon, seconds_value> {};

        struct hours_value : datetime_value {};

        struct minutes_value : datetime_value {};

        struct seconds_value
            : tao::pegtl::seq<
                seconds_integer_value,
                tao::pegtl::opt<period, tao::pegtl::opt<seconds_fraction>>> {};

        struct seconds_integer_value : unsigned_integer {};

        struct seconds_fraction : unsigned_integer {};

        struct time_zone_interval : tao::pegtl::seq<sign, hours_value, colon, minutes_value> {};

        struct timestamp_literal : tao::pegtl::seq<keywords::TIMESTAMP, timestamp_string> {};

        struct timestamp_string : tao::pegtl::seq<quote, unquoted_timestamp_string, quote> {};

        struct unquoted_timestamp_string : tao::pegtl::seq<unquoted_date_string, space, unquoted_time_string> {};

        struct interval_literal
            : tao::pegtl::seq<keywords::INTERVAL, tao::pegtl::opt<sign>, interval_string, interval_qualifier> {};

        struct interval_string : tao::pegtl::seq<quote, unquoted_interval_string, quote> {};

        struct unquoted_interval_string
            : tao::pegtl::seq<tao::pegtl::opt<sign>, tao::pegtl::sor<year_month_literal, day_time_literal>> {};

        struct year_month_literal
            : tao::pegtl::sor<
                tao::pegtl::seq<years_value, colon, months_value>,
                years_value,
                months_value> {};

        struct day_time_literal : tao::pegtl::sor<day_time_interval, time_interval> {};

        struct day_time_interval
            : tao::pegtl::seq<
                days_value,
                tao::pegtl::opt<space, hours_value,
                    tao::pegtl::opt<colon, minutes_value,
                        tao::pegtl::opt<colon, seconds_value>>>
            > {};

        struct time_interval
            : tao::pegtl::sor<
                tao::pegtl::seq<hours_value,
                    tao::pegtl::opt<colon, minutes_value,
                        tao::pegtl::opt<colon, seconds_value>>>,
                tao::pegtl::opt<minutes_value,
                    tao::pegtl::opt<colon, seconds_value>>,
                seconds_value
            > {};

        struct boolean_literal : tao::pegtl::sor<keywords::TRUE_, keywords::FALSE_, keywords::UNKNOWN> {};
    }
    // namespace grammar
}
// namespace squeal

#endif // SQUEAL_GRAMMAR_LEXEMES_HPP
