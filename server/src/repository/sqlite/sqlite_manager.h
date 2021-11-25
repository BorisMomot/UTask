//
// Created by boris on 25.11.2021.
//

#ifndef GTEST_DEMO_SQLITE_MANAGER_H
#define GTEST_DEMO_SQLITE_MANAGER_H

#include "db_manager.h"
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>

class SQLiteManager: public DBManager {
  const std::string db_address_;
  sqlite3* db;

  void init();

public:
  explicit SQLiteManager(const std::string db_address);
  ~SQLiteManager() override;
  virtual std::vector<tableRow> executeQuery(std::string query) override;
};

#endif // GTEST_DEMO_SQLITE_MANAGER_H
