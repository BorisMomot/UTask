//
// Created by boris on 25.11.2021.
//

#ifndef GTEST_DEMO_DB_MANAGER_H
#define GTEST_DEMO_DB_MANAGER_H

#include <string>
#include <vector>

class DBManager{
public:
  typedef std::vector<std::string> tableRow;
  DBManager() {}
  virtual ~DBManager() {
  }

  virtual std::vector<tableRow> executeQuery(std::string query) = 0;
};


#endif // GTEST_DEMO_DB_MANAGER_H
