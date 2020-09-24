#include <random>
#include <iostream>
#include <string>

#include "squeal/util/utf8.hpp"

namespace // anonymous
{
    template <typename K>
    struct keyword
    {
        template <typename R>
        static void gen(R& p_rng, std::ostream& p_out)
        {
            p_out << K::name;
        }
    };

    template <int Lo, int Hi>
    struct number
    {
        template <typename R>
        static void gen(R& p_rng, std::ostream& p_out)
        {
            std::uniform_int_distribution<int> U(Lo, Hi);
            int u = U(p_rng);
            p_out << u;
        }
    };

    template <char32_t Lo, char32_t Hi>
    struct unicode
    {
        template <typename R>
        static void gen(R& p_rng, std::ostream& p_out)
        {
            std::uniform_int_distribution<char32_t> U(Lo, Hi);
            char32_t u = U(p_rng);
            std::string s;
            squeal::util::utf8::encoder(s).push_back(u);
            p_out << s;
        }
    };

    template <typename... Ts> struct conj0 {};

    template <>
    struct conj0<>
    {
        template <typename R>
        static void gen(R& p_rng, std::ostream& p_out)
        {
        }
    };

    template <typename T, typename... Ts>
    struct conj0<T, Ts...>
    {
        template <typename R>
        static void gen(R& p_rng, std::ostream& p_out)
        {
            T::gen(p_rng, p_out);
            conj0<Ts...>::gen(p_rng, p_out);
        }
    };

    template <typename... Ts> struct conj {};

    template <>
    struct conj<>
    {
        template <typename R>
        static void gen(R& p_rng, std::ostream& p_out)
        {
        }
    };

    template <typename T, typename... Ts>
    struct conj<T, Ts...>
    {
        template <typename R>
        static void gen(R& p_rng, std::ostream& p_out)
        {
            T::gen(p_rng, p_out);
            p_out << " ";
            conj<Ts...>::gen(p_rng, p_out);
        }
    };

    template <int N, typename... Ts> struct disj0 {};

    template <int N, typename T, typename... Ts>
    struct disj0<N, T, Ts...>
    {
        template <typename R>
        static void gen(int p_n, R& p_rng, std::ostream& p_out)
        {
            if (p_n == N)
            {
                T::gen(p_rng, p_out);
                return;
            }
            disj0<N-1, Ts...>::gen(p_n, p_rng, p_out);
        }
    };

    template <>
    struct disj0<0>
    {
        template <typename R>
        static void gen(int p_n, R& p_rng, std::ostream& p_out)
        {
            throw std::logic_error("disj0");
        }
    };

    template <typename... Ts>
    struct disj
    {
        static constexpr int N = sizeof...(Ts);

        template <typename R>
        static void gen(R& p_rng, std::ostream& p_out)
        {
            std::uniform_int_distribution<int> U(1, N);
            int u = U(p_rng);
            disj0<N, Ts...>::gen(u, p_rng, p_out);
        }
    };

    template <typename... Ts>
    struct opt
    {
        static constexpr int N = sizeof...(Ts);

        template <typename R>
        static void gen(R& p_rng, std::ostream& p_out)
        {
            std::uniform_real_distribution<double> U;
            double u = U(p_rng);
            if (u < 0.5)
            {
                conj<Ts...>::gen(p_rng, p_out);
            }
        }
    };

    template <int P, typename... Ts>
    struct star0
    {
        static constexpr int N = sizeof...(Ts);

        template <typename R>
        static void gen(R& p_rng, std::ostream& p_out)
        {
            const double p = 0.01 * P;
            std::uniform_real_distribution<double> U;
            double u = U(p_rng);
            while (u < p)
            {
                conj0<Ts...>::gen(p_rng, p_out);
                u = U(p_rng);
            }
        }
    };

    template <int P, typename... Ts>
    struct star
    {
        static constexpr int N = sizeof...(Ts);

        template <typename R>
        static void gen(R& p_rng, std::ostream& p_out)
        {
            const double p = 0.01 * P;
            std::uniform_real_distribution<double> U;
            double u = U(p_rng);
            while (u < p)
            {
                conj<Ts...>::gen(p_rng, p_out);
                u = U(p_rng);
            }
        }
    };

    template <int P, typename... Ts>
    struct plus
    {
        static constexpr int N = sizeof...(Ts);

        template <typename R>
        static void gen(R& p_rng, std::ostream& p_out)
        {
            const double p = 0.01 * P;
            std::uniform_real_distribution<double> U;
            while (true)
            {
                conj<Ts...>::gen(p_rng, p_out);
                double u = U(p_rng);
                if (u > p)
                {
                    break;
                }
            }
        }
    };

    struct alphabetic
        : disj<
            unicode<'a', 'z'>,
            unicode<'A', 'Z'>
        >
    {};

    struct ideographic  : unicode<0x4E00, 0x62FF> {};

    struct combining : unicode<0x0300, 0x30F> {};

    struct simple_Latin_upper_case_letter : unicode<'A', 'Z'> {};
    struct simple_Latin_lower_case_letter : unicode<'a', 'z'> {};
    struct simple_Latin_letter : disj<simple_Latin_upper_case_letter, simple_Latin_lower_case_letter> {};

    struct digit : unicode<'0', '9'> {};

    struct underscore : unicode<'_', '_'> {};

    struct identifier_start : disj<alphabetic, ideographic, underscore> {};

    struct identifier_part : disj<alphabetic, ideographic, digit, combining> {};

    struct identifier : conj0<identifier_start, star0<70, identifier_part>> {};

    struct BOOLEAN : keyword<BOOLEAN> { static constexpr const char* name = "BOOLEAN"; };
    struct DATE : keyword<DATE> { static constexpr const char* name = "DATE"; };
    struct DAY : keyword<DAY> { static constexpr const char* name = "DAY"; };
    struct DECIMAL : keyword<DECIMAL> { static constexpr const char* name = "DECIMAL"; };
    struct DEC : keyword<DEC> { static constexpr const char* name = "DEC"; };
    struct DOUBLE : keyword<DOUBLE> { static constexpr const char* name = "DOUBLE"; };
    struct FLOAT : keyword<FLOAT> { static constexpr const char* name = "FLOAT"; };
    struct HOUR : keyword<HOUR> { static constexpr const char* name = "HOUR"; };
    struct INTEGER : keyword<INTEGER> { static constexpr const char* name = "INTEGER"; };
    struct INTERVAL : keyword<INTERVAL> { static constexpr const char* name = "INTERVAL"; };
    struct INT : keyword<INT> { static constexpr const char* name = "INT"; };
    struct MINUTE : keyword<MINUTE> { static constexpr const char* name = "MINUTE"; };
    struct MONTH : keyword<MONTH> { static constexpr const char* name = "MONTH"; };
    struct NUMERIC : keyword<NUMERIC> { static constexpr const char* name = "NUMERIC"; };
    struct PRECISION : keyword<PRECISION> { static constexpr const char* name = "PRECISION"; };
    struct REAL : keyword<REAL> { static constexpr const char* name = "REAL"; };
    struct SECOND : keyword<SECOND> { static constexpr const char* name = "SECOND"; };
    struct SMALLINT : keyword<SMALLINT> { static constexpr const char* name = "SMALLINT"; };
    struct TIME : keyword<TIME> { static constexpr const char* name = "TIME"; };
    struct TIMESTAMP : keyword<TIMESTAMP> { static constexpr const char* name = "TIMESTAMP"; };
    struct TO : keyword<TO> { static constexpr const char* name = "TO"; };
    struct WITH : keyword<WITH> { static constexpr const char* name = "WITH"; };
    struct WITHOUT : keyword<WITHOUT> { static constexpr const char* name = "WITHOUT"; };
    struct YEAR : keyword<YEAR> { static constexpr const char* name = "YEAR"; };
    struct ZONE : keyword<ZONE> { static constexpr const char* name = "ZONE"; };
    struct BIT : keyword<BIT> { static constexpr const char* name = "BIT"; };
    struct VARYING : keyword<VARYING> { static constexpr const char* name = "VARYING"; };
    struct BINARY : keyword<BINARY> { static constexpr const char* name = "BINARY"; };
    struct LARGE : keyword<LARGE> { static constexpr const char* name = "LARGE"; };
    struct OBJECT : keyword<OBJECT> { static constexpr const char* name = "OBJECT"; };
    struct BLOB : keyword<BLOB> { static constexpr const char* name = "BLOB"; };
    struct CHARACTER : keyword<CHARACTER> { static constexpr const char* name = "CHARACTER"; };
    struct CHAR : keyword<CHAR> { static constexpr const char* name = "CHAR"; };
    struct VARCHAR : keyword<VARCHAR> { static constexpr const char* name = "VARCHAR"; };
    struct CLOB : keyword<CLOB> { static constexpr const char* name = "CLOB"; };
    struct K : keyword<K> { static constexpr const char* name = "K"; };
    struct M : keyword<M> { static constexpr const char* name = "M"; };
    struct G : keyword<G> { static constexpr const char* name = "G"; };
    struct SET : keyword<SET> { static constexpr const char* name = "SET"; };

    struct kws : disj<NUMERIC, DECIMAL, DEC, INTEGER, INT, SMALLINT> {};

    struct left_paren : keyword<left_paren> { static constexpr const char* name = "("; };
    struct right_paren : keyword<right_paren> { static constexpr const char* name = ")"; };
    struct comma : keyword<comma> { static constexpr const char* name = ","; };
    struct period : keyword<period> { static constexpr const char* name = "."; };

    struct SQL_language_identifier : BLOB {};

    struct unqualified_schema_name : identifier {};

    struct catalog_name : identifier {};

    struct schema_name : conj<opt<catalog_name, period>, unqualified_schema_name> {};

    struct character_set_name : conj<opt<schema_name, period>, SQL_language_identifier> {};

    struct character_set_specification : character_set_name {};

    struct length : number<100, 200> {};

    struct multiplier : disj<K, M, G> {};

    struct large_object_length : conj<length, opt<multiplier>> {};

    struct character_string_type
        : disj<
            conj<CHARACTER, opt<left_paren, length, right_paren>>,
            conj<CHAR, opt<left_paren, length, right_paren>>,
            conj<CHARACTER, VARYING, left_paren, length, right_paren>,
            conj<CHAR, VARYING, left_paren, length, right_paren>,
            conj<VARCHAR, left_paren, length, right_paren>,
            conj<CHARACTER, LARGE, OBJECT, opt<left_paren, length, right_paren>>,
            conj<CHAR, LARGE, OBJECT, opt<left_paren, large_object_length, right_paren>>,
            conj<CLOB, opt<left_paren, large_object_length, right_paren>>
        >
    {};
    
    struct binary_large_object_string_type
        : disj<
            conj<BINARY, LARGE, OBJECT, opt<left_paren, large_object_length, right_paren>>,
            conj<BLOB, opt<left_paren, large_object_length, right_paren>>
        >
    {};

    struct bit_string_type
        : disj<
            conj<BIT, opt<left_paren, length, right_paren>>,
            conj<BIT, VARYING, left_paren, length, right_paren>
        >
    {};

    struct precision : number<1, 8> {};

    struct scale : number<2, 4> {};

    struct x : conj<NUMERIC, DECIMAL> {};
    struct exact_numeric_type
        : disj<
            conj<NUMERIC, opt<left_paren, precision, opt<comma, scale>, right_paren>>,
            conj<DECIMAL, opt<left_paren, precision, opt<comma, scale>, right_paren>>,
            conj<DEC, opt<left_paren, precision, opt<comma, scale>, right_paren>>,
            INTEGER,
            INT,
            SMALLINT
        >
    {};

    struct approximate_numeric_type
        : disj<
            conj<FLOAT, opt<left_paren, precision, right_paren>>,
            REAL,
            conj<DOUBLE, PRECISION>
        >
    {};

    struct numeric_type : disj<exact_numeric_type, approximate_numeric_type> {};

    struct boolean_type : BOOLEAN {};

    struct time_fractional_seconds_precision : number<0, 6> {};

    struct time_precision : time_fractional_seconds_precision {};

    struct timestamp_precision : time_fractional_seconds_precision {};

    struct with_or_without_time_zone
        : disj<
            conj<WITH, TIME, ZONE>,
            conj<WITHOUT, TIME, ZONE>
        >
    {};

    struct datetime_type
        : disj<
            DATE,
            conj<TIME, opt<left_paren, time_precision, right_paren>, opt<with_or_without_time_zone>>,
            conj<TIMESTAMP, opt<left_paren, timestamp_precision, right_paren>, opt<with_or_without_time_zone>>
        >
    {};

    struct non_second_primary_datetime_field
        : disj<
            YEAR, MONTH, DAY, HOUR, MINUTE
        >
    {};

    struct interval_leading_field_precision : number<0, 6> {};

    struct start_field
        : conj<
            non_second_primary_datetime_field,
            opt<left_paren, interval_leading_field_precision, right_paren>
        >
    {};

    struct interval_fractional_seconds_precision : number<1, 5> {};

    struct end_field
        : disj<
            non_second_primary_datetime_field,
            conj<SECOND, opt<left_paren, interval_fractional_seconds_precision, right_paren>>
        >
    {};

    struct single_datetime_field
        : disj<
            conj<non_second_primary_datetime_field, opt<left_paren, interval_leading_field_precision, right_paren>>,
            conj<SECOND,
                opt<left_paren, interval_leading_field_precision,
                    opt<comma, interval_fractional_seconds_precision>,
                    right_paren>>
        >
    {};

    struct interval_qualifier
        : disj<
            conj<start_field, TO, end_field>,
            single_datetime_field
        >
    {};

    struct interval_type
        : conj<
            INTERVAL, interval_qualifier
        >
    {};

    struct predefined_type
        : disj<
            conj<character_string_type, opt<CHARACTER, SET, character_set_specification>>,
            binary_large_object_string_type,
            bit_string_type,
            numeric_type,
            boolean_type,
            datetime_type,
            interval_type
        >
    {};
}
// namespace anonymous

int main(int argc, const char* argv[])
{
    std::random_device dev;
    std::mt19937 rng(dev());

    identifier::gen(rng, std::cout);

    std::cout << std::endl;

    return 0;
}
