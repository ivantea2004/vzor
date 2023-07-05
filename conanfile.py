from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.microsoft import is_msvc_static_runtime

class Test1Recipe(ConanFile):
    name = "vzor"
    version = "0.1.0"

    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    exports_sources = ['CMakeLists.txt', 'src/*', 'include/*', 'loader/*', 'examples/*', 'images/*', 'test/*']

    def requirements(self):
       self.requires('stb/cci.20220909')
       self.test_requires('gtest/1.13.0')

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

    def skip_test(self):
        return self.conf.get("tools.build:skip_test", default=False)

    def generate(self):
        
        tc = CMakeToolchain(self)
        tc.variables['ENABLE_STATIC_RUNTIME'] = is_msvc_static_runtime(self)
        tc.variables['BUILD_EXAMPLES'] = True
        tc.variables['BUILD_SHARED_LIBS'] = False
        tc.variables['BUILD_TESTING'] = not self.skip_test()
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ['vzor']
