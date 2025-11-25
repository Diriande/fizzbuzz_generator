from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from typing import Dict, Any


class FizzBuzzRecipe(ConanFile):
    name = "fizzbuzz_app"
    version = "1.0.0"

    # Réglages gérés par les profils Conan
    settings = "os", "compiler", "build_type", "arch"

    # Type : appli (lib + exe dans ton CMake)
    package_type = "application"

    # Pas d’options particulières ici
    options: Dict[str, Any] = {}
    default_options: Dict[str, Any] = {}

    # Fichiers à exporter dans la source du package
    exports_sources = (
        "CMakeLists.txt",
        "src/*",
        "tests/*",
    )

    def layout(self):
        # Génère :
        #  - src_folder = .
        #  - build/<build_type>/...
        cmake_layout(self)

    def requirements(self):
        # Même version que ton txt, mais tu peux la monter si tu veux
        self.requires("gtest/1.14.0")

    def generate(self):
        # Génère les fichiers de dépendances pour CMake
        deps = CMakeDeps(self)
        deps.generate()

        # Génère le toolchain CMake
        tc = CMakeToolchain(self)

        # Force C++17 ( >14 comme demandé )
        tc.variables["CMAKE_CXX_STANDARD"] = "17"
        tc.variables["CMAKE_CXX_STANDARD_REQUIRED"] = "ON"

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        # Optionnel si tu utilises juste "install + build" à la main,
        # mais utile si tu fais conan create + package
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        # Pas nécessairement utile ici, on ne consomme pas le package ailleurs
        pass
