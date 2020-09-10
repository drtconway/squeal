#ifndef SQUEAL_GRAMMAR_KEYWORDS_HPP
#define SQUEAL_GRAMMAR_KEYWORDS_HPP

namespace squeal
{
    namespace grammar
    {
        namespace keywords
        {

            namespace ch
            {
                struct A : tao::pegtl::utf8::one<'A', 'a'> {};
                struct B : tao::pegtl::utf8::one<'B', 'b'> {};
                struct C : tao::pegtl::utf8::one<'C', 'c'> {};
                struct D : tao::pegtl::utf8::one<'D', 'd'> {};
                struct E : tao::pegtl::utf8::one<'E', 'e'> {};
                struct F : tao::pegtl::utf8::one<'F', 'f'> {};
                struct G : tao::pegtl::utf8::one<'G', 'g'> {};
                struct H : tao::pegtl::utf8::one<'H', 'h'> {};
                struct I : tao::pegtl::utf8::one<'I', 'i'> {};
                struct J : tao::pegtl::utf8::one<'J', 'j'> {};
                struct K : tao::pegtl::utf8::one<'K', 'k'> {};
                struct L : tao::pegtl::utf8::one<'L', 'l'> {};
                struct M : tao::pegtl::utf8::one<'M', 'm'> {};
                struct N : tao::pegtl::utf8::one<'N', 'n'> {};
                struct O : tao::pegtl::utf8::one<'O', 'o'> {};
                struct P : tao::pegtl::utf8::one<'P', 'p'> {};
                struct Q : tao::pegtl::utf8::one<'Q', 'q'> {};
                struct R : tao::pegtl::utf8::one<'R', 'r'> {};
                struct S : tao::pegtl::utf8::one<'S', 's'> {};
                struct T : tao::pegtl::utf8::one<'T', 't'> {};
                struct U : tao::pegtl::utf8::one<'U', 'u'> {};
                struct V : tao::pegtl::utf8::one<'V', 'v'> {};
                struct W : tao::pegtl::utf8::one<'W', 'w'> {};
                struct X : tao::pegtl::utf8::one<'X', 'x'> {};
                struct Y : tao::pegtl::utf8::one<'Y', 'y'> {};
                struct Z : tao::pegtl::utf8::one<'Z', 'z'> {};
                struct _ : tao::pegtl::utf8::one<'_'> {};
                struct hyphen : tao::pegtl::utf8::one<'-'> {};
            }
            // namespace ch
            struct ABS : tao::pegtl::seq<ch::A, ch::B, ch::S> {};
            struct ABSOLUTE : tao::pegtl::seq<ch::A, ch::B, ch::S, ch::O, ch::L, ch::U, ch::T, ch::E> {};
            struct ACTION : tao::pegtl::seq<ch::A, ch::C, ch::T, ch::I, ch::O, ch::N> {};
            struct ADA : tao::pegtl::seq<ch::A, ch::D, ch::A> {};
            struct ADD : tao::pegtl::seq<ch::A, ch::D, ch::D> {};
            struct ADMIN : tao::pegtl::seq<ch::A, ch::D, ch::M, ch::I, ch::N> {};
            struct AFTER : tao::pegtl::seq<ch::A, ch::F, ch::T, ch::E, ch::R> {};
            struct ALL : tao::pegtl::seq<ch::A, ch::L, ch::L> {};
            struct ALLOCATE : tao::pegtl::seq<ch::A, ch::L, ch::L, ch::O, ch::C, ch::A, ch::T, ch::E> {};
            struct ALTER : tao::pegtl::seq<ch::A, ch::L, ch::T, ch::E, ch::R> {};
            struct AND : tao::pegtl::seq<ch::A, ch::N, ch::D> {};
            struct ANY : tao::pegtl::seq<ch::A, ch::N, ch::Y> {};
            struct ARE : tao::pegtl::seq<ch::A, ch::R, ch::E> {};
            struct ARRAY : tao::pegtl::seq<ch::A, ch::R, ch::R, ch::A, ch::Y> {};
            struct AS : tao::pegtl::seq<ch::A, ch::S> {};
            struct ASC : tao::pegtl::seq<ch::A, ch::S, ch::C> {};
            struct ASENSITIVE : tao::pegtl::seq<ch::A, ch::S, ch::E, ch::N, ch::S, ch::I, ch::T, ch::I, ch::V, ch::E> {};
            struct ASSERTION : tao::pegtl::seq<ch::A, ch::S, ch::S, ch::E, ch::R, ch::T, ch::I, ch::O, ch::N> {};
            struct ASSIGNMENT : tao::pegtl::seq<ch::A, ch::S, ch::S, ch::I, ch::G, ch::N, ch::M, ch::E, ch::N, ch::T> {};
            struct ASYMMETRIC : tao::pegtl::seq<ch::A, ch::S, ch::Y, ch::M, ch::M, ch::E, ch::T, ch::R, ch::I, ch::C> {};
            struct AT : tao::pegtl::seq<ch::A, ch::T> {};
            struct ATOMIC : tao::pegtl::seq<ch::A, ch::T, ch::O, ch::M, ch::I, ch::C> {};
            struct ATTRIBUTE : tao::pegtl::seq<ch::A, ch::T, ch::T, ch::R, ch::I, ch::B, ch::U, ch::T, ch::E> {};
            struct AUTHORIZATION : tao::pegtl::seq<ch::A, ch::U, ch::T, ch::H, ch::O, ch::R, ch::I, ch::Z, ch::A, ch::T, ch::I, ch::O, ch::N> {};
            struct AVG : tao::pegtl::seq<ch::A, ch::V, ch::G> {};
            struct BEFORE : tao::pegtl::seq<ch::B, ch::E, ch::F, ch::O, ch::R, ch::E> {};
            struct BEGIN : tao::pegtl::seq<ch::B, ch::E, ch::G, ch::I, ch::N> {};
            struct BETWEEN : tao::pegtl::seq<ch::B, ch::E, ch::T, ch::W, ch::E, ch::E, ch::N> {};
            struct BINARY : tao::pegtl::seq<ch::B, ch::I, ch::N, ch::A, ch::R, ch::Y> {};
            struct BIT : tao::pegtl::seq<ch::B, ch::I, ch::T> {};
            struct BIT_LENGTH : tao::pegtl::seq<ch::B, ch::I, ch::T, ch::_, ch::L, ch::E, ch::N, ch::G, ch::T, ch::H> {};
            struct BLOB : tao::pegtl::seq<ch::B, ch::L, ch::O, ch::B> {};
            struct BOOLEAN : tao::pegtl::seq<ch::B, ch::O, ch::O, ch::L, ch::E, ch::A, ch::N> {};
            struct BOTH : tao::pegtl::seq<ch::B, ch::O, ch::T, ch::H> {};
            struct BREADTH : tao::pegtl::seq<ch::B, ch::R, ch::E, ch::A, ch::D, ch::T, ch::H> {};
            struct BY : tao::pegtl::seq<ch::B, ch::Y> {};
            struct C : tao::pegtl::seq<ch::C> {};
            struct CALL : tao::pegtl::seq<ch::C, ch::A, ch::L, ch::L> {};
            struct CALLED : tao::pegtl::seq<ch::C, ch::A, ch::L, ch::L, ch::E, ch::D> {};
            struct CARDINALITY : tao::pegtl::seq<ch::C, ch::A, ch::R, ch::D, ch::I, ch::N, ch::A, ch::L, ch::I, ch::T, ch::Y> {};
            struct CASCADE : tao::pegtl::seq<ch::C, ch::A, ch::S, ch::C, ch::A, ch::D, ch::E> {};
            struct CASCADED : tao::pegtl::seq<ch::C, ch::A, ch::S, ch::C, ch::A, ch::D, ch::E, ch::D> {};
            struct CASE : tao::pegtl::seq<ch::C, ch::A, ch::S, ch::E> {};
            struct CAST : tao::pegtl::seq<ch::C, ch::A, ch::S, ch::T> {};
            struct CATALOG : tao::pegtl::seq<ch::C, ch::A, ch::T, ch::A, ch::L, ch::O, ch::G> {};
            struct CATALOG_NAME : tao::pegtl::seq<ch::C, ch::A, ch::T, ch::A, ch::L, ch::O, ch::G, ch::_, ch::N, ch::A, ch::M, ch::E> {};
            struct CHAIN : tao::pegtl::seq<ch::C, ch::H, ch::A, ch::I, ch::N> {};
            struct CHAR : tao::pegtl::seq<ch::C, ch::H, ch::A, ch::R> {};
            struct CHARACTER : tao::pegtl::seq<ch::C, ch::H, ch::A, ch::R, ch::A, ch::C, ch::T, ch::E, ch::R> {};
            struct CHARACTERISTICS : tao::pegtl::seq<ch::C, ch::H, ch::A, ch::R, ch::A, ch::C, ch::T, ch::E, ch::R, ch::I, ch::S, ch::T, ch::I, ch::C, ch::S> {};
            struct CHARACTER_LENGTH : tao::pegtl::seq<ch::C, ch::H, ch::A, ch::R, ch::A, ch::C, ch::T, ch::E, ch::R, ch::_, ch::L, ch::E, ch::N, ch::G, ch::T, ch::H> {};
            struct CHARACTER_SET_CATALOG : tao::pegtl::seq<ch::C, ch::H, ch::A, ch::R, ch::A, ch::C, ch::T, ch::E, ch::R, ch::_, ch::S, ch::E, ch::T, ch::_, ch::C, ch::A, ch::T, ch::A, ch::L, ch::O, ch::G> {};
            struct CHARACTER_SET_NAME : tao::pegtl::seq<ch::C, ch::H, ch::A, ch::R, ch::A, ch::C, ch::T, ch::E, ch::R, ch::_, ch::S, ch::E, ch::T, ch::_, ch::N, ch::A, ch::M, ch::E> {};
            struct CHARACTER_SET_SCHEMA : tao::pegtl::seq<ch::C, ch::H, ch::A, ch::R, ch::A, ch::C, ch::T, ch::E, ch::R, ch::_, ch::S, ch::E, ch::T, ch::_, ch::S, ch::C, ch::H, ch::E, ch::M, ch::A> {};
            struct CHAR_LENGTH : tao::pegtl::seq<ch::C, ch::H, ch::A, ch::R, ch::_, ch::L, ch::E, ch::N, ch::G, ch::T, ch::H> {};
            struct CHECK : tao::pegtl::seq<ch::C, ch::H, ch::E, ch::C, ch::K> {};
            struct CHECKED : tao::pegtl::seq<ch::C, ch::H, ch::E, ch::C, ch::K, ch::E, ch::D> {};
            struct CLASS_ORIGIN : tao::pegtl::seq<ch::C, ch::L, ch::A, ch::S, ch::S, ch::_, ch::O, ch::R, ch::I, ch::G, ch::I, ch::N> {};
            struct CLOB : tao::pegtl::seq<ch::C, ch::L, ch::O, ch::B> {};
            struct CLOSE : tao::pegtl::seq<ch::C, ch::L, ch::O, ch::S, ch::E> {};
            struct COALESCE : tao::pegtl::seq<ch::C, ch::O, ch::A, ch::L, ch::E, ch::S, ch::C, ch::E> {};
            struct COBOL : tao::pegtl::seq<ch::C, ch::O, ch::B, ch::O, ch::L> {};
            struct COLLATE : tao::pegtl::seq<ch::C, ch::O, ch::L, ch::L, ch::A, ch::T, ch::E> {};
            struct COLLATION : tao::pegtl::seq<ch::C, ch::O, ch::L, ch::L, ch::A, ch::T, ch::I, ch::O, ch::N> {};
            struct COLLATION_CATALOG : tao::pegtl::seq<ch::C, ch::O, ch::L, ch::L, ch::A, ch::T, ch::I, ch::O, ch::N, ch::_, ch::C, ch::A, ch::T, ch::A, ch::L, ch::O, ch::G> {};
            struct COLLATION_NAME : tao::pegtl::seq<ch::C, ch::O, ch::L, ch::L, ch::A, ch::T, ch::I, ch::O, ch::N, ch::_, ch::N, ch::A, ch::M, ch::E> {};
            struct COLLATION_SCHEMA : tao::pegtl::seq<ch::C, ch::O, ch::L, ch::L, ch::A, ch::T, ch::I, ch::O, ch::N, ch::_, ch::S, ch::C, ch::H, ch::E, ch::M, ch::A> {};
            struct COLUMN : tao::pegtl::seq<ch::C, ch::O, ch::L, ch::U, ch::M, ch::N> {};
            struct COLUMN_NAME : tao::pegtl::seq<ch::C, ch::O, ch::L, ch::U, ch::M, ch::N, ch::_, ch::N, ch::A, ch::M, ch::E> {};
            struct COMMAND_FUNCTION : tao::pegtl::seq<ch::C, ch::O, ch::M, ch::M, ch::A, ch::N, ch::D, ch::_, ch::F, ch::U, ch::N, ch::C, ch::T, ch::I, ch::O, ch::N> {};
            struct COMMAND_FUNCTION_CODE : tao::pegtl::seq<ch::C, ch::O, ch::M, ch::M, ch::A, ch::N, ch::D, ch::_, ch::F, ch::U, ch::N, ch::C, ch::T, ch::I, ch::O, ch::N, ch::_, ch::C, ch::O, ch::D, ch::E> {};
            struct COMMIT : tao::pegtl::seq<ch::C, ch::O, ch::M, ch::M, ch::I, ch::T> {};
            struct COMMITTED : tao::pegtl::seq<ch::C, ch::O, ch::M, ch::M, ch::I, ch::T, ch::T, ch::E, ch::D> {};
            struct CONDITION : tao::pegtl::seq<ch::C, ch::O, ch::N, ch::D, ch::I, ch::T, ch::I, ch::O, ch::N> {};
            struct CONDITION_IDENTIFIER : tao::pegtl::seq<ch::C, ch::O, ch::N, ch::D, ch::I, ch::T, ch::I, ch::O, ch::N, ch::_, ch::I, ch::D, ch::E, ch::N, ch::T, ch::I, ch::F, ch::I, ch::E, ch::R> {};
            struct CONDITION_NUMBER : tao::pegtl::seq<ch::C, ch::O, ch::N, ch::D, ch::I, ch::T, ch::I, ch::O, ch::N, ch::_, ch::N, ch::U, ch::M, ch::B, ch::E, ch::R> {};
            struct CONNECT : tao::pegtl::seq<ch::C, ch::O, ch::N, ch::N, ch::E, ch::C, ch::T> {};
            struct CONNECTION : tao::pegtl::seq<ch::C, ch::O, ch::N, ch::N, ch::E, ch::C, ch::T, ch::I, ch::O, ch::N> {};
            struct CONNECTION_NAME : tao::pegtl::seq<ch::C, ch::O, ch::N, ch::N, ch::E, ch::C, ch::T, ch::I, ch::O, ch::N, ch::_, ch::N, ch::A, ch::M, ch::E> {};
            struct CONSTRAINT : tao::pegtl::seq<ch::C, ch::O, ch::N, ch::S, ch::T, ch::R, ch::A, ch::I, ch::N, ch::T> {};
            struct CONSTRAINTS : tao::pegtl::seq<ch::C, ch::O, ch::N, ch::S, ch::T, ch::R, ch::A, ch::I, ch::N, ch::T, ch::S> {};
            struct CONSTRAINT_CATALOG : tao::pegtl::seq<ch::C, ch::O, ch::N, ch::S, ch::T, ch::R, ch::A, ch::I, ch::N, ch::T, ch::_, ch::C, ch::A, ch::T, ch::A, ch::L, ch::O, ch::G> {};
            struct CONSTRAINT_NAME : tao::pegtl::seq<ch::C, ch::O, ch::N, ch::S, ch::T, ch::R, ch::A, ch::I, ch::N, ch::T, ch::_, ch::N, ch::A, ch::M, ch::E> {};
            struct CONSTRAINT_SCHEMA : tao::pegtl::seq<ch::C, ch::O, ch::N, ch::S, ch::T, ch::R, ch::A, ch::I, ch::N, ch::T, ch::_, ch::S, ch::C, ch::H, ch::E, ch::M, ch::A> {};
            struct CONSTRUCTOR : tao::pegtl::seq<ch::C, ch::O, ch::N, ch::S, ch::T, ch::R, ch::U, ch::C, ch::T, ch::O, ch::R> {};
            struct CONTAINS : tao::pegtl::seq<ch::C, ch::O, ch::N, ch::T, ch::A, ch::I, ch::N, ch::S> {};
            struct CONTINUE : tao::pegtl::seq<ch::C, ch::O, ch::N, ch::T, ch::I, ch::N, ch::U, ch::E> {};
            struct CONVERT : tao::pegtl::seq<ch::C, ch::O, ch::N, ch::V, ch::E, ch::R, ch::T> {};
            struct CORRESPONDING : tao::pegtl::seq<ch::C, ch::O, ch::R, ch::R, ch::E, ch::S, ch::P, ch::O, ch::N, ch::D, ch::I, ch::N, ch::G> {};
            struct COUNT : tao::pegtl::seq<ch::C, ch::O, ch::U, ch::N, ch::T> {};
            struct CREATE : tao::pegtl::seq<ch::C, ch::R, ch::E, ch::A, ch::T, ch::E> {};
            struct CROSS : tao::pegtl::seq<ch::C, ch::R, ch::O, ch::S, ch::S> {};
            struct CUBE : tao::pegtl::seq<ch::C, ch::U, ch::B, ch::E> {};
            struct CURRENT : tao::pegtl::seq<ch::C, ch::U, ch::R, ch::R, ch::E, ch::N, ch::T> {};
            struct CURRENT_DATE : tao::pegtl::seq<ch::C, ch::U, ch::R, ch::R, ch::E, ch::N, ch::T, ch::_, ch::D, ch::A, ch::T, ch::E> {};
            struct CURRENT_DEFAULT_TRANSFORM_GROUP : tao::pegtl::seq<ch::C, ch::U, ch::R, ch::R, ch::E, ch::N, ch::T, ch::_, ch::D, ch::E, ch::F, ch::A, ch::U, ch::L, ch::T, ch::_, ch::T, ch::R, ch::A, ch::N, ch::S, ch::F, ch::O, ch::R, ch::M, ch::_, ch::G, ch::R, ch::O, ch::U, ch::P> {};
            struct CURRENT_PATH : tao::pegtl::seq<ch::C, ch::U, ch::R, ch::R, ch::E, ch::N, ch::T, ch::_, ch::P, ch::A, ch::T, ch::H> {};
            struct CURRENT_ROLE : tao::pegtl::seq<ch::C, ch::U, ch::R, ch::R, ch::E, ch::N, ch::T, ch::_, ch::R, ch::O, ch::L, ch::E> {};
            struct CURRENT_TIME : tao::pegtl::seq<ch::C, ch::U, ch::R, ch::R, ch::E, ch::N, ch::T, ch::_, ch::T, ch::I, ch::M, ch::E> {};
            struct CURRENT_TIMESTAMP : tao::pegtl::seq<ch::C, ch::U, ch::R, ch::R, ch::E, ch::N, ch::T, ch::_, ch::T, ch::I, ch::M, ch::E, ch::S, ch::T, ch::A, ch::M, ch::P> {};
            struct CURRENT_TRANSFORM_GROUP_FOR_TYPE : tao::pegtl::seq<ch::C, ch::U, ch::R, ch::R, ch::E, ch::N, ch::T, ch::_, ch::T, ch::R, ch::A, ch::N, ch::S, ch::F, ch::O, ch::R, ch::M, ch::_, ch::G, ch::R, ch::O, ch::U, ch::P, ch::_, ch::F, ch::O, ch::R, ch::_, ch::T, ch::Y, ch::P, ch::E> {};
            struct CURRENT_USER : tao::pegtl::seq<ch::C, ch::U, ch::R, ch::R, ch::E, ch::N, ch::T, ch::_, ch::U, ch::S, ch::E, ch::R> {};
            struct CURSOR : tao::pegtl::seq<ch::C, ch::U, ch::R, ch::S, ch::O, ch::R> {};
            struct CURSOR_NAME : tao::pegtl::seq<ch::C, ch::U, ch::R, ch::S, ch::O, ch::R, ch::_, ch::N, ch::A, ch::M, ch::E> {};
            struct CYCLE : tao::pegtl::seq<ch::C, ch::Y, ch::C, ch::L, ch::E> {};
            struct DATA : tao::pegtl::seq<ch::D, ch::A, ch::T, ch::A> {};
            struct DATE : tao::pegtl::seq<ch::D, ch::A, ch::T, ch::E> {};
            struct DATETIME_INTERVAL_CODE : tao::pegtl::seq<ch::D, ch::A, ch::T, ch::E, ch::T, ch::I, ch::M, ch::E, ch::_, ch::I, ch::N, ch::T, ch::E, ch::R, ch::V, ch::A, ch::L, ch::_, ch::C, ch::O, ch::D, ch::E> {};
            struct DATETIME_INTERVAL_PRECISION : tao::pegtl::seq<ch::D, ch::A, ch::T, ch::E, ch::T, ch::I, ch::M, ch::E, ch::_, ch::I, ch::N, ch::T, ch::E, ch::R, ch::V, ch::A, ch::L, ch::_, ch::P, ch::R, ch::E, ch::C, ch::I, ch::S, ch::I, ch::O, ch::N> {};
            struct DAY : tao::pegtl::seq<ch::D, ch::A, ch::Y> {};
            struct DEALLOCATE : tao::pegtl::seq<ch::D, ch::E, ch::A, ch::L, ch::L, ch::O, ch::C, ch::A, ch::T, ch::E> {};
            struct DEC : tao::pegtl::seq<ch::D, ch::E, ch::C> {};
            struct DECIMAL : tao::pegtl::seq<ch::D, ch::E, ch::C, ch::I, ch::M, ch::A, ch::L> {};
            struct DECLARE : tao::pegtl::seq<ch::D, ch::E, ch::C, ch::L, ch::A, ch::R, ch::E> {};
            struct DEFAULT : tao::pegtl::seq<ch::D, ch::E, ch::F, ch::A, ch::U, ch::L, ch::T> {};
            struct DEFERRABLE : tao::pegtl::seq<ch::D, ch::E, ch::F, ch::E, ch::R, ch::R, ch::A, ch::B, ch::L, ch::E> {};
            struct DEFERRED : tao::pegtl::seq<ch::D, ch::E, ch::F, ch::E, ch::R, ch::R, ch::E, ch::D> {};
            struct DEFINED : tao::pegtl::seq<ch::D, ch::E, ch::F, ch::I, ch::N, ch::E, ch::D> {};
            struct DEFINER : tao::pegtl::seq<ch::D, ch::E, ch::F, ch::I, ch::N, ch::E, ch::R> {};
            struct DEGREE : tao::pegtl::seq<ch::D, ch::E, ch::G, ch::R, ch::E, ch::E> {};
            struct DELETE : tao::pegtl::seq<ch::D, ch::E, ch::L, ch::E, ch::T, ch::E> {};
            struct DEPTH : tao::pegtl::seq<ch::D, ch::E, ch::P, ch::T, ch::H> {};
            struct DEREF : tao::pegtl::seq<ch::D, ch::E, ch::R, ch::E, ch::F> {};
            struct DERIVED : tao::pegtl::seq<ch::D, ch::E, ch::R, ch::I, ch::V, ch::E, ch::D> {};
            struct DESC : tao::pegtl::seq<ch::D, ch::E, ch::S, ch::C> {};
            struct DESCRIBE : tao::pegtl::seq<ch::D, ch::E, ch::S, ch::C, ch::R, ch::I, ch::B, ch::E> {};
            struct DESCRIPTOR : tao::pegtl::seq<ch::D, ch::E, ch::S, ch::C, ch::R, ch::I, ch::P, ch::T, ch::O, ch::R> {};
            struct DETERMINISTIC : tao::pegtl::seq<ch::D, ch::E, ch::T, ch::E, ch::R, ch::M, ch::I, ch::N, ch::I, ch::S, ch::T, ch::I, ch::C> {};
            struct DIAGNOSTICS : tao::pegtl::seq<ch::D, ch::I, ch::A, ch::G, ch::N, ch::O, ch::S, ch::T, ch::I, ch::C, ch::S> {};
            struct DISCONNECT : tao::pegtl::seq<ch::D, ch::I, ch::S, ch::C, ch::O, ch::N, ch::N, ch::E, ch::C, ch::T> {};
            struct DISPATCH : tao::pegtl::seq<ch::D, ch::I, ch::S, ch::P, ch::A, ch::T, ch::C, ch::H> {};
            struct DISTINCT : tao::pegtl::seq<ch::D, ch::I, ch::S, ch::T, ch::I, ch::N, ch::C, ch::T> {};
            struct DO : tao::pegtl::seq<ch::D, ch::O> {};
            struct DOMAIN : tao::pegtl::seq<ch::D, ch::O, ch::M, ch::A, ch::I, ch::N> {};
            struct DOUBLE : tao::pegtl::seq<ch::D, ch::O, ch::U, ch::B, ch::L, ch::E> {};
            struct DROP : tao::pegtl::seq<ch::D, ch::R, ch::O, ch::P> {};
            struct DYNAMIC : tao::pegtl::seq<ch::D, ch::Y, ch::N, ch::A, ch::M, ch::I, ch::C> {};
            struct EACH : tao::pegtl::seq<ch::E, ch::A, ch::C, ch::H> {};
            struct ELSE : tao::pegtl::seq<ch::E, ch::L, ch::S, ch::E> {};
            struct ELSEIF : tao::pegtl::seq<ch::E, ch::L, ch::S, ch::E, ch::I, ch::F> {};
            struct END : tao::pegtl::seq<ch::E, ch::N, ch::D> {};
            struct END_EXEC : tao::pegtl::seq<ch::E, ch::N, ch::D, ch::hyphen, ch::E, ch::X, ch::E, ch::C> {};
            struct EQUALS : tao::pegtl::seq<ch::E, ch::Q, ch::U, ch::A, ch::L, ch::S> {};
            struct ESCAPE : tao::pegtl::seq<ch::E, ch::S, ch::C, ch::A, ch::P, ch::E> {};
            struct EVERY : tao::pegtl::seq<ch::E, ch::V, ch::E, ch::R, ch::Y> {};
            struct EXCEPT : tao::pegtl::seq<ch::E, ch::X, ch::C, ch::E, ch::P, ch::T> {};
            struct EXCEPTION : tao::pegtl::seq<ch::E, ch::X, ch::C, ch::E, ch::P, ch::T, ch::I, ch::O, ch::N> {};
            struct EXEC : tao::pegtl::seq<ch::E, ch::X, ch::E, ch::C> {};
            struct EXECUTE : tao::pegtl::seq<ch::E, ch::X, ch::E, ch::C, ch::U, ch::T, ch::E> {};
            struct EXISTS : tao::pegtl::seq<ch::E, ch::X, ch::I, ch::S, ch::T, ch::S> {};
            struct EXIT : tao::pegtl::seq<ch::E, ch::X, ch::I, ch::T> {};
            struct EXTERNAL : tao::pegtl::seq<ch::E, ch::X, ch::T, ch::E, ch::R, ch::N, ch::A, ch::L> {};
            struct EXTRACT : tao::pegtl::seq<ch::E, ch::X, ch::T, ch::R, ch::A, ch::C, ch::T> {};
            struct FALSE_ : tao::pegtl::seq<ch::F, ch::A, ch::L, ch::S, ch::E> {};
            struct FETCH : tao::pegtl::seq<ch::F, ch::E, ch::T, ch::C, ch::H> {};
            struct FINAL : tao::pegtl::seq<ch::F, ch::I, ch::N, ch::A, ch::L> {};
            struct FIRST : tao::pegtl::seq<ch::F, ch::I, ch::R, ch::S, ch::T> {};
            struct FLOAT : tao::pegtl::seq<ch::F, ch::L, ch::O, ch::A, ch::T> {};
            struct FOR : tao::pegtl::seq<ch::F, ch::O, ch::R> {};
            struct FOREIGN : tao::pegtl::seq<ch::F, ch::O, ch::R, ch::E, ch::I, ch::G, ch::N> {};
            struct FORTRAN : tao::pegtl::seq<ch::F, ch::O, ch::R, ch::T, ch::R, ch::A, ch::N> {};
            struct FOUND : tao::pegtl::seq<ch::F, ch::O, ch::U, ch::N, ch::D> {};
            struct FREE : tao::pegtl::seq<ch::F, ch::R, ch::E, ch::E> {};
            struct FROM : tao::pegtl::seq<ch::F, ch::R, ch::O, ch::M> {};
            struct FULL : tao::pegtl::seq<ch::F, ch::U, ch::L, ch::L> {};
            struct FUNCTION : tao::pegtl::seq<ch::F, ch::U, ch::N, ch::C, ch::T, ch::I, ch::O, ch::N> {};
            struct G : tao::pegtl::seq<ch::G> {};
            struct GENERAL : tao::pegtl::seq<ch::G, ch::E, ch::N, ch::E, ch::R, ch::A, ch::L> {};
            struct GENERATED : tao::pegtl::seq<ch::G, ch::E, ch::N, ch::E, ch::R, ch::A, ch::T, ch::E, ch::D> {};
            struct GET : tao::pegtl::seq<ch::G, ch::E, ch::T> {};
            struct GLOBAL : tao::pegtl::seq<ch::G, ch::L, ch::O, ch::B, ch::A, ch::L> {};
            struct GO : tao::pegtl::seq<ch::G, ch::O> {};
            struct GOTO : tao::pegtl::seq<ch::G, ch::O, ch::T, ch::O> {};
            struct GRANT : tao::pegtl::seq<ch::G, ch::R, ch::A, ch::N, ch::T> {};
            struct GRANTED : tao::pegtl::seq<ch::G, ch::R, ch::A, ch::N, ch::T, ch::E, ch::D> {};
            struct GROUP : tao::pegtl::seq<ch::G, ch::R, ch::O, ch::U, ch::P> {};
            struct GROUPING : tao::pegtl::seq<ch::G, ch::R, ch::O, ch::U, ch::P, ch::I, ch::N, ch::G> {};
            struct HANDLE : tao::pegtl::seq<ch::H, ch::A, ch::N, ch::D, ch::L, ch::E> {};
            struct HAVING : tao::pegtl::seq<ch::H, ch::A, ch::V, ch::I, ch::N, ch::G> {};
            struct HIERARCHY : tao::pegtl::seq<ch::H, ch::I, ch::E, ch::R, ch::A, ch::R, ch::C, ch::H, ch::Y> {};
            struct HOLD : tao::pegtl::seq<ch::H, ch::O, ch::L, ch::D> {};
            struct HOUR : tao::pegtl::seq<ch::H, ch::O, ch::U, ch::R> {};
            struct IDENTITY : tao::pegtl::seq<ch::I, ch::D, ch::E, ch::N, ch::T, ch::I, ch::T, ch::Y> {};
            struct IF : tao::pegtl::seq<ch::I, ch::F> {};
            struct IMMEDIATE : tao::pegtl::seq<ch::I, ch::M, ch::M, ch::E, ch::D, ch::I, ch::A, ch::T, ch::E> {};
            struct IMPLEMENTATION : tao::pegtl::seq<ch::I, ch::M, ch::P, ch::L, ch::E, ch::M, ch::E, ch::N, ch::T, ch::A, ch::T, ch::I, ch::O, ch::N> {};
            struct IN : tao::pegtl::seq<ch::I, ch::N> {};
            struct INDICATOR : tao::pegtl::seq<ch::I, ch::N, ch::D, ch::I, ch::C, ch::A, ch::T, ch::O, ch::R> {};
            struct INITIALLY : tao::pegtl::seq<ch::I, ch::N, ch::I, ch::T, ch::I, ch::A, ch::L, ch::L, ch::Y> {};
            struct INNER : tao::pegtl::seq<ch::I, ch::N, ch::N, ch::E, ch::R> {};
            struct INOUT : tao::pegtl::seq<ch::I, ch::N, ch::O, ch::U, ch::T> {};
            struct INPUT : tao::pegtl::seq<ch::I, ch::N, ch::P, ch::U, ch::T> {};
            struct INSENSITIVE : tao::pegtl::seq<ch::I, ch::N, ch::S, ch::E, ch::N, ch::S, ch::I, ch::T, ch::I, ch::V, ch::E> {};
            struct INSERT : tao::pegtl::seq<ch::I, ch::N, ch::S, ch::E, ch::R, ch::T> {};
            struct INSTANCE : tao::pegtl::seq<ch::I, ch::N, ch::S, ch::T, ch::A, ch::N, ch::C, ch::E> {};
            struct INSTANTIABLE : tao::pegtl::seq<ch::I, ch::N, ch::S, ch::T, ch::A, ch::N, ch::T, ch::I, ch::A, ch::B, ch::L, ch::E> {};
            struct INT : tao::pegtl::seq<ch::I, ch::N, ch::T> {};
            struct INTEGER : tao::pegtl::seq<ch::I, ch::N, ch::T, ch::E, ch::G, ch::E, ch::R> {};
            struct INTERSECT : tao::pegtl::seq<ch::I, ch::N, ch::T, ch::E, ch::R, ch::S, ch::E, ch::C, ch::T> {};
            struct INTERVAL : tao::pegtl::seq<ch::I, ch::N, ch::T, ch::E, ch::R, ch::V, ch::A, ch::L> {};
            struct INTO : tao::pegtl::seq<ch::I, ch::N, ch::T, ch::O> {};
            struct INVOKER : tao::pegtl::seq<ch::I, ch::N, ch::V, ch::O, ch::K, ch::E, ch::R> {};
            struct IS : tao::pegtl::seq<ch::I, ch::S> {};
            struct ISOLATION : tao::pegtl::seq<ch::I, ch::S, ch::O, ch::L, ch::A, ch::T, ch::I, ch::O, ch::N> {};
            struct JOIN : tao::pegtl::seq<ch::J, ch::O, ch::I, ch::N> {};
            struct K : tao::pegtl::seq<ch::K> {};
            struct KEY : tao::pegtl::seq<ch::K, ch::E, ch::Y> {};
            struct KEY_MEMBER : tao::pegtl::seq<ch::K, ch::E, ch::Y, ch::_, ch::M, ch::E, ch::M, ch::B, ch::E, ch::R> {};
            struct KEY_TYPE : tao::pegtl::seq<ch::K, ch::E, ch::Y, ch::_, ch::T, ch::Y, ch::P, ch::E> {};
            struct LANGUAGE : tao::pegtl::seq<ch::L, ch::A, ch::N, ch::G, ch::U, ch::A, ch::G, ch::E> {};
            struct LARGE : tao::pegtl::seq<ch::L, ch::A, ch::R, ch::G, ch::E> {};
            struct LAST : tao::pegtl::seq<ch::L, ch::A, ch::S, ch::T> {};
            struct LATERAL : tao::pegtl::seq<ch::L, ch::A, ch::T, ch::E, ch::R, ch::A, ch::L> {};
            struct LEADING : tao::pegtl::seq<ch::L, ch::E, ch::A, ch::D, ch::I, ch::N, ch::G> {};
            struct LEAVE : tao::pegtl::seq<ch::L, ch::E, ch::A, ch::V, ch::E> {};
            struct LEFT : tao::pegtl::seq<ch::L, ch::E, ch::F, ch::T> {};
            struct LENGTH : tao::pegtl::seq<ch::L, ch::E, ch::N, ch::G, ch::T, ch::H> {};
            struct LEVEL : tao::pegtl::seq<ch::L, ch::E, ch::V, ch::E, ch::L> {};
            struct LIKE : tao::pegtl::seq<ch::L, ch::I, ch::K, ch::E> {};
            struct LOCAL : tao::pegtl::seq<ch::L, ch::O, ch::C, ch::A, ch::L> {};
            struct LOCALTIME : tao::pegtl::seq<ch::L, ch::O, ch::C, ch::A, ch::L, ch::T, ch::I, ch::M, ch::E> {};
            struct LOCALTIMESTAMP : tao::pegtl::seq<ch::L, ch::O, ch::C, ch::A, ch::L, ch::T, ch::I, ch::M, ch::E, ch::S, ch::T, ch::A, ch::M, ch::P> {};
            struct LOCATOR : tao::pegtl::seq<ch::L, ch::O, ch::C, ch::A, ch::T, ch::O, ch::R> {};
            struct LOOP : tao::pegtl::seq<ch::L, ch::O, ch::O, ch::P> {};
            struct LOWER : tao::pegtl::seq<ch::L, ch::O, ch::W, ch::E, ch::R> {};
            struct M : tao::pegtl::seq<ch::M> {};
            struct MAP : tao::pegtl::seq<ch::M, ch::A, ch::P> {};
            struct MATCH : tao::pegtl::seq<ch::M, ch::A, ch::T, ch::C, ch::H> {};
            struct MAX : tao::pegtl::seq<ch::M, ch::A, ch::X> {};
            struct MESSAGE_LENGTH : tao::pegtl::seq<ch::M, ch::E, ch::S, ch::S, ch::A, ch::G, ch::E, ch::_, ch::L, ch::E, ch::N, ch::G, ch::T, ch::H> {};
            struct MESSAGE_OCTET_LENGTH : tao::pegtl::seq<ch::M, ch::E, ch::S, ch::S, ch::A, ch::G, ch::E, ch::_, ch::O, ch::C, ch::T, ch::E, ch::T, ch::_, ch::L, ch::E, ch::N, ch::G, ch::T, ch::H> {};
            struct MESSAGE_TEXT : tao::pegtl::seq<ch::M, ch::E, ch::S, ch::S, ch::A, ch::G, ch::E, ch::_, ch::T, ch::E, ch::X, ch::T> {};
            struct METHOD : tao::pegtl::seq<ch::M, ch::E, ch::T, ch::H, ch::O, ch::D> {};
            struct MIN : tao::pegtl::seq<ch::M, ch::I, ch::N> {};
            struct MINUTE : tao::pegtl::seq<ch::M, ch::I, ch::N, ch::U, ch::T, ch::E> {};
            struct MOD : tao::pegtl::seq<ch::M, ch::O, ch::D> {};
            struct MODIFIES : tao::pegtl::seq<ch::M, ch::O, ch::D, ch::I, ch::F, ch::I, ch::E, ch::S> {};
            struct MODULE : tao::pegtl::seq<ch::M, ch::O, ch::D, ch::U, ch::L, ch::E> {};
            struct MONTH : tao::pegtl::seq<ch::M, ch::O, ch::N, ch::T, ch::H> {};
            struct MORE : tao::pegtl::seq<ch::M, ch::O, ch::R, ch::E> {};
            struct MUMPS : tao::pegtl::seq<ch::M, ch::U, ch::M, ch::P, ch::S> {};
            struct NAME : tao::pegtl::seq<ch::N, ch::A, ch::M, ch::E> {};
            struct NAMES : tao::pegtl::seq<ch::N, ch::A, ch::M, ch::E, ch::S> {};
            struct NATIONAL : tao::pegtl::seq<ch::N, ch::A, ch::T, ch::I, ch::O, ch::N, ch::A, ch::L> {};
            struct NATURAL : tao::pegtl::seq<ch::N, ch::A, ch::T, ch::U, ch::R, ch::A, ch::L> {};
            struct NCHAR : tao::pegtl::seq<ch::N, ch::C, ch::H, ch::A, ch::R> {};
            struct NCLOB : tao::pegtl::seq<ch::N, ch::C, ch::L, ch::O, ch::B> {};
            struct NESTING : tao::pegtl::seq<ch::N, ch::E, ch::S, ch::T, ch::I, ch::N, ch::G> {};
            struct NEW : tao::pegtl::seq<ch::N, ch::E, ch::W> {};
            struct NEXT : tao::pegtl::seq<ch::N, ch::E, ch::X, ch::T> {};
            struct NO : tao::pegtl::seq<ch::N, ch::O> {};
            struct NONE : tao::pegtl::seq<ch::N, ch::O, ch::N, ch::E> {};
            struct NOT : tao::pegtl::seq<ch::N, ch::O, ch::T> {};
            struct NULL_ : tao::pegtl::seq<ch::N, ch::U, ch::L, ch::L> {};
            struct NULLABLE : tao::pegtl::seq<ch::N, ch::U, ch::L, ch::L, ch::A, ch::B, ch::L, ch::E> {};
            struct NULLIF : tao::pegtl::seq<ch::N, ch::U, ch::L, ch::L, ch::I, ch::F> {};
            struct NUMBER : tao::pegtl::seq<ch::N, ch::U, ch::M, ch::B, ch::E, ch::R> {};
            struct NUMERIC : tao::pegtl::seq<ch::N, ch::U, ch::M, ch::E, ch::R, ch::I, ch::C> {};
            struct OBJECT : tao::pegtl::seq<ch::O, ch::B, ch::J, ch::E, ch::C, ch::T> {};
            struct OCTET_LENGTH : tao::pegtl::seq<ch::O, ch::C, ch::T, ch::E, ch::T, ch::_, ch::L, ch::E, ch::N, ch::G, ch::T, ch::H> {};
            struct OF : tao::pegtl::seq<ch::O, ch::F> {};
            struct OLD : tao::pegtl::seq<ch::O, ch::L, ch::D> {};
            struct ON : tao::pegtl::seq<ch::O, ch::N> {};
            struct ONLY : tao::pegtl::seq<ch::O, ch::N, ch::L, ch::Y> {};
            struct OPEN : tao::pegtl::seq<ch::O, ch::P, ch::E, ch::N> {};
            struct OPTION : tao::pegtl::seq<ch::O, ch::P, ch::T, ch::I, ch::O, ch::N> {};
            struct OPTIONS : tao::pegtl::seq<ch::O, ch::P, ch::T, ch::I, ch::O, ch::N, ch::S> {};
            struct OR : tao::pegtl::seq<ch::O, ch::R> {};
            struct ORDER : tao::pegtl::seq<ch::O, ch::R, ch::D, ch::E, ch::R> {};
            struct ORDERING : tao::pegtl::seq<ch::O, ch::R, ch::D, ch::E, ch::R, ch::I, ch::N, ch::G> {};
            struct ORDINALITY : tao::pegtl::seq<ch::O, ch::R, ch::D, ch::I, ch::N, ch::A, ch::L, ch::I, ch::T, ch::Y> {};
            struct OUT : tao::pegtl::seq<ch::O, ch::U, ch::T> {};
            struct OUTER : tao::pegtl::seq<ch::O, ch::U, ch::T, ch::E, ch::R> {};
            struct OUTPUT : tao::pegtl::seq<ch::O, ch::U, ch::T, ch::P, ch::U, ch::T> {};
            struct OVERLAPS : tao::pegtl::seq<ch::O, ch::V, ch::E, ch::R, ch::L, ch::A, ch::P, ch::S> {};
            struct OVERLAY : tao::pegtl::seq<ch::O, ch::V, ch::E, ch::R, ch::L, ch::A, ch::Y> {};
            struct OVERRIDING : tao::pegtl::seq<ch::O, ch::V, ch::E, ch::R, ch::R, ch::I, ch::D, ch::I, ch::N, ch::G> {};
            struct PAD : tao::pegtl::seq<ch::P, ch::A, ch::D> {};
            struct PARAMETER : tao::pegtl::seq<ch::P, ch::A, ch::R, ch::A, ch::M, ch::E, ch::T, ch::E, ch::R> {};
            struct PARAMETER_MODE : tao::pegtl::seq<ch::P, ch::A, ch::R, ch::A, ch::M, ch::E, ch::T, ch::E, ch::R, ch::_, ch::M, ch::O, ch::D, ch::E> {};
            struct PARAMETER_NAME : tao::pegtl::seq<ch::P, ch::A, ch::R, ch::A, ch::M, ch::E, ch::T, ch::E, ch::R, ch::_, ch::N, ch::A, ch::M, ch::E> {};
            struct PARAMETER_ORDINAL_POSITION : tao::pegtl::seq<ch::P, ch::A, ch::R, ch::A, ch::M, ch::E, ch::T, ch::E, ch::R, ch::_, ch::O, ch::R, ch::D, ch::I, ch::N, ch::A, ch::L, ch::_, ch::P, ch::O, ch::S, ch::I, ch::T, ch::I, ch::O, ch::N> {};
            struct PARAMETER_SPECIFIC_CATALOG : tao::pegtl::seq<ch::P, ch::A, ch::R, ch::A, ch::M, ch::E, ch::T, ch::E, ch::R, ch::_, ch::S, ch::P, ch::E, ch::C, ch::I, ch::F, ch::I, ch::C, ch::_, ch::C, ch::A, ch::T, ch::A, ch::L, ch::O, ch::G> {};
            struct PARAMETER_SPECIFIC_NAME : tao::pegtl::seq<ch::P, ch::A, ch::R, ch::A, ch::M, ch::E, ch::T, ch::E, ch::R, ch::_, ch::S, ch::P, ch::E, ch::C, ch::I, ch::F, ch::I, ch::C, ch::_, ch::N, ch::A, ch::M, ch::E> {};
            struct PARAMETER_SPECIFIC_SCHEMA : tao::pegtl::seq<ch::P, ch::A, ch::R, ch::A, ch::M, ch::E, ch::T, ch::E, ch::R, ch::_, ch::S, ch::P, ch::E, ch::C, ch::I, ch::F, ch::I, ch::C, ch::_, ch::S, ch::C, ch::H, ch::E, ch::M, ch::A> {};
            struct PARTIAL : tao::pegtl::seq<ch::P, ch::A, ch::R, ch::T, ch::I, ch::A, ch::L> {};
            struct PASCAL : tao::pegtl::seq<ch::P, ch::A, ch::S, ch::C, ch::A, ch::L> {};
            struct PATH : tao::pegtl::seq<ch::P, ch::A, ch::T, ch::H> {};
            struct PLI : tao::pegtl::seq<ch::P, ch::L, ch::I> {};
            struct POSITION : tao::pegtl::seq<ch::P, ch::O, ch::S, ch::I, ch::T, ch::I, ch::O, ch::N> {};
            struct PRECISION : tao::pegtl::seq<ch::P, ch::R, ch::E, ch::C, ch::I, ch::S, ch::I, ch::O, ch::N> {};
            struct PREPARE : tao::pegtl::seq<ch::P, ch::R, ch::E, ch::P, ch::A, ch::R, ch::E> {};
            struct PRESERVE : tao::pegtl::seq<ch::P, ch::R, ch::E, ch::S, ch::E, ch::R, ch::V, ch::E> {};
            struct PRIMARY : tao::pegtl::seq<ch::P, ch::R, ch::I, ch::M, ch::A, ch::R, ch::Y> {};
            struct PRIOR : tao::pegtl::seq<ch::P, ch::R, ch::I, ch::O, ch::R> {};
            struct PRIVILEGES : tao::pegtl::seq<ch::P, ch::R, ch::I, ch::V, ch::I, ch::L, ch::E, ch::G, ch::E, ch::S> {};
            struct PROCEDURE : tao::pegtl::seq<ch::P, ch::R, ch::O, ch::C, ch::E, ch::D, ch::U, ch::R, ch::E> {};
            struct PUBLIC : tao::pegtl::seq<ch::P, ch::U, ch::B, ch::L, ch::I, ch::C> {};
            struct READ : tao::pegtl::seq<ch::R, ch::E, ch::A, ch::D> {};
            struct READS : tao::pegtl::seq<ch::R, ch::E, ch::A, ch::D, ch::S> {};
            struct REAL : tao::pegtl::seq<ch::R, ch::E, ch::A, ch::L> {};
            struct RECURSIVE : tao::pegtl::seq<ch::R, ch::E, ch::C, ch::U, ch::R, ch::S, ch::I, ch::V, ch::E> {};
            struct REDO : tao::pegtl::seq<ch::R, ch::E, ch::D, ch::O> {};
            struct REF : tao::pegtl::seq<ch::R, ch::E, ch::F> {};
            struct REFERENCES : tao::pegtl::seq<ch::R, ch::E, ch::F, ch::E, ch::R, ch::E, ch::N, ch::C, ch::E, ch::S> {};
            struct REFERENCING : tao::pegtl::seq<ch::R, ch::E, ch::F, ch::E, ch::R, ch::E, ch::N, ch::C, ch::I, ch::N, ch::G> {};
            struct RELATIVE : tao::pegtl::seq<ch::R, ch::E, ch::L, ch::A, ch::T, ch::I, ch::V, ch::E> {};
            struct RELEASE : tao::pegtl::seq<ch::R, ch::E, ch::L, ch::E, ch::A, ch::S, ch::E> {};
            struct REPEAT : tao::pegtl::seq<ch::R, ch::E, ch::P, ch::E, ch::A, ch::T> {};
            struct REPEATABLE : tao::pegtl::seq<ch::R, ch::E, ch::P, ch::E, ch::A, ch::T, ch::A, ch::B, ch::L, ch::E> {};
            struct RESIGNAL : tao::pegtl::seq<ch::R, ch::E, ch::S, ch::I, ch::G, ch::N, ch::A, ch::L> {};
            struct RESTRICT : tao::pegtl::seq<ch::R, ch::E, ch::S, ch::T, ch::R, ch::I, ch::C, ch::T> {};
            struct RESULT : tao::pegtl::seq<ch::R, ch::E, ch::S, ch::U, ch::L, ch::T> {};
            struct RETURN : tao::pegtl::seq<ch::R, ch::E, ch::T, ch::U, ch::R, ch::N> {};
            struct RETURNED_CARDINALITY : tao::pegtl::seq<ch::R, ch::E, ch::T, ch::U, ch::R, ch::N, ch::E, ch::D, ch::_, ch::C, ch::A, ch::R, ch::D, ch::I, ch::N, ch::A, ch::L, ch::I, ch::T, ch::Y> {};
            struct RETURNED_LENGTH : tao::pegtl::seq<ch::R, ch::E, ch::T, ch::U, ch::R, ch::N, ch::E, ch::D, ch::_, ch::L, ch::E, ch::N, ch::G, ch::T, ch::H> {};
            struct RETURNED_OCTET_LENGTH : tao::pegtl::seq<ch::R, ch::E, ch::T, ch::U, ch::R, ch::N, ch::E, ch::D, ch::_, ch::O, ch::C, ch::T, ch::E, ch::T, ch::_, ch::L, ch::E, ch::N, ch::G, ch::T, ch::H> {};
            struct RETURNED_SQLSTATE : tao::pegtl::seq<ch::R, ch::E, ch::T, ch::U, ch::R, ch::N, ch::E, ch::D, ch::_, ch::S, ch::Q, ch::L, ch::S, ch::T, ch::A, ch::T, ch::E> {};
            struct RETURNS : tao::pegtl::seq<ch::R, ch::E, ch::T, ch::U, ch::R, ch::N, ch::S> {};
            struct REVOKE : tao::pegtl::seq<ch::R, ch::E, ch::V, ch::O, ch::K, ch::E> {};
            struct RIGHT : tao::pegtl::seq<ch::R, ch::I, ch::G, ch::H, ch::T> {};
            struct ROLE : tao::pegtl::seq<ch::R, ch::O, ch::L, ch::E> {};
            struct ROLLBACK : tao::pegtl::seq<ch::R, ch::O, ch::L, ch::L, ch::B, ch::A, ch::C, ch::K> {};
            struct ROLLUP : tao::pegtl::seq<ch::R, ch::O, ch::L, ch::L, ch::U, ch::P> {};
            struct ROUTINE : tao::pegtl::seq<ch::R, ch::O, ch::U, ch::T, ch::I, ch::N, ch::E> {};
            struct ROUTINE_CATALOG : tao::pegtl::seq<ch::R, ch::O, ch::U, ch::T, ch::I, ch::N, ch::E, ch::_, ch::C, ch::A, ch::T, ch::A, ch::L, ch::O, ch::G> {};
            struct ROUTINE_NAME : tao::pegtl::seq<ch::R, ch::O, ch::U, ch::T, ch::I, ch::N, ch::E, ch::_, ch::N, ch::A, ch::M, ch::E> {};
            struct ROUTINE_SCHEMA : tao::pegtl::seq<ch::R, ch::O, ch::U, ch::T, ch::I, ch::N, ch::E, ch::_, ch::S, ch::C, ch::H, ch::E, ch::M, ch::A> {};
            struct ROW : tao::pegtl::seq<ch::R, ch::O, ch::W> {};
            struct ROWS : tao::pegtl::seq<ch::R, ch::O, ch::W, ch::S> {};
            struct ROW_COUNT : tao::pegtl::seq<ch::R, ch::O, ch::W, ch::_, ch::C, ch::O, ch::U, ch::N, ch::T> {};
            struct SAVEPOINT : tao::pegtl::seq<ch::S, ch::A, ch::V, ch::E, ch::P, ch::O, ch::I, ch::N, ch::T> {};
            struct SCALE : tao::pegtl::seq<ch::S, ch::C, ch::A, ch::L, ch::E> {};
            struct SCHEMA : tao::pegtl::seq<ch::S, ch::C, ch::H, ch::E, ch::M, ch::A> {};
            struct SCHEMA_NAME : tao::pegtl::seq<ch::S, ch::C, ch::H, ch::E, ch::M, ch::A, ch::_, ch::N, ch::A, ch::M, ch::E> {};
            struct SCOPE : tao::pegtl::seq<ch::S, ch::C, ch::O, ch::P, ch::E> {};
            struct SCROLL : tao::pegtl::seq<ch::S, ch::C, ch::R, ch::O, ch::L, ch::L> {};
            struct SEARCH : tao::pegtl::seq<ch::S, ch::E, ch::A, ch::R, ch::C, ch::H> {};
            struct SECOND : tao::pegtl::seq<ch::S, ch::E, ch::C, ch::O, ch::N, ch::D> {};
            struct SECTION : tao::pegtl::seq<ch::S, ch::E, ch::C, ch::T, ch::I, ch::O, ch::N> {};
            struct SECURITY : tao::pegtl::seq<ch::S, ch::E, ch::C, ch::U, ch::R, ch::I, ch::T, ch::Y> {};
            struct SELECT : tao::pegtl::seq<ch::S, ch::E, ch::L, ch::E, ch::C, ch::T> {};
            struct SELF : tao::pegtl::seq<ch::S, ch::E, ch::L, ch::F> {};
            struct SENSITIVE : tao::pegtl::seq<ch::S, ch::E, ch::N, ch::S, ch::I, ch::T, ch::I, ch::V, ch::E> {};
            struct SERIALIZABLE : tao::pegtl::seq<ch::S, ch::E, ch::R, ch::I, ch::A, ch::L, ch::I, ch::Z, ch::A, ch::B, ch::L, ch::E> {};
            struct SERVER_NAME : tao::pegtl::seq<ch::S, ch::E, ch::R, ch::V, ch::E, ch::R, ch::_, ch::N, ch::A, ch::M, ch::E> {};
            struct SESSION : tao::pegtl::seq<ch::S, ch::E, ch::S, ch::S, ch::I, ch::O, ch::N> {};
            struct SESSION_USER : tao::pegtl::seq<ch::S, ch::E, ch::S, ch::S, ch::I, ch::O, ch::N, ch::_, ch::U, ch::S, ch::E, ch::R> {};
            struct SET : tao::pegtl::seq<ch::S, ch::E, ch::T> {};
            struct SETS : tao::pegtl::seq<ch::S, ch::E, ch::T, ch::S> {};
            struct SIGNAL : tao::pegtl::seq<ch::S, ch::I, ch::G, ch::N, ch::A, ch::L> {};
            struct SIMILAR : tao::pegtl::seq<ch::S, ch::I, ch::M, ch::I, ch::L, ch::A, ch::R> {};
            struct SIMPLE : tao::pegtl::seq<ch::S, ch::I, ch::M, ch::P, ch::L, ch::E> {};
            struct SIZE : tao::pegtl::seq<ch::S, ch::I, ch::Z, ch::E> {};
            struct SMALLINT : tao::pegtl::seq<ch::S, ch::M, ch::A, ch::L, ch::L, ch::I, ch::N, ch::T> {};
            struct SOME : tao::pegtl::seq<ch::S, ch::O, ch::M, ch::E> {};
            struct SOURCE : tao::pegtl::seq<ch::S, ch::O, ch::U, ch::R, ch::C, ch::E> {};
            struct SPACE : tao::pegtl::seq<ch::S, ch::P, ch::A, ch::C, ch::E> {};
            struct SPECIFIC : tao::pegtl::seq<ch::S, ch::P, ch::E, ch::C, ch::I, ch::F, ch::I, ch::C> {};
            struct SPECIFICTYPE : tao::pegtl::seq<ch::S, ch::P, ch::E, ch::C, ch::I, ch::F, ch::I, ch::C, ch::T, ch::Y, ch::P, ch::E> {};
            struct SPECIFIC_NAME : tao::pegtl::seq<ch::S, ch::P, ch::E, ch::C, ch::I, ch::F, ch::I, ch::C, ch::_, ch::N, ch::A, ch::M, ch::E> {};
            struct SQL : tao::pegtl::seq<ch::S, ch::Q, ch::L> {};
            struct SQLEXCEPTION : tao::pegtl::seq<ch::S, ch::Q, ch::L, ch::E, ch::X, ch::C, ch::E, ch::P, ch::T, ch::I, ch::O, ch::N> {};
            struct SQLSTATE : tao::pegtl::seq<ch::S, ch::Q, ch::L, ch::S, ch::T, ch::A, ch::T, ch::E> {};
            struct SQLWARNING : tao::pegtl::seq<ch::S, ch::Q, ch::L, ch::W, ch::A, ch::R, ch::N, ch::I, ch::N, ch::G> {};
            struct START : tao::pegtl::seq<ch::S, ch::T, ch::A, ch::R, ch::T> {};
            struct STATE : tao::pegtl::seq<ch::S, ch::T, ch::A, ch::T, ch::E> {};
            struct STATEMENT : tao::pegtl::seq<ch::S, ch::T, ch::A, ch::T, ch::E, ch::M, ch::E, ch::N, ch::T> {};
            struct STATIC : tao::pegtl::seq<ch::S, ch::T, ch::A, ch::T, ch::I, ch::C> {};
            struct STRUCTURE : tao::pegtl::seq<ch::S, ch::T, ch::R, ch::U, ch::C, ch::T, ch::U, ch::R, ch::E> {};
            struct STYLE : tao::pegtl::seq<ch::S, ch::T, ch::Y, ch::L, ch::E> {};
            struct SUBCLASS_ORIGIN : tao::pegtl::seq<ch::S, ch::U, ch::B, ch::C, ch::L, ch::A, ch::S, ch::S, ch::_, ch::O, ch::R, ch::I, ch::G, ch::I, ch::N> {};
            struct SUBSTRING : tao::pegtl::seq<ch::S, ch::U, ch::B, ch::S, ch::T, ch::R, ch::I, ch::N, ch::G> {};
            struct SUM : tao::pegtl::seq<ch::S, ch::U, ch::M> {};
            struct SYMMETRIC : tao::pegtl::seq<ch::S, ch::Y, ch::M, ch::M, ch::E, ch::T, ch::R, ch::I, ch::C> {};
            struct SYSTEM : tao::pegtl::seq<ch::S, ch::Y, ch::S, ch::T, ch::E, ch::M> {};
            struct SYSTEM_USER : tao::pegtl::seq<ch::S, ch::Y, ch::S, ch::T, ch::E, ch::M, ch::_, ch::U, ch::S, ch::E, ch::R> {};
            struct TABLE : tao::pegtl::seq<ch::T, ch::A, ch::B, ch::L, ch::E> {};
            struct TABLE_NAME : tao::pegtl::seq<ch::T, ch::A, ch::B, ch::L, ch::E, ch::_, ch::N, ch::A, ch::M, ch::E> {};
            struct TEMPORARY : tao::pegtl::seq<ch::T, ch::E, ch::M, ch::P, ch::O, ch::R, ch::A, ch::R, ch::Y> {};
            struct THEN : tao::pegtl::seq<ch::T, ch::H, ch::E, ch::N> {};
            struct TIME : tao::pegtl::seq<ch::T, ch::I, ch::M, ch::E> {};
            struct TIMESTAMP : tao::pegtl::seq<ch::T, ch::I, ch::M, ch::E, ch::S, ch::T, ch::A, ch::M, ch::P> {};
            struct TIMEZONE_HOUR : tao::pegtl::seq<ch::T, ch::I, ch::M, ch::E, ch::Z, ch::O, ch::N, ch::E, ch::_, ch::H, ch::O, ch::U, ch::R> {};
            struct TIMEZONE_MINUTE : tao::pegtl::seq<ch::T, ch::I, ch::M, ch::E, ch::Z, ch::O, ch::N, ch::E, ch::_, ch::M, ch::I, ch::N, ch::U, ch::T, ch::E> {};
            struct TO : tao::pegtl::seq<ch::T, ch::O> {};
            struct TOP_LEVEL_COUNT : tao::pegtl::seq<ch::T, ch::O, ch::P, ch::_, ch::L, ch::E, ch::V, ch::E, ch::L, ch::_, ch::C, ch::O, ch::U, ch::N, ch::T> {};
            struct TRAILING : tao::pegtl::seq<ch::T, ch::R, ch::A, ch::I, ch::L, ch::I, ch::N, ch::G> {};
            struct TRANSACTION : tao::pegtl::seq<ch::T, ch::R, ch::A, ch::N, ch::S, ch::A, ch::C, ch::T, ch::I, ch::O, ch::N> {};
            struct TRANSACTIONS_COMMITTED : tao::pegtl::seq<ch::T, ch::R, ch::A, ch::N, ch::S, ch::A, ch::C, ch::T, ch::I, ch::O, ch::N, ch::S, ch::_, ch::C, ch::O, ch::M, ch::M, ch::I, ch::T, ch::T, ch::E, ch::D> {};
            struct TRANSACTIONS_ROLLED_BACK : tao::pegtl::seq<ch::T, ch::R, ch::A, ch::N, ch::S, ch::A, ch::C, ch::T, ch::I, ch::O, ch::N, ch::S, ch::_, ch::R, ch::O, ch::L, ch::L, ch::E, ch::D, ch::_, ch::B, ch::A, ch::C, ch::K> {};
            struct TRANSACTION_ACTIVE : tao::pegtl::seq<ch::T, ch::R, ch::A, ch::N, ch::S, ch::A, ch::C, ch::T, ch::I, ch::O, ch::N, ch::_, ch::A, ch::C, ch::T, ch::I, ch::V, ch::E> {};
            struct TRANSFORM : tao::pegtl::seq<ch::T, ch::R, ch::A, ch::N, ch::S, ch::F, ch::O, ch::R, ch::M> {};
            struct TRANSFORMS : tao::pegtl::seq<ch::T, ch::R, ch::A, ch::N, ch::S, ch::F, ch::O, ch::R, ch::M, ch::S> {};
            struct TRANSLATE : tao::pegtl::seq<ch::T, ch::R, ch::A, ch::N, ch::S, ch::L, ch::A, ch::T, ch::E> {};
            struct TRANSLATION : tao::pegtl::seq<ch::T, ch::R, ch::A, ch::N, ch::S, ch::L, ch::A, ch::T, ch::I, ch::O, ch::N> {};
            struct TREAT : tao::pegtl::seq<ch::T, ch::R, ch::E, ch::A, ch::T> {};
            struct TRIGGER : tao::pegtl::seq<ch::T, ch::R, ch::I, ch::G, ch::G, ch::E, ch::R> {};
            struct TRIGGER_CATALOG : tao::pegtl::seq<ch::T, ch::R, ch::I, ch::G, ch::G, ch::E, ch::R, ch::_, ch::C, ch::A, ch::T, ch::A, ch::L, ch::O, ch::G> {};
            struct TRIGGER_NAME : tao::pegtl::seq<ch::T, ch::R, ch::I, ch::G, ch::G, ch::E, ch::R, ch::_, ch::N, ch::A, ch::M, ch::E> {};
            struct TRIGGER_SCHEMA : tao::pegtl::seq<ch::T, ch::R, ch::I, ch::G, ch::G, ch::E, ch::R, ch::_, ch::S, ch::C, ch::H, ch::E, ch::M, ch::A> {};
            struct TRIM : tao::pegtl::seq<ch::T, ch::R, ch::I, ch::M> {};
            struct TRUE_ : tao::pegtl::seq<ch::T, ch::R, ch::U, ch::E> {};
            struct TYPE : tao::pegtl::seq<ch::T, ch::Y, ch::P, ch::E> {};
            struct UNCOMMITTED : tao::pegtl::seq<ch::U, ch::N, ch::C, ch::O, ch::M, ch::M, ch::I, ch::T, ch::T, ch::E, ch::D> {};
            struct UNDER : tao::pegtl::seq<ch::U, ch::N, ch::D, ch::E, ch::R> {};
            struct UNDO : tao::pegtl::seq<ch::U, ch::N, ch::D, ch::O> {};
            struct UNION : tao::pegtl::seq<ch::U, ch::N, ch::I, ch::O, ch::N> {};
            struct UNIQUE : tao::pegtl::seq<ch::U, ch::N, ch::I, ch::Q, ch::U, ch::E> {};
            struct UNKNOWN : tao::pegtl::seq<ch::U, ch::N, ch::K, ch::N, ch::O, ch::W, ch::N> {};
            struct UNNAMED : tao::pegtl::seq<ch::U, ch::N, ch::N, ch::A, ch::M, ch::E, ch::D> {};
            struct UNNEST : tao::pegtl::seq<ch::U, ch::N, ch::N, ch::E, ch::S, ch::T> {};
            struct UNTIL : tao::pegtl::seq<ch::U, ch::N, ch::T, ch::I, ch::L> {};
            struct UPDATE : tao::pegtl::seq<ch::U, ch::P, ch::D, ch::A, ch::T, ch::E> {};
            struct UPPER : tao::pegtl::seq<ch::U, ch::P, ch::P, ch::E, ch::R> {};
            struct USAGE : tao::pegtl::seq<ch::U, ch::S, ch::A, ch::G, ch::E> {};
            struct USER : tao::pegtl::seq<ch::U, ch::S, ch::E, ch::R> {};
            struct USING : tao::pegtl::seq<ch::U, ch::S, ch::I, ch::N, ch::G> {};
            struct VALUE : tao::pegtl::seq<ch::V, ch::A, ch::L, ch::U, ch::E> {};
            struct VALUES : tao::pegtl::seq<ch::V, ch::A, ch::L, ch::U, ch::E, ch::S> {};
            struct VARCHAR : tao::pegtl::seq<ch::V, ch::A, ch::R, ch::C, ch::H, ch::A, ch::R> {};
            struct VARYING : tao::pegtl::seq<ch::V, ch::A, ch::R, ch::Y, ch::I, ch::N, ch::G> {};
            struct VIEW : tao::pegtl::seq<ch::V, ch::I, ch::E, ch::W> {};
            struct WHEN : tao::pegtl::seq<ch::W, ch::H, ch::E, ch::N> {};
            struct WHENEVER : tao::pegtl::seq<ch::W, ch::H, ch::E, ch::N, ch::E, ch::V, ch::E, ch::R> {};
            struct WHERE : tao::pegtl::seq<ch::W, ch::H, ch::E, ch::R, ch::E> {};
            struct WHILE : tao::pegtl::seq<ch::W, ch::H, ch::I, ch::L, ch::E> {};
            struct WITH : tao::pegtl::seq<ch::W, ch::I, ch::T, ch::H> {};
            struct WITHOUT : tao::pegtl::seq<ch::W, ch::I, ch::T, ch::H, ch::O, ch::U, ch::T> {};
            struct WORK : tao::pegtl::seq<ch::W, ch::O, ch::R, ch::K> {};
            struct WRITE : tao::pegtl::seq<ch::W, ch::R, ch::I, ch::T, ch::E> {};
            struct YEAR : tao::pegtl::seq<ch::Y, ch::E, ch::A, ch::R> {};
            struct ZONE : tao::pegtl::seq<ch::Z, ch::O, ch::N, ch::E> {};

            struct reserved
                : tao::pegtl::sor<
                    ABSOLUTE,
                    ACTION,
                    ADD,
                    AFTER,
                    ALL,
                    ALLOCATE,
                    ALTER,
                    AND,
                    ANY,
                    ARE,
                    ARRAY,
                    AS,
                    ASC,
                    ASSERTION,
                    AT,
                    AUTHORIZATION,
                    BEFORE,
                    BEGIN,
                    BETWEEN,
                    BINARY,
                    BIT,
                    BLOB,
                    BOOLEAN,
                    BOTH,
                    BREADTH,
                    BY,
                    CALL,
                    CASCADE,
                    CASCADED,
                    CASE,
                    CAST,
                    CATALOG,
                    CHAR,
                    CHARACTER,
                    CHECK,
                    CLOB,
                    CLOSE,
                    COLLATE,
                    COLLATION,
                    COLUMN,
                    COMMIT,
                    CONDITION,
                    CONNECT,
                    CONNECTION,
                    CONSTRAINT,
                    CONSTRAINTS,
                    CONSTRUCTOR,
                    CONTINUE,
                    CORRESPONDING,
                    CREATE,
                    CROSS,
                    CUBE,
                    CURRENT,
                    CURRENT_DATE,
                    CURRENT_DEFAULT_TRANSFORM_GROUP,
                    CURRENT_PATH,
                    CURRENT_ROLE,
                    CURRENT_TIME,
                    CURRENT_TIMESTAMP,
                    CURRENT_TRANSFORM_GROUP_FOR_TYPE,
                    CURRENT_USER,
                    CURSOR,
                    CYCLE,
                    DATA,
                    DATE,
                    DAY,
                    DEALLOCATE,
                    DEC,
                    DECIMAL,
                    DECLARE,
                    DEFAULT,
                    DEFERRABLE,
                    DEFERRED,
                    DELETE,
                    DEPTH,
                    DEREF,
                    DESC,
                    DESCRIBE,
                    DESCRIPTOR,
                    DETERMINISTIC,
                    DIAGNOSTICS,
                    DISCONNECT,
                    DISTINCT,
                    DO,
                    DOMAIN,
                    DOUBLE,
                    DROP,
                    DYNAMIC,
                    EACH,
                    ELSE,
                    ELSEIF,
                    END,
                    END_EXEC,
                    EQUALS,
                    ESCAPE,
                    EXCEPT,
                    EXCEPTION,
                    EXEC,
                    EXECUTE,
                    EXISTS,
                    EXIT,
                    EXTERNAL,
                    FALSE_,
                    FETCH,
                    FIRST,
                    FLOAT,
                    FOR,
                    FOREIGN,
                    FOUND,
                    FREE,
                    FROM,
                    FULL,
                    FUNCTION,
                    GENERAL,
                    GET,
                    GLOBAL,
                    GO,
                    GOTO,
                    GRANT,
                    GROUP,
                    GROUPING,
                    HANDLE,
                    HAVING,
                    HOLD,
                    HOUR,
                    IDENTITY,
                    IF,
                    IMMEDIATE,
                    IN,
                    INDICATOR,
                    INITIALLY,
                    INNER,
                    INOUT,
                    INPUT,
                    INSERT,
                    INT,
                    INTEGER,
                    INTERSECT,
                    INTERVAL,
                    INTO,
                    IS,
                    ISOLATION,
                    JOIN,
                    KEY,
                    LANGUAGE,
                    LARGE,
                    LAST,
                    LATERAL,
                    LEADING,
                    LEAVE,
                    LEFT,
                    LEVEL,
                    LIKE,
                    LOCAL,
                    LOCALTIME,
                    LOCALTIMESTAMP,
                    LOCATOR,
                    LOOP,
                    MAP,
                    MATCH,
                    METHOD,
                    MINUTE,
                    MODIFIES,
                    MODULE,
                    MONTH,
                    NAMES,
                    NATIONAL,
                    NATURAL,
                    NCHAR,
                    NCLOB,
                    NESTING,
                    NEW,
                    NEXT,
                    NO,
                    NONE,
                    NOT,
                    NULL_,
                    NUMERIC,
                    OBJECT,
                    OF,
                    OLD,
                    ON,
                    ONLY,
                    OPEN,
                    OPTION,
                    OR,
                    ORDER,
                    ORDINALITY,
                    OUT,
                    OUTER,
                    OUTPUT,
                    OVERLAPS,
                    PAD,
                    PARAMETER,
                    PARTIAL,
                    PATH,
                    PRECISION,
                    PREPARE,
                    PRESERVE,
                    PRIMARY,
                    PRIOR,
                    PRIVILEGES,
                    PROCEDURE,
                    PUBLIC,
                    READ,
                    READS,
                    REAL,
                    RECURSIVE,
                    REDO,
                    REF,
                    REFERENCES,
                    REFERENCING,
                    RELATIVE,
                    RELEASE,
                    REPEAT,
                    RESIGNAL,
                    RESTRICT,
                    RESULT,
                    RETURN,
                    RETURNS,
                    REVOKE,
                    RIGHT,
                    ROLE,
                    ROLLBACK,
                    ROLLUP,
                    ROUTINE,
                    ROW,
                    ROWS,
                    SAVEPOINT,
                    SCHEMA,
                    SCROLL,
                    SEARCH,
                    SECOND,
                    SECTION,
                    SELECT,
                    SESSION,
                    SESSION_USER,
                    SET,
                    SETS,
                    SIGNAL,
                    SIMILAR,
                    SIZE,
                    SMALLINT,
                    SOME,
                    SPACE,
                    SPECIFIC,
                    SPECIFICTYPE,
                    SQL,
                    SQLEXCEPTION,
                    SQLSTATE,
                    SQLWARNING,
                    START,
                    STATE,
                    STATIC,
                    SYSTEM_USER,
                    TABLE,
                    TEMPORARY,
                    THEN,
                    TIME,
                    TIMESTAMP,
                    TIMEZONE_HOUR,
                    TIMEZONE_MINUTE,
                    TO,
                    TRAILING,
                    TRANSACTION,
                    TRANSLATION,
                    TREAT,
                    TRIGGER,
                    TRUE_,
                    UNDER,
                    UNDO,
                    UNION,
                    UNIQUE,
                    UNKNOWN,
                    UNNEST,
                    UNTIL,
                    UPDATE,
                    USAGE,
                    USER,
                    USING,
                    VALUE,
                    VALUES,
                    VARCHAR,
                    VARYING,
                    VIEW,
                    WHEN,
                    WHENEVER,
                    WHERE,
                    WHILE,
                    WITH,
                    WITHOUT,
                    WORK,
                    WRITE,
                    YEAR,
                    ZONE
                >
            {};
        }
        // namespace keywords
    }
    // namespace grammar
}
// namespace squeal

#endif // SQUEAL_GRAMMAR_KEYWORDS_HPP
