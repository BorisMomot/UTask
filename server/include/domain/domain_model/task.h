//
// Created by boris on 15.11.2021.
//

#ifndef GTEST_DEMO_TASK_H
#define GTEST_DEMO_TASK_H

#include <cstdint>
#include <string>

class Task {
  uint64_t id;
  uint64_t priority;
  std::string name;
  std::string status;
  uint64_t userCreator;
  uint64_t  userExecutor;
  std::string description;
  std::string stored;

public:
  Task(const uint64_t id, const uint64_t priority, const std::string &name,
     const std::string &status, const uint64_t userCreator,
     const uint64_t userExecutor, const std::string &description,
     const std::string &stored)
    : id(id), priority(priority), name(name), status(status),
      userCreator(userCreator), userExecutor(userExecutor),
      description(description), stored(stored) {}

  const uint64_t getId() const { return id; }
  const uint64_t getPriority() const { return priority; }
  const std::string &getName() const { return name; }
  const std::string &getStatus() const { return status; }
  const uint64_t getUserCreator() const { return userCreator; }
  const uint64_t getUserExecutor() const { return userExecutor; }
  const std::string &getDescription() const { return description; }
  const std::string &getStored() const { return stored; }
};

class TaskBuilder{
  uint64_t id{0};
  uint64_t priority{0};
  std::string name;
  std::string status;
  uint64_t userCreator{0};
  uint64_t  userExecutor{0};
  std::string description;
  std::string stored;

public:
  Task buildTask();
  void setId(uint64_t id) { TaskBuilder::id = id; }
  void setPriority(uint64_t priority) { TaskBuilder::priority = priority; }
  void setName(const std::string &name) { TaskBuilder::name = name; }
  void setStatus(const std::string &status) { TaskBuilder::status = status; }
  void setUserCreator(uint64_t userCreator) {
    TaskBuilder::userCreator = userCreator;
  }
  void setUserExecutor(uint64_t userExecutor) {
    TaskBuilder::userExecutor = userExecutor;
  }
  void setDescription(const std::string &description) {
    TaskBuilder::description = description;
  }
  void setStored(const std::string &stored) { TaskBuilder::stored = stored; }
};

#endif // GTEST_DEMO_TASK_H
