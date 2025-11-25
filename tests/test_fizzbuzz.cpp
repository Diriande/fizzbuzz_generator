#include <gtest/gtest.h>

#include "../include/fizzbuzz/fizzbuzz.hpp"

// Test the canonical FizzBuzz case (3, 5)
TEST(FizzBuzzTest, CanonicalExample) {
    auto result = core::FizzBuzzGenerator::generate(3, 5, 16, "fizz", "buzz");

    ASSERT_EQ(result.size(), 16);
    EXPECT_EQ(result[0], "1");
    EXPECT_EQ(result[1], "2");
    EXPECT_EQ(result[2], "fizz");       // 3
    EXPECT_EQ(result[4], "buzz");       // 5
    EXPECT_EQ(result[5], "fizz");       // 6
    EXPECT_EQ(result[14], "fizzbuzz");  // 15
    EXPECT_EQ(result[15], "16");
}

// Test with different custom parameters
TEST(FizzBuzzTest, CustomParameters) {
    auto result = core::FizzBuzzGenerator::generate(2, 4, 5, "foo", "bar");
    // 1 -> 1
    // 2 -> foo (divisible by 2)
    // 3 -> 3
    // 4 -> foobar (divisible by 2 AND 4)
    // 5 -> 5

    EXPECT_EQ(result[1], "foo");
    EXPECT_EQ(result[3], "foobar");
}

// Test edge case: Limit is zero
TEST(FizzBuzzTest, ZeroLimit) {
    auto result = core::FizzBuzzGenerator::generate(3, 5, 0, "fizz", "buzz");
    EXPECT_TRUE(result.empty());
}

// Test validation: Divisor is zero
TEST(FizzBuzzTest, ZeroDivisorThrows) {
    EXPECT_THROW(core::FizzBuzzGenerator::generate(0, 5, 10, "fizz", "buzz"),
                 std::invalid_argument);
    EXPECT_THROW(core::FizzBuzzGenerator::generate(3, 0, 10, "fizz", "buzz"),
                 std::invalid_argument);
}

// Test validation: Negative divisor
TEST(FizzBuzzTest, NegativeDivisorThrows) {
    EXPECT_THROW(core::FizzBuzzGenerator::generate(-1, 5, 10, "fizz", "buzz"),
                 std::invalid_argument);
}
