add_library(services user_service.h user_service.cc)

target_include_directories(services PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_model)
target_include_directories(services PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_repository_interface)
target_include_directories(services PRIVATE ${PROJECT_SOURCE_DIR}/include/repositories)
target_include_directories(services PUBLIC ${PROJECT_SOURCE_DIR}/include/domain/domain_service_interface)
target_include_directories(services PUBLIC ${PROJECT_SOURCE_DIR}/include/services)

target_link_libraries(services repository sqlite_repo)
target_include_directories(services PUBLIC repository)
target_include_directories(services PUBLIC sqlite_repo)