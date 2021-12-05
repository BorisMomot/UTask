add_subdirectory(sqlite)
add_subdirectory(curl)

add_library(repository
        project_repository.h project_repository.cc
        role_repository.h role_repository.cc
        task_repository.h task_repository.cc
        user_repository.h user_repository.cc
)

target_include_directories(repository
        PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_model
        PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_repository_interface
        PRIVATE ${PROJECT_SOURCE_DIR}/include/repositories
        PRIVATE ${PROJECT_SOURCE_DIR}/include/utils
)

target_link_libraries(repository sqlite_repo)