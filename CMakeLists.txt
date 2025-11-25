cmake_minimum_required(VERSION 3.15)
project(FizzBuzzApp VERSION 1.0.0 LANGUAGES CXX)

# Require C++11 as requested (or newer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_CODE_COVERAGE "Enable coverage flags" OFF)

if(ENABLE_CODE_COVERAGE)
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(--coverage -O0 -g)
        add_link_options(--coverage)
    endif()
endif()

# --- Dependencies ---
# Using find_package to locate GTest provided by Conan
find_package(GTest CONFIG REQUIRED)

# --- Library ---
# Build the logic as a library for modularity and testability
add_library(fizzbuzz_lib
    src/fizzbuzz.cpp
    include/fizzbuzz/fizzbuzz.hpp
)
target_include_directories(fizzbuzz_lib PUBLIC src)

# --- Main Executable ---
add_executable(fizzbuzz_app src/main.cpp)
target_link_libraries(fizzbuzz_app PRIVATE fizzbuzz_lib)

# --- Testing ---
enable_testing()

add_executable(fizzbuzz_test tests/test_fizzbuzz.cpp)
target_link_libraries(fizzbuzz_test PRIVATE fizzbuzz_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(fizzbuzz_test)
