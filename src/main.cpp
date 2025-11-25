/**
 * @file main.cpp
 * @brief Point d'entrée de l'application de génération FizzBuzz.
 * * Ce fichier gère l'interface en ligne de commande (CLI), le parsing des arguments
 * et l'affichage des résultats sur la sortie standard.
 */

#include <iostream>
#include <string>
#include <vector>

#include "../include/fizzbuzz/fizzbuzz.hpp"

/**
 * @brief Affiche l'aide d'utilisation du programme.
 * * @param program_name Le nom de l'exécutable (argv[0]).
 */
void print_usage(const char* program_name) {
    std::cerr << "Usage: " << program_name << " <int1> <int2> <limit> <str1> <str2>\n"
              << "Example: " << program_name << " 3 5 100 fizz buzz\n";
}

/**
 * @brief Fonction principale.
 * * @param argc Nombre d'arguments.
 * @param argv Tableau des arguments.
 * @return int Code de retour (0 pour succès, 1 pour erreur).
 */
int main(int argc, char* argv[]) {
    // 1. Vérification des arguments
    if (argc != 6) {
        print_usage(argv[0]);
        return 1;
    }

    try {
        // Parsing robuste avec vérification d'erreurs (C++11 std::stoi)
        int int1 = std::stoi(argv[1]);
        int int2 = std::stoi(argv[2]);
        int limit = std::stoi(argv[3]);
        std::string str1 = argv[4];
        std::string str2 = argv[5];

        // 2. Exécution de la logique métier
        auto result = core::FizzBuzzGenerator::generate(int1, int2, limit, str1, str2);

        // 3. Affichage (Format CSV)
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i];
            if (i != result.size() - 1) {
                std::cout << ",";
            }
        }
        std::cout << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Invalid numeric argument provided. " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
