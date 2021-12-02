//
// Created by boris on 02.12.2021.
//

#ifndef GTEST_DEMO_DB_MANAGER_INTERFACE_H
#define GTEST_DEMO_DB_MANAGER_INTERFACE_H

#include <exception>
#include <sstream>
#include <string>
#include <vector>

class DBManagerInterfaceNullPtr:public std::exception {
public:
  const char *
  what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override {
    return "DBManager nullptr";
  }
};

class DBNotFoundItem: public std::exception {
public:
  const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override{
    return "Item not found";
  }
};

class DBCommandFailed: public std::exception {
  std::string error_;
public:
  explicit DBCommandFailed(std::string&& error): error_(error){}
  const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override {
    std::stringstream ss;
    ss << "Command failed, error: " << error_;
    return ss.str().c_str();
  }
};

class DBManagerInterface{
public:
  virtual bool init() = 0;
  virtual bool executeQuery(const std::string& query) = 0;
  virtual std::vector<std::vector<std::string>> getDataFromQuery(const std::string& query) = 0;
};

#endif // GTEST_DEMO_DB_MANAGER_INTERFACE_H
