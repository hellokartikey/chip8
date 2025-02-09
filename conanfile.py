from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout


class CHIP8(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("fmt/11.1.1")
        self.requires("raylib/5.0")

    def build_requirements(self):
        self.test_requires("gtest/1.15.0")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
