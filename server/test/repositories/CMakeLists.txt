add_executable(repo_tests user_repo_tests.cc)
target_link_libraries(repo_tests domain_model repository gtest gmock)
target_include_directories(repo_tests
        PRIVATE ${PROJECT_SOURCE_DIR}/src/repositories
        PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_model
        PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_repository_interface
        PRIVATE ${PROJECT_SOURCE_DIR}/include/repositories
)

add_subdirectory(sqlite)