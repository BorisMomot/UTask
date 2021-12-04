//
// Created by boris on 02.12.2021.
//

#ifndef GTEST_DEMO_USER_SQLITE_HELPER_H
#define GTEST_DEMO_USER_SQLITE_HELPER_H

#include <string>
#include <user.h>

class UserSqliteHelper {
public:
  /**
   * Check that user table exist
   * @return query that user table exist
   */
  static std::string checkUserTableExist();
  /**
   * Create command for userTable creation
   * @return query that create user table
   */
  static std::string createUserTableCommand();
  /**
   * Add user command
   * @param user
   * @return command to add user info to DB
   */
  static std::string addUserCommand(const User& user);
  /**
   * Find user
   * @param userId
   * @return command to find user info from id
   */
  static std::string findUserByIdCommand(uint userId);
  /**
   * Update user in DB
   * @param userId user id to update
   * @param user information to save in DB
   * @return command to DB
   */
  static std::string updateUserCommand(uint userId, const User& user);
  /**
   * Delete user
   * @param userId to delete from DB
   * @return command to DB
   */
  static std::string deleteUserCommand(uint userId);
  /**
   * From data to User
   * @param data from DB
   * @return User object
   */
  static User userFromData(const std::vector<std::vector<std::string>> &data);
};

#endif // GTEST_DEMO_USER_SQLITE_HELPER_H
