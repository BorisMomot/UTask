//
// Created by boris on 25.11.2021.
//

#ifndef GTEST_DEMO_SQLITE_MANAGER_H
#define GTEST_DEMO_SQLITE_MANAGER_H

#include <db_manager_interface.h>
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>
/**
 * \brief Class to handle basic query to SQLite
 */
class SQLiteManager: public DBManagerInterface {
  const std::string db_address_;
  sqlite3* db; ///< ptr to work with db

public:
  explicit SQLiteManager(const std::string db_address);
  ~SQLiteManager();
  bool init() override; ///< init ptr
  /**
   * Function for execution queries that return true or false
   * Example create table, table exist and so on
   * @param query to Database
   * @return true if everything ok, false if command failed
   */
  bool executeQuery(const std::string &query) override;
  /**
   * Execution return data from DB
   * @param query to Database
   * @return if everythig right returns data
   */
  std::vector<std::vector<std::string>>
  getDataFromQuery(const std::string &query) override;
};

#endif // GTEST_DEMO_SQLITE_MANAGER_H
