find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLite REQUIRED IMPORTED_TARGET sqlite3)

add_library(sqlite_repo sqlite_repo.h sqlite_repo.cpp table_info.h table_info.cpp table_info_creator.h )
target_include_directories(sqlite_repo PRIVATE ${PROJECT_SOURCE_DIR}/src/core)
target_link_libraries(sqlite_repo PUBLIC PkgConfig::SQLite)
