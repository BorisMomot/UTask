//
// Created by boris on 15.11.2021.
//

#ifndef GTEST_DEMO_PROJECT_H
#define GTEST_DEMO_PROJECT_H

#include <cstdint>
#include <string>

class Project{
  const uint64_t id;
  const std::string name;
  const std::string description;
public:
  Project(const uint64_t id, const std::string name,
          const std::string description)
      : id(id), name(name), description(description) {}
  const uint64_t getId() const { return id; }
  const std::string &getName() const { return name; }
  const std::string &getDescription() const { return description; }
};

#endif // GTEST_DEMO_PROJECT_H
