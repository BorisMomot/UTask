include(FindPkgConfig)
pkg_check_modules(CURL libcurl REQUIRED)

add_library(curl_repo curl_repo.h curl_repo.cc)
target_include_directories(curl_repo PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(curl_repo ${CURL_LIBRARIES})