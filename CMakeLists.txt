cmake_minimum_required(VERSION 3.15)
project(FizzBuzzApp VERSION 1.0.0 LANGUAGES CXX)

# Require C++11 as requested (or newer). We use C++17 here.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_CODE_COVERAGE "Enable coverage flags" OFF)

if(ENABLE_CODE_COVERAGE)
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(--coverage -O0 -g)
        add_link_options(--coverage)
    endif()
endif()

# --- Dependencies (provided by Conan) ---
find_package(GTest CONFIG REQUIRED)

# --- Subdirectories ---
add_subdirectory(src)
add_subdirectory(tests)
