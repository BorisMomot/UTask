find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLite REQUIRED IMPORTED_TARGET sqlite3)

add_library(sqlite_repo
        sqlite_manager.h sqlite_manager.cpp
        user_sqlite_helper.h user_sqlite_helper.cc
)

target_include_directories(sqlite_repo
        PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_model/
        PRIVATE ${PROJECT_SOURCE_DIR}/include/domain/domain_repository_interface/
        PRIVATE ${PROJECT_SOURCE_DIR}/include/repositories/
        PRIVATE ${PROJECT_SOURCE_DIR}/src/entities
)

target_link_libraries(sqlite_repo
        PUBLIC PkgConfig::SQLite
)
