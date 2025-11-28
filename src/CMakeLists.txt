#
# Library and executable for FizzBuzz core and CLI
#

# --- Library ---
# Build the logic as a library for modularity and testability
add_library(fizzbuzz_lib
    fizzbuzz.cpp
    ../include/fizzbuzz/fizzbuzz.hpp
)

# Public headers live in the top-level include/ directory
target_include_directories(fizzbuzz_lib
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/../include
)

# --- Main Executable ---
add_executable(fizzbuzz_app main.cpp)
target_link_libraries(fizzbuzz_app PRIVATE fizzbuzz_lib)
