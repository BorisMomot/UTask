find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLite REQUIRED IMPORTED_TARGET sqlite3)

add_library(sqlite_repo
        sqlite_repo.h sqlite_repo.cpp
        user_sqlite_helper.h user_sqlite_helper.cc
        table_info.h table_info.cpp table_info_creator.h
)

target_include_directories(sqlite_repo
        PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_model/
        PRIVATE ${PROJECT_SOURCE_DIR}/src/entities
)

target_link_libraries(sqlite_repo
        PUBLIC PkgConfig::SQLite
)
