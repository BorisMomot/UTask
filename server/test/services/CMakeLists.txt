add_executable(service_tests user_service_tests.cpp)
target_link_libraries(service_tests services domain_model repository gtest gmock)
target_include_directories(service_tests
        PRIVATE ${PROJECT_SOURCE_DIR}/src/repositories
        PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_model
        PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_repository_interface
        PRIVATE ${PROJECT_SOURCE_DIR}/include/repositories
        PRIVATE ${PROJECT_SOURCE_DIR}/src/services
        )