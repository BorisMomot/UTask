//
// Created by boris on 15.11.2021.
//

#ifndef GTEST_DEMO_ROLE_H
#define GTEST_DEMO_ROLE_H

#include <cstdint>
#include <string>

class Role{
  uint64_t id;
  std::string name;
  std::string description;

public:
  Role(const uint64_t id, const std::string &name,
       const std::string &description);
  const uint64_t getId() const { return id; }
  const std::string &getName() const { return name; }
  const std::string &getDescription() const { return description; }
};


#endif // GTEST_DEMO_ROLE_H
