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

  // Проверяем нужно ли пересоздавать таблицы
  // если нужно - пересоздаем

  auto getCreateCommand = [](TableInfo& tableInfo){
    std::ostringstream command;
    command << "CREATE TABLE " << tableInfo.getTableName() << " (";
    for (const auto& p:tableInfo.getColumsProperties()){
      command << " " <<  p.first << " ";
      for (const auto& s: p.second){
        command << " " << s;
      }
    }
    return command.str();
  };

  TableInfoSQLiteFactory tableInfoSqLiteFactory;

  // create tables roles
  auto rolesTableInfo = tableInfoSqLiteFactory.createRoleTable();
  auto rolesCreateCommand = getCreateCommand(rolesTableInfo);
  manager->executeQuery(rolesCreateCommand);

  // create tables projects
  auto projectTableInfo = tableInfoSqLiteFactory.createProjectTable();
  auto projectCreateCommand = getCreateCommand(projectTableInfo);
  manager->executeQuery(projectCreateCommand);

  // create tables tasks
  auto taskTableInfo = tableInfoSqLiteFactory.createTaskTable();
  auto taskCreateCommand = getCreateCommand(taskTableInfo);
  manager->executeQuery(taskCreateCommand);

  // create tables users
  auto userTableInfo = tableInfoSqLiteFactory.createUserTable();
  auto userCreateCommand = getCreateCommand(userTableInfo);
  manager->executeQuery(userCreateCommand);

  // create tables usersRoles
  auto userRolesTableInfo = tableInfoSqLiteFactory.createUsersRoles();
  auto userRolesCreateCommand = getCreateCommand(userRolesTableInfo);
  manager->executeQuery(userRolesCreateCommand);

}
