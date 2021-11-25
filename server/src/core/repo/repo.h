//
// Created by boris on 25.11.2021.
//

#ifndef GTEST_DEMO_REPO_H
#define GTEST_DEMO_REPO_H

#include <string>
#include <list>
#include "filter.h"
#include "project.h"
#include "role.h"
#include "task.h"
#include "user.h"

#include "db_manager.h"

class Repo {
public:
  Repo(){}
  virtual ~Repo(){}

  virtual bool saveProjectData(const Project role) = 0;
  virtual bool saveRoleData(const Role role) = 0;
  virtual bool saveUserData(const User user) = 0;
  virtual bool saveTaskData(const Project project) = 0;

  virtual std::list<Project> getProjects(const Filter& filter ) = 0;
  virtual std::list<Project> getProjects(const std::string filterField, const std::string FliterValue) = 0;
  virtual std::list<Project> getProjects() = 0;

  virtual std::list<Role> getRole(const Filter& filter ) = 0;
  virtual std::list<Role> getRole(const std::string filterField, const std::string FliterValue) = 0;
  virtual std::list<Role> getRole() = 0;

  virtual std::list<User> getUser(const Filter& filter ) = 0;
  virtual std::list<User> getUser(const std::string filterField, const std::string FliterValue) = 0;
  virtual std::list<User> getUser() = 0;

  virtual std::list<Task> getTasks(const Filter& filter ) = 0;
  virtual std::list<Task> getTasks(const std::string filterField, const std::string FliterValue) = 0;
  virtual std::list<Task> getTasks() = 0;
};


#endif // GTEST_DEMO_REPO_H
