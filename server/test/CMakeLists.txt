include(FetchContent)
FetchContent_Declare(gtest
        QUIET
        URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
        )
# Configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)


add_executable(
        unit_tests
        testlib_add.cc
        testlib_subtract.cc
)

target_link_libraries(unit_tests
        PRIVATE
        testlib
        gtest_main
        )

# Automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(unit_tests
        PROPERTIES
        LABELS "unit"
        DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
        240
        )

add_subdirectory(domain)
add_subdirectory(repositories)
add_subdirectory(services)