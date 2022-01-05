//
// Created by boris on 02.12.2021.
//

#ifndef GTEST_DEMO_USER_REPOSITORY_INTERFACE_H
#define GTEST_DEMO_USER_REPOSITORY_INTERFACE_H

#include <user.h>
#include <list>
/**
 * @brief репозиторий для сохранения информации о пользователях
 */
class UserRepositoryInterface{
public:
  virtual bool addUser(const User& user) = 0;
  virtual User findById(uint id) = 0;
  virtual bool updateUser(uint id, const User& user) = 0;
  virtual bool deleteUser(uint id)= 0;
  virtual uint getUserIdByName(const std::string& name) = 0;
  virtual std::list<User> getAllUsers() = 0;
  virtual std::list<User> getAllUsers(size_t limit) = 0;
  virtual std::list<User> getAllUsers(size_t limit, size_t offset) = 0;
};

#endif // GTEST_DEMO_USER_REPOSITORY_INTERFACE_H
