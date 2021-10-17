add_library(testlib)
target_sources(testlib PRIVATE testlib.cc PUBLIC testlib.h)
target_include_directories(testlib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

# for code coverage
target_compile_options(testlib PUBLIC "--coverage")
target_link_options(testlib INTERFACE "--coverage")

add_subdirectory(pistache_server)
