#include <gtest/gtest.h>

#include <array>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>

// Fonction utilitaire pour exécuter un programme et capturer stdout
std::string run_command(const std::string& cmd, int& exit_code) {
    std::array<char, 256> buffer{};
    std::string output;

    // On redirige stderr vers stdout pour tout capturer
    std::string full_cmd = cmd + " 2>&1";

    FILE* pipe = popen(full_cmd.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("popen() failed");
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        output += buffer.data();
    }

    int status = pclose(pipe);

#ifdef WEXITSTATUS
    if (status == -1) {
        exit_code = -1;
    } else {
        exit_code = WEXITSTATUS(status);
    }
#else
    exit_code = status;
#endif

    return output;
}

static const std::string BINARY = "./fizzbuzz_app";

// Test 1 — Pas assez d’arguments → erreur + exit code 1
TEST(MainCliTest, NotEnoughArguments) {
    int exit_code = 0;
    std::string out = run_command(BINARY, exit_code);

    EXPECT_EQ(exit_code, 1);
    EXPECT_TRUE(out.find("Usage:") != std::string::npos);
}

// Test 2 — Mauvais arguments numériques → exception stoi
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
