from conans import ConanFile, CMake, tools, AutoToolsBuildEnvironment, RunEnvironment, python_requires
from conans.errors import ConanInvalidConfiguration, ConanException
from conans.tools import os_info
import os, re, stat, fnmatch, platform, glob, traceback, shutil
from functools import total_ordering

# if you using python less than 3 use from distutils import strtobool
from distutils.util import strtobool

# conan runs the methods in this order:
# config_options(),
# configure(),
# requirements(),
# package_id(),
# build_requirements(),
# build_id(),
# system_requirements(),
# source(),
# imports(),
# build(),
# package(),
# package_info()

conan_build_helper = python_requires("conan_build_helper/[~=0.0]@conan/stable")

class chromium_base_conan_project(conan_build_helper.CMakePackage):
    name = "chromium_base"

    # Indicates License type of the packaged library
    # TODO (!!!)
    # license = "MIT"

    version = "master"

    # TODO (!!!)
    #url = "https://github.com/blockspacer/CXXCTP"

    description = "modified `base` library from chromium"
    topics = ('c++')

    options = {
        "shared": [True, False],
        "debug": [True, False],
        "enable_protoc_autoinstall": [True, False],
        "use_alloc_shim": [True, False],
        "use_deb_alloc": [True, False],
        "use_test_support": [True, False],
        "use_partition_alloc": [True, False],
        "enable_web_pthreads": [True, False],
        "enable_profiling": [True, False],
        "enable_ubsan": [True, False],
        "enable_asan": [True, False],
        "enable_msan": [True, False],
        "enable_tsan": [True, False],
        "enable_valgrind": [True, False]
    }

    default_options = (
        "shared=False",
        "debug=False",
        "enable_protoc_autoinstall=True",
        "enable_ubsan=False",
        "enable_asan=False",
        "enable_msan=False",
        "enable_tsan=False",
        "enable_valgrind=False",
        # requires to build tcmalloc with same `use_alloc_shim` flag
        "use_alloc_shim=False",
        "use_deb_alloc=False",
        "use_test_support=True",
        "use_partition_alloc=True",
        "enable_web_pthreads=False",
        "enable_profiling=False",
        # build
        "openssl:shared=True"
    )

    # Custom attributes for Bincrafters recipe conventions
    _source_subfolder = "."
    _build_subfolder = "."

    # NOTE: no cmake_find_package due to custom FindXXX.cmake
    generators = "cmake", "cmake_paths", "virtualenv"

    # Packages the license for the conanfile.py
    #exports = ["LICENSE.md"]

    # If the source code is going to be in the same repo as the Conan recipe,
    # there is no need to define a `source` method. The source folder can be
    # defined like this
    exports_sources = ("LICENSE", "VERSION", "*.md", "include/*", "src/*",
                       "cmake/*", "examples/*", "CMakeLists.txt", "tests/*", "benchmarks/*",
                       "scripts/*", "tools/*", "codegen/*", "assets/*",
                       "docs/*", "licenses/*", "patches/*", "resources/*",
                       "submodules/*", "thirdparty/*", "third-party/*",
                       "third_party/*", "base/*", "extensions/*", "starboard/*")

    settings = "os", "compiler", "build_type", "arch"

    # sets cmake variables required to use clang 10 from conan
    def _is_compile_with_llvm_tools_enabled(self):
      return self._environ_option("COMPILE_WITH_LLVM_TOOLS", default = 'false')

    # installs clang 10 from conan
    def _is_llvm_tools_enabled(self):
      return self._environ_option("ENABLE_LLVM_TOOLS", default = 'false')

    def _is_cppcheck_enabled(self):
      return self._environ_option("ENABLE_CPPCHECK", default = 'false')

    #def source(self):
    #  url = "https://github.com/....."
    #  self.run("git clone %s ......." % url)

    def configure(self):
        lower_build_type = str(self.settings.build_type).lower()

        if lower_build_type != "release" and not self._is_llvm_tools_enabled():
            self.output.warn('enable llvm_tools for Debug builds')

        if self._is_compile_with_llvm_tools_enabled() and not self._is_llvm_tools_enabled():
            raise ConanInvalidConfiguration("llvm_tools must be enabled")

        if self.options.enable_ubsan \
           or self.options.enable_asan \
           or self.options.enable_msan \
           or self.options.enable_tsan:
            if not self._is_llvm_tools_enabled():
                raise ConanInvalidConfiguration("sanitizers require llvm_tools")

        if self.options.use_alloc_shim:
          self.options["chromium_tcmalloc"].use_alloc_shim = True

        if self.options.enable_profiling:
          self.options["chromium_tcmalloc"].enable_profiling = True

        if self.options.enable_ubsan:
            if self._is_tests_enabled():
              self.options["conan_gtest"].enable_ubsan = True
              self.options["benchmark"].enable_ubsan = True
            if self._is_tests_enabled() or self.options.use_test_support:
              self.options["chromium_libxml"].enable_ubsan = True
            if self.settings.os == "Linux":
              self.options["chromium_libevent"].enable_ubsan = True
              self.options["chromium_xdg_user_dirs"].enable_ubsan = True
              self.options["chromium_xdg_mime"].enable_ubsan = True
            self.options["chromium_icu"].enable_ubsan = True
            self.options["chromium_dynamic_annotations"].enable_ubsan = True
            self.options["chromium_modp_b64"].enable_ubsan = True
            self.options["chromium_compact_enc_det"].enable_ubsan = True
            self.options["abseil"].enable_ubsan = True
            self.options["perfetto"].is_ubsan = True

        if self.options.enable_asan:
            if self._is_tests_enabled():
              self.options["conan_gtest"].enable_asan = True
              self.options["benchmark"].enable_asan = True
            if self._is_tests_enabled() or self.options.use_test_support:
              self.options["chromium_libxml"].enable_asan = True
            if self.settings.os == "Linux":
              self.options["chromium_libevent"].enable_asan = True
              self.options["chromium_xdg_user_dirs"].enable_asan = True
              self.options["chromium_xdg_mime"].enable_asan = True
            self.options["chromium_icu"].enable_asan = True
            self.options["chromium_dynamic_annotations"].enable_asan = True
            self.options["chromium_modp_b64"].enable_asan = True
            self.options["chromium_compact_enc_det"].enable_asan = True
            self.options["abseil"].enable_asan = True
            self.options["perfetto"].is_asan = True

        if self.options.enable_msan:
            if self._is_tests_enabled():
              self.options["conan_gtest"].enable_msan = True
              self.options["benchmark"].enable_msan = True
            if self._is_tests_enabled() or self.options.use_test_support:
              self.options["chromium_libxml"].enable_msan = True
            if self.settings.os == "Linux":
              self.options["chromium_libevent"].enable_msan = True
              self.options["chromium_xdg_user_dirs"].enable_msan = True
              self.options["chromium_xdg_mime"].enable_msan = True
            self.options["chromium_icu"].enable_msan = True
            self.options["chromium_dynamic_annotations"].enable_msan = True
            self.options["chromium_modp_b64"].enable_msan = True
            self.options["chromium_compact_enc_det"].enable_msan = True
            self.options["abseil"].enable_msan = True
            self.options["perfetto"].is_msan = True

        if self.options.enable_tsan:
            if self._is_tests_enabled():
              self.options["conan_gtest"].enable_tsan = True
              self.options["benchmark"].enable_tsan = True
            if self._is_tests_enabled() or self.options.use_test_support:
              self.options["chromium_libxml"].enable_tsan = True
            if self.settings.os == "Linux":
              self.options["chromium_libevent"].enable_tsan = True
              self.options["chromium_xdg_user_dirs"].enable_tsan = True
              self.options["chromium_xdg_mime"].enable_tsan = True
            self.options["chromium_icu"].enable_tsan = True
            self.options["chromium_dynamic_annotations"].enable_tsan = True
            self.options["chromium_modp_b64"].enable_tsan = True
            self.options["chromium_compact_enc_det"].enable_tsan = True
            self.options["abseil"].enable_tsan = True
            self.options["perfetto"].is_tsan = True

    def build_requirements(self):
        self.build_requires("cmake_platform_detection/master@conan/stable")
        self.build_requires("cmake_build_options/master@conan/stable")
        self.build_requires("cmake_helper_utils/master@conan/stable")
        # see https://chromium.googlesource.com/linux-syscall-support/+archive/29f7c7e018f4ce706a709f0b0afbf8bacf869480.tar.gz

        if self.options.enable_tsan \
            or self.options.enable_msan \
            or self.options.enable_asan \
            or self.options.enable_ubsan:
          self.build_requires("cmake_sanitizers/master@conan/stable")

        if self._is_cppcheck_enabled():
          self.build_requires("cppcheck_installer/1.90@conan/stable")

        # provides clang-tidy, clang-format, IWYU, scan-build, etc.
        if self._is_llvm_tools_enabled():
          self.build_requires("llvm_tools/master@conan/stable")

    def requirements(self):
        self.requires("chromium_build_util/master@conan/stable")
        self.requires("double-conversion/3.1.4@bincrafters/stable")

        if self._is_tests_enabled() or self.options.use_test_support:
            self.requires("chromium_libxml/stable@conan/stable")
            self.requires("conan_gtest/stable@conan/stable")
            self.requires("benchmark/v1.5.2@dev/stable")

        if self.settings.os == "Linux":
            self.requires("linux-syscall-support/cci.20200813")
            self.requires("chromium_libevent/master@conan/stable")
            self.requires("chromium_xdg_user_dirs/master@conan/stable")
            self.requires("chromium_xdg_mime/master@conan/stable")

            if not self.options.enable_asan \
               and not self.options.enable_tsan \
               and not self.options.enable_ubsan \
               and not self.options.enable_msan \
               and not self.options.enable_valgrind:
              self.requires("chromium_tcmalloc/master@conan/stable")

        self.requires("chromium_icu/master@conan/stable")

        self.requires("chromium_dynamic_annotations/master@conan/stable")
        self.requires("chromium_modp_b64/master@conan/stable", private=False)

        # todo: in WASM remove ced, replace with "unicode/ucsdet.h"
        # to make smaller binary
        self.requires("chromium_compact_enc_det/master@conan/stable")

        # NOTE: also update headers in `extensions/third_party/perfetto`
        self.requires("perfetto/v13.0@conan/stable")

        # NOTE: also update headers in `extensions/third_party/boringssl/src/include/openssl`
        self.requires("openssl/OpenSSL_1_1_1-stable@conan/stable")

        self.requires("fmt/master@dev/stable")

        self.requires("boost_iterator/1.69.0@bincrafters/stable")

        self.requires("boost_intrusive/1.69.0@bincrafters/stable")

        self.requires("boost_preprocessor/1.69.0@bincrafters/testing")

        # NOTE: also update headers in `extensions/third_party/abseil-cpp`
        self.requires("abseil/lts_2020_09_23@conan/stable")

        if self.options.enable_protoc_autoinstall:
            # TODO: https://github.com/gaeus/conan-grpc
            #self.requires("protobuf/3.6.1@bincrafters/stable")
            #self.requires("grpc_conan/v1.26.x@conan/stable")
            #self.requires("openssl/OpenSSL_1_1_1-stable@conan/stable")
            #self.requires("zlib/v1.2.11@conan/stable")
            #self.requires("c-ares/cares-1_15_0@conan/stable")
            self.requires("protobuf/v3.9.1@conan/stable")

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.parallel = True
        cmake.verbose = True

        cmake.definitions["BUILD_SHARED_LIBS"] = "ON" if self.options.shared else "OFF"

        cmake.definitions["CMAKE_BUILD_TYPE"] = self.settings.build_type

        cmake.definitions["ENABLE_VALGRIND"] = "ON" if self.options.enable_valgrind else "OFF"

        cmake.definitions["ENABLE_UBSAN"] = "ON" if self.options.enable_ubsan else "OFF"

        cmake.definitions["ENABLE_ASAN"] = "ON" if self.options.enable_asan else "OFF"

        cmake.definitions["ENABLE_MSAN"] = "ON" if self.options.enable_msan else "OFF"

        cmake.definitions["ENABLE_TSAN"] = "ON" if self.options.enable_tsan else "OFF"

        self.add_cmake_option(cmake, "ENABLE_TESTS", self._is_tests_enabled())

        self.add_cmake_option(cmake, "ENABLE_WEB_PTHREADS", self.options.enable_web_pthreads)

        self.add_cmake_option(cmake, "USE_ALLOC_SHIM", self.options.use_alloc_shim)

        self.add_cmake_option(cmake, "BASE_USE_PARTITION_ALLOCATOR", self.options.use_test_support)

        self.add_cmake_option(cmake, "USE_TEST_SUPPORT", self.options.use_partition_alloc)

        self.add_cmake_option(cmake, "USE_DEB_ALLOC", self.options.use_deb_alloc)

        self.add_cmake_option(cmake, "COMPILE_WITH_LLVM_TOOLS", self._is_compile_with_llvm_tools_enabled())

        cmake.configure(build_folder=self._build_subfolder, args=['--debug-trycompile'])

        return cmake

    def package(self):
        self.copy(pattern="LICENSE", dst="licenses", src=self._source_subfolder)
        cmake = self._configure_cmake()
        cmake.install()

        self.copy_conanfile_for_editable_package(".")

        self.rmdir_if_packaged('.git')
        self.rmdir_if_packaged('tests')
        self.rmdir_if_packaged('lib/tests')
        self.rmdir_if_packaged('lib/pkgconfig')

    def build(self):
        cmake = self._configure_cmake()
        if self.settings.compiler == 'gcc':
            cmake.definitions["CMAKE_C_COMPILER"] = "gcc-{}".format(
                self.settings.compiler.version)
            cmake.definitions["CMAKE_CXX_COMPILER"] = "g++-{}".format(
                self.settings.compiler.version)

        #cmake.definitions["CMAKE_TOOLCHAIN_FILE"] = 'conan_paths.cmake'

        # The CMakeLists.txt file must be in `source_folder`
        cmake.configure(source_folder=".", args=['--trace', '--debug-trycompile', '--debug-output'])

        cpu_count = tools.cpu_count()
        self.output.info('Detected %s CPUs' % (cpu_count))

        # -j flag for parallel builds
        cmake.build(args=["--", "-j%s" % cpu_count])

        if self._is_tests_enabled():
          self.output.info('Running tests')
          cmake.test(target="chromium_base_run_unittests", output_on_failure=True)

    # Importing files copies files from the local store to your project.
    def imports(self):
        dest = os.getenv("CONAN_IMPORT_PATH", "bin")
        self.copy("license*", dst=dest, ignore_case=True)
        self.copy("*.dll", dst=dest, src="bin")
        self.copy("*.so*", dst=dest, src="bin")
        self.copy("*.pdb", dst=dest, src="lib")
        self.copy("*.dylib*", dst=dest, src="lib")
        self.copy("*.lib*", dst=dest, src="lib")
        self.copy("*.a*", dst=dest, src="lib")

    # package_info() method specifies the list of
    # the necessary libraries, defines and flags
    # for different build configurations for the consumers of the package.
    # This is necessary as there is no possible way to extract this information
    # from the CMake install automatically.
    # For instance, you need to specify the lib directories, etc.
    def package_info(self):
        #self.cpp_info.libs = ["chromium_base"]

        self.cpp_info.includedirs = ["include"]
        self.cpp_info.libs = tools.collect_libs(self)
        self.cpp_info.libdirs = ["lib"]
        self.cpp_info.bindirs = ["bin"]
        self.env_info.LD_LIBRARY_PATH.append(
            os.path.join(self.package_folder, "lib"))
        self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))
        for libpath in self.deps_cpp_info.lib_paths:
            self.env_info.LD_LIBRARY_PATH.append(libpath)

        #self.cpp_info.includedirs.append(os.getcwd())
        #self.cpp_info.includedirs.append(
        #  os.path.join("base", "third_party", "icu"))
        #self.cpp_info.includedirs.append(
        #  os.path.join("base", "third_party", "icu", "compat"))

        #if self.settings.os == "Linux":
        #  self.cpp_info.defines.append('HAVE_CONFIG_H=1')

        # in linux we need to link also with these libs
        #if self.settings.os == "Linux":
        #    self.cpp_info.libs.extend(["pthread", "dl", "rt"])

        #self.cpp_info.libs = tools.collect_libs(self)
        #self.cpp_info.defines.append('PDFLIB_DLL')
