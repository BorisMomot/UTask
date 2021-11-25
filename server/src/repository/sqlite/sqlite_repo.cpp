//
// Created by boris on 15.11.2021.
//

#include "sqlite_repo.h"
#include <sstream>

SQLiteRepo::~SQLiteRepo() {
  delete manager;
}
bool SQLiteRepo::saveProjectData(const Project role) { return false; }
bool SQLiteRepo::saveRoleData(const Role role) { return false; }
bool SQLiteRepo::saveUserData(const User user) { return false; }
bool SQLiteRepo::saveTaskData(const Project project) { return false; }

std::list<Project> SQLiteRepo::getProjects(const Filter &filter) {
  return std::list<Project>();
}
std::list<Project> SQLiteRepo::getProjects(const std::string filterField,
                                           const std::string FliterValue) {
  return std::list<Project>();
}
std::list<Project> SQLiteRepo::getProjects() { return std::list<Project>(); }
std::list<Role> SQLiteRepo::getRole(const Filter &filter) {
  return std::list<Role>();
}
std::list<Role> SQLiteRepo::getRole(const std::string filterField,
                                    const std::string FliterValue) {
  return std::list<Role>();
}
std::list<Role> SQLiteRepo::getRole() { return std::list<Role>(); }
std::list<User> SQLiteRepo::getUser(const Filter &filter) {
  return std::list<User>();
}
std::list<User> SQLiteRepo::getUser(const std::string filterField,
                                    const std::string FliterValue) {
  return std::list<User>();
}
std::list<User> SQLiteRepo::getUser() { return std::list<User>(); }
std::list<Task> SQLiteRepo::getTasks(const Filter &filter) {
  return std::list<Task>();
}
std::list<Task> SQLiteRepo::getTasks(const std::string filterField,
                                     const std::string FliterValue) {
  return std::list<Task>();
}
std::list<Task> SQLiteRepo::getTasks() { return std::list<Task>(); }
//------------------------------------------------------------------------------
SQLiteRepo::SQLiteRepo(const std::string &dbAddress) {
  manager = new SQLiteManager("test.db");

}
//------------------------------------------------------------------------------
bool SQLiteRepo::createProjectTable() {
  TableInfoSQLiteFactory tableInfoSqLiteFactory;
  auto projectTableInfo = tableInfoSqLiteFactory.createProjectTable();
  return createTableCommand(projectTableInfo);
}
bool SQLiteRepo::createRoleTable() {
  TableInfoSQLiteFactory tableInfoSqLiteFactory;
  auto roleTableInfo = tableInfoSqLiteFactory.createRoleTable();
  return createTableCommand(roleTableInfo);
}
bool SQLiteRepo::createTaskTable() {
  TableInfoSQLiteFactory tableInfoSqLiteFactory;
  auto taskTableInfo = tableInfoSqLiteFactory.createTaskTable();
  return createTableCommand(taskTableInfo);
}
bool SQLiteRepo::createUserTable() {
  TableInfoSQLiteFactory tableInfoSqLiteFactory;
  auto userTableInfo = tableInfoSqLiteFactory.createUserTable();
  return createTableCommand(userTableInfo);
}
bool SQLiteRepo::createUserRolesTable() {
  TableInfoSQLiteFactory tableInfoSqLiteFactory;
  auto userRolesTableInfo = tableInfoSqLiteFactory.createUsersRoles();
  return createTableCommand(userRolesTableInfo);
}

//------------------------------------------------------------------------------
bool SQLiteRepo::projectTableExist() { return false; }
bool SQLiteRepo::roleTableExist() { return false; }
bool SQLiteRepo::taskTableExist() { return false; }
bool SQLiteRepo::userTableExist() { return false; }
bool SQLiteRepo::userRolesTableExist() { return false; }


bool SQLiteRepo::createTableCommand(TableInfo &tableInfo) {
  std::ostringstream command;
  command << "CREATE TABLE " << tableInfo.getTableName() << " (";
  for (const auto& p:tableInfo.getColumsProperties()){
    command << " " <<  p.first << " ";
    for (const auto& s: p.second){
      command << " " << s;
    }
  }
  try {
    manager->executeQuery(command.str());
  } catch (...) {
    return false;
  }
  return true;
}
