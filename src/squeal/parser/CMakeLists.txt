cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)

include_directories( . )

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/squeal_grammar_fwd_decls.hpp ${CMAKE_CURRENT_SOURCE_DIR}/squeal_grammar_main.hpp
    COMMAND metasqueal ${CMAKE_CURRENT_SOURCE_DIR}/squeal-grammar.txt ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS metasqueal ${CMAKE_CURRENT_SOURCE_DIR}/squeal-grammar.txt
)

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

add_library(parsesqueal
    squeal_grammar_fwd_decls.hpp
    squeal_grammar_main.hpp
    parser.cpp)
set_target_properties(parsesqueal PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
target_link_libraries(parsesqueal ICU::uc ICU::i18n)
