//
// Created by boris on 02.12.2021.
//

#ifndef GTEST_DEMO_ROLE_REPOSITORY_INTERFACE_H
#define GTEST_DEMO_ROLE_REPOSITORY_INTERFACE_H

#include <role.h>
#include <list>
/**
 * @brief Интерфейс для сохранения разных ролей пользователей
 */
class RoleRepositoryInterface{
public:
  virtual bool addRole(const Role& role) = 0;
  virtual Role findById(uint id) = 0;
  virtual bool updateRole(uint id, const Role& role) = 0;
  virtual bool deleteRole(uint id) = 0;
  virtual uint getRoleByName(const std::string& name) = 0;
  virtual std::list<Role> getAllRoles() = 0;
  virtual std::list<Role> getAllRoles(size_t limit) = 0;
  virtual std::list<Role> getAllRoles(size_t limit, size_t offset) = 0;
};
#endif // GTEST_DEMO_ROLE_REPOSITORY_INTERFACE_H
