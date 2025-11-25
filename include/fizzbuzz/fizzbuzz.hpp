#pragma once

#include <stdexcept>
#include <string>
#include <vector>

/**
 * @namespace core
 * @brief Espace de nom principal pour la logique métier de l'application.
 */
namespace core {

/**
 * @class FizzBuzzGenerator
 * @brief Classe statique gérant la logique du problème FizzBuzz généralisé.
 * * Cette classe n'a pas vocation à être instanciée. Elle fournit une méthode
 * pur pour générer la séquence.
 */
class FizzBuzzGenerator {
public:
    /**
     * @brief Génère la séquence FizzBuzz selon les paramètres fournis.
     * * Cette méthode applique la logique de remplacement des multiples.
     * Complexité temporelle : O(limit).
     * * @param int1 Diviseur pour le premier remplacement (doit être > 0).
     * @param int2 Diviseur pour le deuxième remplacement (doit être > 0).
     * @param limit La limite supérieure de la séquence (inclusive).
     * @param str1 La chaîne utilisée pour remplacer les multiples de int1.
     * @param str2 La chaîne utilisée pour remplacer les multiples de int2.
     * @return std::vector<std::string> La liste des chaînes générées.
     * * @throws std::invalid_argument Si int1 ou int2 sont <= 0.
     */
    static std::vector<std::string> generate(int int1, int int2, int limit, const std::string& str1,
                                             const std::string& str2);
};

}  // namespace core
