//
// Created by boris on 15.11.2021.
//

#ifndef GTEST_DEMO_SQLITE_REPO_H
#define GTEST_DEMO_SQLITE_REPO_H

#include <iostream>
#include <cstring>
#include <sqlite3.h>
#include <list>
#include <map>
#include <functional>

#include <repo.h>

#include "filter.h"
#include "project.h"
#include "role.h"
#include "task.h"
#include "user.h"

#include "table_info_factory.h"
#include "sqlite_manager.h"

class SQLiteRepo: public Repo {
  SQLiteManager* manager;
public:
  SQLiteRepo(const std::string &dbAddress);

  bool saveProjectData(const Project role);
  bool saveRoleData(const Role role);
  bool saveUserData(const User user);
  bool saveTaskData(const Project project);

  std::list<Project> getProjects(const Filter& filter );
  std::list<Project> getProjects(const std::string filterField, const std::string FliterValue);
  std::list<Project> getProjects();

  std::list<Role> getRole(const Filter& filter );
  std::list<Role> getRole(const std::string filterField, const std::string FliterValue);
  std::list<Role> getRole();

  std::list<User> getUser(const Filter& filter );
  std::list<User> getUser(const std::string filterField, const std::string FliterValue);
  std::list<User> getUser();

  std::list<Task> getTasks(const Filter& filter );
  std::list<Task> getTasks(const std::string filterField, const std::string FliterValue);
  std::list<Task> getTasks();

  virtual ~SQLiteRepo();

protected:
  bool createProjectTable() override;
  bool createRoleTable() override;
  bool createTaskTable() override;
  bool createUserTable() override;
  bool createUserRolesTable() override;
  bool projectTableExist() override;
  bool roleTableExist() override;
  bool taskTableExist() override;
  bool userTableExist() override;
  bool userRolesTableExist() override;

private:
  bool createTableCommand(TableInfo& tableInfo);
};






#endif // GTEST_DEMO_SQLITE_REPO_H
