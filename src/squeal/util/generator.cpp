#include <random>
#include <iostream>
#include <string>

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

    struct NUMERIC : keyword<NUMERIC> { static constexpr const char* name = "NUMERIC"; };
    struct DECIMAL : keyword<DECIMAL> { static constexpr const char* name = "DECIMAL"; };
    struct DEC : keyword<DEC> { static constexpr const char* name = "DEC"; };
    struct INTEGER : keyword<INTEGER> { static constexpr const char* name = "INTEGER"; };
    struct INT : keyword<INT> { static constexpr const char* name = "INT"; };
    struct SMALLINT : keyword<SMALLINT> { static constexpr const char* name = "SMALLINT"; };

    struct kws : disj<NUMERIC, DECIMAL, DEC, INTEGER, INT, SMALLINT> {};

    struct left_paren : keyword<left_paren> { static constexpr const char* name = "("; };
    struct right_paren : keyword<right_paren> { static constexpr const char* name = ")"; };
    struct comma : keyword<comma> { static constexpr const char* name = ","; };

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

#if 0
    struct numeric_type : disj<exact_numeric_type, approximate_numeric_type> {};
#endif

}
// namespace anonymous

int main(int argc, const char* argv[])
{
    std::random_device dev;
    std::mt19937 rng(dev());

    exact_numeric_type::gen(rng, std::cout);

    std::cout << std::endl;

    return 0;
}
