#include "squeal/parser.hpp"

#include <deque>

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/icu/utf8.hpp>
#include <tao/pegtl/contrib/trace.hpp>
#include <tao/pegtl/contrib/parse_tree.hpp>
#include <tao/pegtl/contrib/parse_tree_to_dot.hpp>

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
                struct reserved : tao::pegtl::seq<Rules..., tao::pegtl::not_at<identifier_part>> {};

                template <typename... Rules>
                struct keyword : tao::pegtl::seq<Rules..., tao::pegtl::not_at<identifier_part>> {};
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
            using seq = detail::interleaved<tao::pegtl::opt<separator>, Rules...>;

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

namespace 
{
    template< typename Rule > struct blacklist : std::true_type {};

    template <typename... Rules>
    struct blacklist<tao::pegtl::seq<Rules...>> : std::false_type {};
    template <typename... Rules>
    struct blacklist<tao::pegtl::sor<Rules...>> : std::false_type {};
    template <typename... Rules>
    struct blacklist<tao::pegtl::opt<Rules...>> : std::false_type {};
    template <typename... Rules>
    struct blacklist<tao::pegtl::star<Rules...>> : std::false_type {};
    template <typename... Rules>
    struct blacklist<tao::pegtl::plus<Rules...>> : std::false_type {};
    template <typename... Rules>
    struct blacklist<tao::pegtl::not_at<Rules...>> : std::false_type {};
    template <typename... Rules>
    struct blacklist<squeal::grammar::detail::interleaved<Rules...>> : std::false_type {};

    template <char32_t... Cs>
    struct blacklist<tao::pegtl::utf8::not_one<Cs...>> : std::false_type {};

    template<> struct blacklist<tao::pegtl::utf8::icu::alphabetic>  : std::false_type {};

#include "squeal_grammar_blacklist.hpp"

    template<> struct blacklist<squeal::grammar::keywords::detail::A>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::B>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::C>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::D>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::E>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::F>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::G>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::H>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::I>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::J>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::K>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::L>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::M>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::N>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::O>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::P>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::Q>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::R>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::S>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::T>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::U>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::V>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::W>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::X>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::Y>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::Z>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::hypen>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::detail::underscore>  : std::false_type {};

    template<> struct blacklist<squeal::grammar::keywords::FALSE_>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::FROM>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::SELECT>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::TRUE_>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::UNKNOWN>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::keywords::WHERE>  : std::false_type {};

    template<> struct blacklist<squeal::grammar::SQL_language_identifier_start>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::simple_Latin_upper_case_letter>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::simple_Latin_lower_case_letter>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::alphabetic_character>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::bracketed_comment_contents>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::bracketed_comment_introducer>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::bracketed_comment>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::bracketed_comment_terminator>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::connector_character>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::decimal_digit_character>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::digit>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::double_quote>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::escape_character>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::escaped_character>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::extender_character>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::identifier_body>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::identifier_combining_character>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::identifier_ignorable_character>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::ideographic_character>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::initial_alphabetic_character>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::introducer>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::nondoublequote_character>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::non_escaped_character>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::nonquote_character>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::quote>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::quote_symbol>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::regular_identifier>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::separator>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::simple_comment_introducer>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::simple_comment>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::trim_character>  : std::false_type {};
    template<> struct blacklist<squeal::grammar::white_space>  : std::false_type {};

    template <typename NodeType>
    squeal::parser::ast::node_ptr mkAst(const NodeType& p_node)
    {
        std::string type(p_node->type.begin(), p_node->type.end());;
        if (p_node->children.empty())
        {
            squeal::parser::ast::node_ptr p(new squeal::parser::ast::atom_node(p_node->string()));
            return squeal::parser::ast::object_node::singleton(type, p);
        }
        std::vector<squeal::parser::ast::node_ptr> ns;
        for (auto& child_ptr : p_node->children)
        {
            ns.push_back(mkAst(child_ptr));
        }
        squeal::parser::ast::node_ptr p(new squeal::parser::ast::array_node(ns));
        return squeal::parser::ast::object_node::singleton(type, p);
    }
}


namespace squeal
{
    namespace parser
    {
        squeal::parser::ast::node_ptr x(const std::string& p_txt)
        {
            tao::pegtl::string_input in(p_txt, "string");
            auto root = tao::pegtl::parse_tree::parse<squeal::grammar::general_literal, blacklist>( in );
            if (root)
            {
                return mkAst(root);
            }
            return squeal::parser::ast::node_ptr();
        }

        squeal::parser::ast::node_ptr literal(const std::string& p_txt)
        {
            tao::pegtl::string_input in(p_txt, "string");
            auto root = tao::pegtl::parse_tree::parse<squeal::grammar::literal, blacklist>( in );
            if (root)
            {
                return mkAst(root);
            }
            return squeal::parser::ast::node_ptr();
        }

        squeal::parser::ast::node_ptr query_specification(const std::string& p_txt, bool p_trace)
        {
            if (p_trace)
            {
                tao::pegtl::string_input in(p_txt, "string");
                tao::pegtl::standard_trace<squeal::grammar::query_specification, blacklist>( in );
            }
            tao::pegtl::string_input in(p_txt, "string");
            auto root = tao::pegtl::parse_tree::parse<squeal::grammar::query_specification, blacklist>( in );
            if (root)
            {
                return mkAst(root);
            }
            return squeal::parser::ast::node_ptr();
        }

        squeal::parser::ast::node_ptr value_expression(const std::string& p_txt)
        {
            tao::pegtl::string_input in(p_txt, "string");
            auto root = tao::pegtl::parse_tree::parse<squeal::grammar::value_expression, blacklist>( in );
            if (root)
            {
                return mkAst(root);
            }
            return squeal::parser::ast::node_ptr();
        }
    }
    // namespace parser
}
// namespace squeal
