//
// Created by boris on 15.11.2021.
//

#include "sqlite_repo.h"


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
SQLiteRepo::SQLiteRepo(const std::string &dbAddress) {
  manager = new SQLiteManager("test.db");
  // create tables roles
  auto rolesTableInfo = tablesInfoCreation::createRoleTable();
  auto rolesCreateCommand = rolesTableInfo.getCreateCommand();
  manager->executeQuery(rolesCreateCommand);

  // create tables projects
  auto projectTableInfo = tablesInfoCreation::createProjectTable();
  auto projectCreateCommand = projectTableInfo.getCreateCommand();
  manager->executeQuery(projectCreateCommand);

  // create tables tasks
  auto taskTableInfo = tablesInfoCreation::createTasksTable();
  auto taskCreateCommand = taskTableInfo.getCreateCommand();
  manager->executeQuery(taskCreateCommand);

  // create tables users
  auto userTableInfo = tablesInfoCreation::createUserTable();
  auto userCreateCommand = userTableInfo.getCreateCommand();
  manager->executeQuery(userCreateCommand);

  // create tables usersRoles
  auto userRolesTableInfo = tablesInfoCreation::createUsersRoles();
  auto userRolesCreateCommand = userRolesTableInfo.getCreateCommand();
  manager->executeQuery(userRolesCreateCommand);

}
