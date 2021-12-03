add_executable(sqlite_repo_tests sqlite_repo_tests.cc)
target_link_libraries(sqlite_repo_tests gtest sqlite_repo domain_model)
target_include_directories(sqlite_repo_tests
        PRIVATE ${PROJECT_SOURCE_DIR}/src/repositories/sqlite
        PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_model
        PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_repository_interface
        PRIVATE ${PROJECT_SOURCE_DIR}/include/repositories

)