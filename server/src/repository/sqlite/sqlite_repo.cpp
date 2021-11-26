//
// Created by boris on 15.11.2021.
//

#include "sqlite_repo.h"
#include <sstream>


// Construct/Destruct
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
SQLiteRepo::SQLiteRepo(DBManager& dbManager) :
    manager(dbManager),
    projectTableInfo(tableInfoSqLiteFactory.createProjectTable()),
    roleTableInfo(tableInfoSqLiteFactory.createRoleTable()),
    taskTableInfo(tableInfoSqLiteFactory.createTaskTable()),
    userTableInfo(tableInfoSqLiteFactory.createUserTable()),
    userRolesTableInfo(tableInfoSqLiteFactory.createUsersRoles())
{
}
//------------------------------------------------------------------------------
SQLiteRepo::~SQLiteRepo() {
}
// Create tables
//------------------------------------------------------------------------------
bool SQLiteRepo::createProjectTable() {
  return createTableCommand(projectTableInfo);
}
bool SQLiteRepo::createRoleTable() {
  return createTableCommand(roleTableInfo);
}
bool SQLiteRepo::createTaskTable() {
  return createTableCommand(taskTableInfo);
}
bool SQLiteRepo::createUserTable() {
  return createTableCommand(userTableInfo);
}
bool SQLiteRepo::createUserRolesTable() {
  return createTableCommand(userRolesTableInfo);
}
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
    manager.executeQuery(command.str());
  } catch (...) {
    return false;
  }
  return true;
}
// Check that tables exists
//------------------------------------------------------------------------------
bool SQLiteRepo::projectTableExist() {
  return checkTableExist(projectTableInfo.getTableName());
}
bool SQLiteRepo::roleTableExist() {
  return checkTableExist(roleTableInfo.getTableName());
}
bool SQLiteRepo::taskTableExist() {
  return checkTableExist(taskTableInfo.getTableName());
}
bool SQLiteRepo::userTableExist() {
  return checkTableExist(userTableInfo.getTableName());
}
bool SQLiteRepo::userRolesTableExist() {
  return checkTableExist(userRolesTableInfo.getTableName());
}

bool SQLiteRepo::checkTableExist(const std::string &tableName) {
  try {
    auto res = manager.executeQuery(
        "SELECT name FROM sqlite_master WHERE type='table' AND name='{" +
        tableName + "}';");
    if (!res.empty()){
      if (*res[0].begin() != "NULL"){
        return true;
      }
    } else {
      return false;
    }

  } catch (...) {
    return false;
  }
  return false;
}
// Save values to DB
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool SQLiteRepo::saveProjectData(const Project project) {
  // Example of query
  // "INSERT INTO PROJECT (NAME,DESCRIPTION) "  \
  // "VALUES ('MyTestProject', 'Test' ); "
  std::string columnNames;
  // first id - don't set manualy
  // all except last properties with coma
  for(int i = 1; i < projectTableInfo.getColumsNames().size() - 1; ++i){
    columnNames += projectTableInfo.getColumsNames()[i] + ", ";
  }
  // last properties without coma
  columnNames += *projectTableInfo.getColumsNames().end();

  std::string projectValues = "'" + project.getName() + "', '" + project.getDescription() + "'" ;
  try {
    manager.executeQuery("INSERT INTO " + projectTableInfo.getTableName() + " ( " + columnNames + ")"
                      + "VALUES ( " + projectValues +" );");
    return true;
  } catch (...) {
    return false;
  }
}
bool SQLiteRepo::saveRoleData(const Role role) {
  // Example of query
  // "INSERT INTO ROLE (NAME,DESCRIPTION) "  \
  // "VALUES ('MyTestProject', 'Test' ); "
  std::string columnNames;
  for(int i = 1; i < roleTableInfo.getColumsProperties().size(); ++i) {
    columnNames += roleTableInfo.getColumsNames()[i] + ", ";
  }
  columnNames += *roleTableInfo.getColumsNames().end();

  std::string roleValues =  "'" + role.getName() + "', '" + role.getDescription() + "'" ;
  try {
    manager.executeQuery("INSERT INTO " + roleTableInfo.getTableName() + " ( " + columnNames + " )"
                          + "VALUES ( " + roleValues + " );");
    return true;
  } catch (...) {
    return false;
  }
}
bool SQLiteRepo::saveUserData(const User user) { return false; }
bool SQLiteRepo::saveTaskData(const Project project) { return false; }
// Get Values from DB
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Projects
//------------------------------------------------------------------------------
std::list<Project> SQLiteRepo::getProjects(const Filter &filter) {
  return std::list<Project>();
}
std::list<Project> SQLiteRepo::getProjects(const std::string filterField,
                                           const std::string FliterValue) {
  return std::list<Project>();
}
std::list<Project> SQLiteRepo::getProjects() { return std::list<Project>(); }
// Roles
//------------------------------------------------------------------------------

std::list<Role> SQLiteRepo::getRole(const Filter &filter) {
  return std::list<Role>();
}
std::list<Role> SQLiteRepo::getRole(const std::string filterField,
                                    const std::string FliterValue) {
  return std::list<Role>();
}
std::list<Role> SQLiteRepo::getRole() { return std::list<Role>(); }
// Users
//------------------------------------------------------------------------------
std::list<User> SQLiteRepo::getUser(const Filter &filter) {
  return std::list<User>();
}
std::list<User> SQLiteRepo::getUser(const std::string filterField,
                                    const std::string FliterValue) {
  return std::list<User>();
}
std::list<User> SQLiteRepo::getUser() { return std::list<User>(); }
// Tasks
//------------------------------------------------------------------------------
std::list<Task> SQLiteRepo::getTasks(const Filter &filter) {
  return std::list<Task>();
}
std::list<Task> SQLiteRepo::getTasks(const std::string filterField,
                                     const std::string FliterValue) {
  return std::list<Task>();
}
std::list<Task> SQLiteRepo::getTasks() { return std::list<Task>(); }
bool SQLiteRepo::init() {
  // Prepare to work

  // project
  if (!projectTableExist()){
    createProjectTable();
  }
  // role
  if (!roleTableExist()) {
    createRoleTable();
  }
  // task
  if (!taskTableExist()){
    createRoleTable();
  }
  // user
  if (!userTableExist()){
    createUserTable();
  }
  // userRoles
  if (!userRolesTableExist()){
    createUserRolesTable();
  }
  return true; // todo - return normal value

}
