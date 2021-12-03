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

class SQLiteManager: public DBManagerInterface {
  const std::string db_address_;
  sqlite3* db;


public:
  explicit SQLiteManager(const std::string db_address);
  ~SQLiteManager();
  bool init() override;
  bool executeQuery(const std::string &query) override;
  std::vector<std::vector<std::string>>
  getDataFromQuery(const std::string &query) override;
};

#endif // GTEST_DEMO_SQLITE_MANAGER_H
