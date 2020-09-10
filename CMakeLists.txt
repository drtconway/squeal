cmake_minimum_required(VERSION 3.16)

set(SQUEAL_VERSION "0.0.1")

project(squeal VERSION ${SQUEAL_VERSION} LANGUAGES CXX)

find_package(ICU REQUIRED COMPONENTS data i18n io test tu uc)

add_library(squeal INTERFACE)

target_compile_features(squeal INTERFACE cxx_std_17)

include_directories(include)

# testing
enable_testing()
option(SQUEAL_BUILD_TESTS "Build test programs" ON)
if(SQUEAL_BUILD_TESTS)
  add_subdirectory(src/test/squeal)
endif()

