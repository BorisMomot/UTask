//
// Created by boris on 02.12.2021.
//

#ifndef GTEST_DEMO_USER_REPOSITORY_H
#define GTEST_DEMO_USER_REPOSITORY_H

#include <user.h>
#include <db_manager_interface.h>
#include <repository_interface.h>
#include <user_repository_interface.h>



class UserNotFound: public std::exception{
  uint userId;
public:
  UserNotFound(uint userId) : userId(userId) {}

  const char *
  what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override {
    std::string s("Doesn't find user with id:" + userId);
    return s.c_str();
  }
};

class UserRepository: public RepositoryInterface, public UserRepositoryInterface {
public:
  bool addUser(const User &user) override;
  const User &findById(uint id) override;
  bool updateUser(uint id, const User &user) override;
  bool deleteUser(uint id) override;
};

#endif // GTEST_DEMO_USER_REPOSITORY_H
