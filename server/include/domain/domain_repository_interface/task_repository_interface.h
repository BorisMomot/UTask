//
// Created by boris on 02.12.2021.
//

#ifndef GTEST_DEMO_TASK_REPOSITORY_INTERFACE_H
#define GTEST_DEMO_TASK_REPOSITORY_INTERFACE_H

#include <task.h>
#include <list>
/**
 * @brief Interface для хранения информации по задачам
 */
class TaskRepositoryInterface{
public:
  virtual bool addTask(const Task& task) = 0;
  virtual Task findById(uint id) = 0;
  virtual bool updateTask(uint id, const Task& task) = 0;
  virtual bool deleteTask(uint id) = 0;
  virtual uint getTaskIdByName(const std::string& name) = 0;
  virtual std::list<Task> getAllTasks() = 0;
  virtual std::list<Task> getAllTasks(size_t limit) = 0;
  virtual std::list<Task> getAllTasks(size_t limit, size_t offset) = 0;
};
#endif // GTEST_DEMO_TASK_REPOSITORY_INTERFACE_H
