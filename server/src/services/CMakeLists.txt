add_library(services user_service.h user_service.cc)

target_include_directories(services PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_model)
target_include_directories(services PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_repository_interface)
target_include_directories(services PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_service_interface)