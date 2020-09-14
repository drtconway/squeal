cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)

set(util_sources
  grammar2pegtl.cpp)

foreach(utilsourcefile ${util_sources})
    get_filename_component(exename ${utilsourcefile} NAME_WE)
    add_executable(${exename} ${utilsourcefile})
    set_target_properties(${exename} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )
    #target_compile_options(${exename} PRIVATE -pedantic -Wall -Wextra -Wshadow -Werror)
    target_include_directories(${exename} PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(${exename} ICU::uc ICU::i18n)
endforeach(utilsourcefile)
