from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, cmake_layout
from conan.tools.scm import Version
from conan.errors import ConanInvalidConfiguration

class ExampleRecipe(ConanFile):
    name = "Calculator"
    description = "A simple calculator application supporting basic arithmetic operations."
    version = "0.1.0"

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"  
    
    def requirements(self):
        self.requires("boost/1.88.0")
        self.requires("gtest/1.16.0")
        self.requires("qt/6.8.3")

    def configure(self):
        self.options["qt/*"].shared = True
        self.options["qt/*"].qtquickcontrols = True
        self.options["qt/*"].qtquickcontrols2 = True
        self.options["qt/*"].qtdeclarative = True
        self.options["qt/*"].qttools = True
        self.options["qt/*"].with_vulkan = False
        self.options["qt/*"].gui = True
        self.options["qt/*"].qtqmltools = True
        self.options["qt/*"].qtquicktools = True
        self.options["qt/*"].qtshadertools = True
        self.options["qt/*"].qttranslations = True
        self.options["qt/*"].qtsvg = True
        self.options["qt/*"].opengl = "desktop"
        self.options["qt/*"].qttest = True    

        # Boost options
        self.options["boost/*"].header_only = True

    def layout(self):
        self.folders.build_folder_vars = ["settings.os", "settings.compiler", "settings.compiler.version", "settings.arch", "settings.build_type"]
        cmake_layout(self)  

    def validate(self):
        # Validate compiler supports C++17
        if self.settings.compiler == "gcc" and Version(self.settings.compiler.version) < Version("7"):
            raise ConanInvalidConfiguration("GCC >= 7 is required for C++17 support")
        elif self.settings.compiler == "clang" and Version(self.settings.compiler.version) < Version("5"):
            raise ConanInvalidConfiguration("Clang >= 5 is required for C++17 support")
        elif self.settings.compiler == "msvc" and Version(self.settings.compiler.version) < Version("15.8"):
            raise ConanInvalidConfiguration("Visual Studio 2017 or higher is required for C++17 support")

    def build(self):
        from conan.tools.cmake import CMake
        cmake = CMake(self)
        cmake.configure()
        cmake.build()