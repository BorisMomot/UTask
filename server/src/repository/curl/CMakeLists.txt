include(FindPkgConfig)
pkg_check_modules(CURL libcurl REQUIRED)

add_library(curl_repo curl_repo.h curl_repo.cc)
target_include_directories(curl_repo PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(curl_repo ${CURL_LIBRARIES})

# Тестовый бинарник пощупать библиотеку
add_executable(curl_test curl_test.cpp)
target_include_directories(curl_test PRIVATE ${CURL_INCLUDE_DIRS} PRIVATE)
target_link_libraries(curl_test ${CURL_LIBRARIES})

# Второй тестовый бинарник
add_executable(curl_rx curl_rx.cpp)
target_include_directories(curl_rx
        PRIVATE ${CURL_INCLUDE_DIRS}
        PRIVATE ${CMAKE_INSTALL_OLDINCLUDEDIR}/rxcpp/
        PRIVATE ${PROJECT_SOURCE_DIR}/include
        )
target_link_libraries(curl_rx ${CURL_LIBRARIES} Threads::Threads)