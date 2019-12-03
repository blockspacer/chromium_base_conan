include_guard( DIRECTORY )

# Check if libatomic is needed
# see https://github.com/HewlettPackard/foedus_code/blob/master/foedus-core/cmake/FindGccAtomic.cmake
include(GNUInstallDirs)
include(CMakePushCheckState)
include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(CMakePackageConfigHelpers)
cmake_push_check_state()
check_cxx_source_compiles("
    #include <atomic>
    #include <stdint.h>
    int main() {
        std::atomic<int64_t> x;
        x = 1;
        x--;
        return (int) x;
    }"
    atomic64)
#if(NOT atomic64)
    # I'm also putting "atomic.so.1" because at least FC19 and Ubuntu's repo don't create
    # "libatomic.so" symlink. They only have libatomic.so.1.0.0 and libatomic.so.1 symlink. No idea why.
    find_library(ATOMIC
      NAMES
        atomic
        atomic.so.1
        libatomic.so
        libatomic.so.1
        libatomic.so.1.2.0
      HINTS
        $ENV{HOME}/local/lib64
        $ENV{HOME}/local/lib
        /usr/local/lib64
        /usr/local/lib
        /opt/local/lib64
        /opt/local/lib
        /usr/lib64
        /usr/lib
        /lib64
        /lib
        /usr/lib
        /usr/lib/x86_64-linux-gnu
        /opt/usr/lib
        /opt/usr/lib64
    )
    if(ATOMIC)
        set(LIBATOMIC ${ATOMIC})
        message(STATUS "Found libatomic: ${LIBATOMIC}")
    else()
        check_cxx_source_compiles("
            #include <atomic>
            #include <stdint.h>
            int main() {
                std::atomic<int32_t> x;
                x = 1;
                x--;
                return (int) x;
            }"
            atomic32)

        if(atomic32)
            message(FATAL_ERROR "Failed to find libatomic!")
        endif()
    endif(ATOMIC)
#endif(NOT atomic64)
cmake_pop_check_state()
