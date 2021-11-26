include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.10.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

    message("Poppulated!!!!")
endif()

add_executable(sqlite_manager_tests sqlite_manager_tests.cpp)
target_link_libraries(sqlite_manager_tests PUBLIC sqlite_repo gmock)
target_include_directories(sqlite_manager_tests PRIVATE gmock)

# Automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(sqlite_manager_tests
        PROPERTIES
            LABELS "sqlite_repo"
            DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
            240
)