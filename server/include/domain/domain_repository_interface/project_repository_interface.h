//
// Created by boris on 02.12.2021.
//

#ifndef GTEST_DEMO_PROJECT_REPOSITORY_INTERFACE_H
#define GTEST_DEMO_PROJECT_REPOSITORY_INTERFACE_H

#include <project.h>
#include <list>
/**
 * @brief  Интерфейс для сохранения информации по задачам
 */
class ProjectRepositoryInterface{
public:
  virtual bool addProject(const Project& project) = 0;
  virtual Project findById(uint id) = 0;
  virtual bool updateProject(uint id, const Project& project) = 0;
  virtual bool deleteProject(uint id) = 0;
  virtual uint getProjectByName(const std::string& name) = 0;
  virtual std::list<Project> getAllProjects() = 0;
  virtual std::list<Project> getAllProjects(size_t limit) = 0;
  virtual std::list<Project> getAllProjects(size_t limit, size_t offset) = 0;
};
#endif // GTEST_DEMO_PROJECT_REPOSITORY_INTERFACE_H
