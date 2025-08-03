from conan import ConanFile
from conan.tools.cmake import cmake_layout

class ExampleRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("boost/1.88.0", options={"header_only": True})
        self.requires("gtest/1.16.0")

    def layout(self):
        cmake_layout(self)  