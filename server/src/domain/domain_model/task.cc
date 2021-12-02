//
// Created by boris on 02.12.2021.
//

#include <task.h>

Task TaskBuilder::buildTask() {
  return Task(id, priority, name, status, userCreator, userExecutor, description, stored);
}