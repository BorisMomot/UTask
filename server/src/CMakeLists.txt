add_subdirectory(pistache_server)
add_subdirectory(core)
add_subdirectory(repository)
#######################################################################################################
# Test
#######################################################################################################
add_library(testlib)
target_sources(testlib PRIVATE testlib.cc PUBLIC testlib.h)
target_include_directories(testlib PUBLIC ${CMAKE_CURRENT_LIST_DIR} PUBLIC ${PROJECT_SOURCE_DIR}/src/infrastructure/controllers)

# for code coverage
target_compile_options(testlib PUBLIC "--coverage")
target_link_options(testlib INTERFACE "--coverage" )
#target_link_libraries(testlib logger)

