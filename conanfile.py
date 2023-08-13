from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

class VzorRecipe(ConanFile):
    name = "vzor"
    version = "0.2.0"

    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    exports_sources = ['CMakeLists.txt', 'src/*', 'include/*', 'common/*', 'examples/*', 'tests/*']

    def skip_test(self):
        return self.conf.get("tools.build:skip_test", default=False)

    def should_test(self):
        return not self.options.shared and not self.skip_test()

    def requirements(self):
        self.requires('stb/cci.20220909')
        if self.should_test():
            self.test_requires('gtest/1.13.0')

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        
        tc = CMakeToolchain(self)
        tc.variables['BUILD_EXAMPLES'] = False
        tc.variables['BUILD_TESTING'] = self.should_test()
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if self.should_test():
            cmake.test()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ['vzor']
