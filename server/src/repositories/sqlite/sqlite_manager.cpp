//
// Created by boris on 25.11.2021.
//
#include <sstream>
#include "sqlite_manager.h"
bool SQLiteManager::init() {
  // Init connection
  auto rc = sqlite3_open(db_address_.c_str(), &db);
  if (rc){
    std::cerr << "Couldn't open db" << std::endl;
  } else {
    std::cout << "Open successfully" << std::endl;
  }
  return true;
}
//--------------------------------------------------------------------------v
SQLiteManager::SQLiteManager(const std::string db_address) {
  init();
}
//--------------------------------------------------------------------------
std::vector<std::vector<std::string>> SQLiteManager::getDataFromQuery(const std::string& query) {
  std::vector<std::vector<std::string>> result;
  // Execute SQL query
  char *errorMsg = 0;
  auto callback_l = [](void* data, int argc, char** argv, char** azColName) -> int {
    auto res = reinterpret_cast<std::vector<std::vector<std::string>>&> (data);
    std::vector<std::string> row;
    for(int i=0; i < argc; ++i){
//        std::cout << azColName[i] << " = " << (argv[i] ? argv[i]: "NULL") << std::endl;
      row.emplace_back((argv[i] ? argv[i]: "NULL"));
    }
    res.emplace_back(row);
    return 0;
  };

  auto rc = sqlite3_exec(db, query.c_str(), callback_l , (void*)&result, &errorMsg);
  if ( rc != SQLITE_OK) {
    std::cerr << "Error: " << errorMsg << std::endl;
    std::stringstream ss;
    ss << errorMsg;
    sqlite3_free(errorMsg);
    throw (ss.str());
  } else {
    std::cout << "[SUCCESS] Execute:" << query << std::endl;
  }

  return result;
}
SQLiteManager::~SQLiteManager() {
  sqlite3_close(db);
}

bool SQLiteManager::executeQuery(const std::string &query) { return false; }

