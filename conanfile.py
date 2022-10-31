from conans import ConanFile, CMake, tools

class LoggerConan(ConanFile):
    name = "Logger"
    version = "0.4"
    license = "Copyright Dark Francis 2021"
    author = "Dark Francis dark.francis.dod@gmail.com"
    url = "https://github.com/darkFrancis/Logger"
    
    description = "Basic Qt logger used for projects"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": True, "fPIC": True}
    generators = "cmake"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def source(self):
        self.run("git clone git@github.com:darkFrancis/Logger.git")

    def build(self):
        cmake = CMake(self)
        cmake.definitions["DEFINED_VERSION"] = self.version
        cmake.configure(source_folder="Logger")
        cmake.build()

    def requirements(self):
        self.requires("CommonQtCMake/0.1@yggdrasil/stable")
        self.requires("qt/5.15.3")

    def package(self):
        self.copy("*.h", dst="include", src="Logger/inc")
        self.copy("*.hpp", dst="include", src="Logger/inc")
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

