#include "squeal/parser.hpp"

#include <tao/pegtl.hpp>
#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/icu/utf8.hpp>
#include <tao/pegtl/contrib/trace.hpp>

#include "squeal/parser/ast.hpp"

#include "squeal_grammar_fwd_decls.hpp"

namespace squeal
{
    namespace grammar
    {
        namespace keywords
        {
            namespace detail
            {
                template <typename... Rules>
                struct reserved : tao::pegtl::seq<Rules...> {};

                template <typename... Rules>
                struct keyword : tao::pegtl::seq<Rules...> {};
            }
            // namespace detail
        }
        // namespace keywords

        namespace detail
        {
            template <typename Separator, typename... Rules>
            struct interleaved;

            template <typename Separator, typename Rule0, typename... RulesRest>
            struct interleaved<Separator, Rule0, RulesRest...>
                : tao::pegtl::seq<Separator, Rule0, interleaved<Separator, RulesRest...>> {};

            template <typename Separator, typename Rule0>
            struct interleaved<Separator, Rule0>
                : tao::pegtl::seq<Separator, Rule0> {};

            template<typename... Rules>
            using seq = detail::interleaved<separator, Rules...>;

            template<typename... Rules>
            using plus = tao::pegtl::plus<seq<Rules...>>;

            template<typename... Rules>
            using star = tao::pegtl::star<seq<Rules...>>;

            template<typename... Rules>
            using opt = tao::pegtl::opt<seq<Rules...>>;

            template<typename... Rules>
            using sor = tao::pegtl::sor<Rules...>;
        }
        // namespace detail

        struct Ada_host_identifier : tao::pegtl::failure {};

        struct C_host_identifier : tao::pegtl::failure {};

        struct COBOL_host_identifier : tao::pegtl::failure {};

        struct Fortran_host_identifier : tao::pegtl::failure {};

        struct MUMPS_host_identifier : tao::pegtl::failure {};

        struct Pascal_host_identifier : tao::pegtl::failure {};

        struct PL_I_host_identifier : tao::pegtl::failure {};

        struct nondoublequote_character
            : tao::pegtl::seq<tao::pegtl::utf8::not_one<'"'>>
        {};

        struct nonquote_character
            : tao::pegtl::seq<tao::pegtl::utf8::not_one<'\''>>
        {};
    }
    // namespace grammar
}
// namespace squeal

namespace tao
{
    namespace pegtl
    {
        namespace utf8
        {
            namespace icu
            {
                struct decimialdigit : general_category<U_DECIMAL_DIGIT_NUMBER> {};

                struct combining : tao::pegtl::seq<tao::pegtl::not_at<canonical_combining_class<0>>, tao::pegtl::utf8::any> {};
            }
            // namespace icu
        }
        // namespace utf8
    }
    // namespace pegtl
}
// namespace tao
#include "squeal_grammar_main.hpp"

using namespace squeal::parser::ast;

namespace 
{
        struct state
        {
            std::vector<node_ptr> nodes;
        };

        template<typename Rule>
        struct build_ast : tao::pegtl::nothing<Rule> {};

        template<>
        struct build_ast<squeal::grammar::boolean_literal>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                node_ptr p(new boolean_literal_node(p_in.string()));
                p_state.nodes.push_back(p);
            }
        };

        template<>
        struct build_ast<squeal::grammar::character_string_literal_part>
        {
            template<typename ActionInput>
            static void apply(const ActionInput& p_in, state& p_state)
            {
                node_ptr p(new character_string_literal_node(p_in.string()));
                p_state.nodes.push_back(p);
            }
        };
}


namespace squeal
{
    namespace parser
    {
        squeal::parser::ast::node_ptr x(const std::string& p_txt)
        {
            tao::pegtl::string_input in(p_txt, "string");
            state S;
            bool result = tao::pegtl::standard_trace<squeal::grammar::character_string_literal_part, build_ast>(in, S);
            if (!result || S.nodes.size() != 1)
            {
                throw std::runtime_error("parse error");
            }
            return S.nodes[0];
        }

        squeal::parser::ast::node_ptr value_expression(const std::string& p_txt)
        {
            tao::pegtl::string_input in(p_txt, "string");
            state S;
            bool result = tao::pegtl::parse<squeal::grammar::general_literal, build_ast>(in, S);
            if (!result || S.nodes.size() != 1)
            {
                throw std::runtime_error("parse error");
            }
            return S.nodes[0];
        }
    }
    // namespace parser
}
// namespace squeal
