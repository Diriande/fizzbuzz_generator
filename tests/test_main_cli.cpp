#include <gtest/gtest.h>

#include <array>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>

// Fonction utilitaire pour exécuter un programme et capturer stdout
std::string run_command(const std::string& cmd, int& exit_code) {
    std::array<char, 128> buffer{};
    std::string output;

#if defined(_WIN32)
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd.c_str(), "r"), _pclose);
#else
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
#endif

    if (!pipe) {
        throw std::runtime_error("Failed to run command");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        output += buffer.data();
    }

#if defined(_WIN32)
    exit_code = _pclose(pipe.get());
#else
    exit_code = WEXITSTATUS(pclose(pipe.get()));
#endif

    return output;
}

static const std::string BINARY = "./fizzbuzz_app";

// ----------------------------------------------------
// Test 1 — Pas assez d’arguments → erreur + exit code 1
// ----------------------------------------------------
TEST(MainCliTest, NotEnoughArguments) {
    int exit_code = 0;
    std::string out = run_command(BINARY, exit_code);

    EXPECT_EQ(exit_code, 1);
    EXPECT_TRUE(out.find("Usage:") != std::string::npos);
}

// ----------------------------------------------------
// Test 2 — Mauvais arguments numériques → exception stoi
// ----------------------------------------------------
TEST(MainCliTest, InvalidNumericArgument) {
    int exit_code = 0;
    std::string out = run_command(BINARY + " a 5 10 fizz buzz", exit_code);

    EXPECT_EQ(exit_code, 1);
    EXPECT_TRUE(out.find("Invalid numeric argument") != std::string::npos);
}

// Test 3 — Test CLI complet (CSV output)
TEST(MainCliTest, ValidFizzBuzzCsvOutput) {
    int exit_code = 0;
    std::string out = run_command(BINARY + " 3 5 15 fizz buzz", exit_code);

    EXPECT_EQ(exit_code, 0);

    std::string expected = "1,2,fizz,4,buzz,fizz,7,8,fizz,buzz,11,fizz,13,14,fizzbuzz\n";

    EXPECT_EQ(out, expected);
}
