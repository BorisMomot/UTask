//
// Created by boris on 02.12.2021.
//

#ifndef GTEST_DEMO_USER_REPOSITORY_H
#define GTEST_DEMO_USER_REPOSITORY_H

#include <user.h>
#include <db_manager_interface.h>
#include <repository_interface.h>
#include <user_repository_interface.h>
#include <logger.h>
/**
 * \brief Exception class to mark that user doesn't found
 * Return userid that doesn't found
 */
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

/**
 * \brief Realisation of userRepository interface
 * Basic CRUD for SQLite
 */
class UserRepository: public RepositoryInterface, public UserRepositoryInterface {
public:
  /**
   * Save user data in DB
   * @param user data
   * @return true if everything fine
   */
  bool addUser(const User &user) override;
  /**
   * Return user info from DB
   * @param id of the user
   * @return user info if userid was found in DB or throw UserNotFound exception
   */
  const User &findById(uint id) override;
  /**
   * Update user info in DB
   * @param id of the user
   * @param user data to update
   * @return true if everything fine or throw UserNotFound exception
   */
  bool updateUser(uint id, const User &user) override;
  /**
   * Delete user
   * @param id of the user
   * @return true if everything fine or throw UserNotFound exception
   */
  bool deleteUser(uint id) override;
};

#endif // GTEST_DEMO_USER_REPOSITORY_H
