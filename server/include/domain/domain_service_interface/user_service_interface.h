//
// Created by boris on 02.12.2021.
//

#ifndef GTEST_DEMO_USER_SERVICE_INTERFACE_H
#define GTEST_DEMO_USER_SERVICE_INTERFACE_H

#include <user.h>

/**
 * \brief Interface for working with User
 */

class UserServiceInterface {
public:
  virtual std::list<User> getUsers() = 0;
  virtual std::vector<std::string> getUserFilters() = 0;
  virtual bool addUser(const User& user) = 0;
  virtual uint getUserId(const std::string& userName ) = 0;
  virtual User getUser(uint userId) = 0;
  virtual updateUserInfo(uint userId, const User& user) = 0;
  virtual deleteUser(uint userId) = 0;
};

#endif // GTEST_DEMO_USER_SERVICE_INTERFACE_H
