#include "../include/fizzbuzz/fizzbuzz.hpp"

#include <algorithm>

namespace core {

std::vector<std::string> FizzBuzzGenerator::generate(int int1, int int2, int limit,
                                                     const std::string& str1,
                                                     const std::string& str2) {
    // Input validation ensures production stability
    if (int1 <= 0 || int2 <= 0) {
        throw std::invalid_argument("Divisors (int1, int2) must be positive integers.");
    }

    std::vector<std::string> result;
    if (limit < 1) {
        return result;  // Return empty vector if limit is less than start
    }

    // Pre-allocate memory to improve performance for large limits
    result.reserve(limit);

    for (int i = 1; i <= limit; ++i) {
        std::string current_token;
        bool match = false;

        // Check first divisor
        if (i % int1 == 0) {
            current_token += str1;
            match = true;
        }

        // Check second divisor
        if (i % int2 == 0) {
            current_token += str2;
            match = true;
        }

        // If no divisors matched, use the number itself
        if (!match) {
            current_token = std::to_string(i);
        }

        result.push_back(std::move(current_token));
    }

    return result;
}

}  // namespace core
