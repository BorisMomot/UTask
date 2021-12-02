add_library(domain_model
        user.cc
        task.cc
        role.cc
        project.cc
        filter.cc
)
target_include_directories(domain_model PUBLIC ${PROJECT_SOURCE_DIR}/include/domain/domain_model)
target_link_libraries(domain_model gcov)
# for code coverage
target_compile_options(domain_model PUBLIC "--coverage")
target_link_options(domain_model INTERFACE "--coverage")
