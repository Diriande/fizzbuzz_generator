#
# Test targets for FizzBuzz (unit tests + CLI tests)
#

enable_testing()

add_executable(fizzbuzz_test
    test_fizzbuzz.cpp
    test_main_cli.cpp
)

target_link_libraries(fizzbuzz_test
    PRIVATE
        fizzbuzz_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(fizzbuzz_test)
