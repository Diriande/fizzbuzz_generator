# FizzBuzz Enterprise Edition

Une implémentation robuste, modulaire et configurable du célèbre problème "FizzBuzz" en C++17 moderne.

## Fonctionnalités

Cette application est une version généralisée qui accepte 5 paramètres :
- Deux diviseurs entiers (`int1`, `int2`).
- Une limite supérieure (`limit`).
- Deux chaînes de caractères de remplacement (`str1`, `str2`).

Elle génère une séquence de 1 à `limit` où :
- Les multiples de `int1` sont remplacés par `str1`.
- Les multiples de `int2` sont remplacés par `str2`.
- Les multiples des deux sont remplacés par la concaténation `str1str2`.

## Prérequis

- Un compilateur C++ compatible C++17 (GCC, Clang, MSVC).
- [CMake](https://cmake.org/) (3.15+).
- [Conan](https://conan.io/) (2.0+) pour la gestion des dépendances (Google Test).
- L'outil de construction `make` ou équivalent.

## Installation et Compilation

1. **Installer les dépendances avec Conan :**
   ```bash
   conan profile detect --force
   conan install . --build=missing
   ```

2. **Configurer et compiler avec CMake :**
   ```bash
   cmake --preset conan-release
   cmake --build --preset conan-release
   ```

## Utilisation

L'exécutable se trouve dans le dossier `build/` (ou `build/Release` sous Windows).

**Syntaxe :**
```bash
./fizzbuzz_app <int1> <int2> <limit> <str1> <str2>
```

**Exemple :**
Pour reproduire le FizzBuzz classique jusqu'à 16 :
```bash
./fizzbuzz_app 3 5 16 fizz buzz
# Sortie : 1,2,fizz,4,buzz,fizz,7,8,fizz,buzz,11,fizz,13,14,fizzbuzz,16
```

## Tests Unitaires

Le projet utilise Google Test. Pour lancer la suite de tests :

```bash
ctest --preset conan-release --output-on-failure
```
