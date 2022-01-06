//
// Created by boris on 06.12.2021.
//

#ifndef GTEST_DEMO_USER_SERVICE_H
#define GTEST_DEMO_USER_SERVICE_H

#include <memory>
#include <iostream>
#include <user.h>
#include <service_interface.h>
#include <user_repository_interface.h>
#include <user_service_interface.h>
#include <cstdlib>

class UserRepositoryUnset: public std::exception{
public:
  const char *
  what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override {
    return "User repository undefined";
  }
};

class UserRepositoryException: public std::exception{
public:
  const char *
  what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override {
    return "Internal repository error";
  }
};


class UserService: public UserServiceInterface {
  std::shared_ptr<UserRepositoryInterface> userRepository;
public:
  UserService();
  void setUserRepository(
      const std::shared_ptr<UserRepositoryInterface> &userRepository);

  std::list<User> getUsers() override;
  std::vector<std::string> getUserFilters() override;
  bool addUser(const User &user) override;
  uint getUserId(const std::string &userName) override;
  User getUser(uint userId) override;
  bool updateUserInfo(uint userId, const User &user) override;
  bool deleteUser(uint userId) override;
};

#endif // GTEST_DEMO_USER_SERVICE_H
