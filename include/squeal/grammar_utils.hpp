#ifndef SQUEAL_GRAMMAR_UTILS_HPP
#define SQUEAL_GRAMMAR_UTILS_HPP

namespace squeal
{
    namespace grammar
    {
        namespace detail
        {
            template <typename Separator, typename... Rules>
            struct interleaved;

            template <typename Separator, typename Rule0, typename... RulesRest>
            struct interleaved<Separator, Rule0, RulesRest...>
                : tao::pegtl::seq<Rule0, Separator, interleaved<Separator, RulesRest...>> {};

            template <typename Separator, typename Rule0>
            struct interleaved<Separator, Rule0>
                : Rule0 {};

        }
        // namespace detail

        template<typename... Rules>
        using sseq = detail::interleaved<separator, Rules...>;
    }
    // namespace grammar
}
// namespace squeal

#endif // SQUEAL_GRAMMAR_UTILS_HPP
