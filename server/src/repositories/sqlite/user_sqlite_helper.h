//
// Created by boris on 02.12.2021.
//

#ifndef GTEST_DEMO_USER_SQLITE_HELPER_H
#define GTEST_DEMO_USER_SQLITE_HELPER_H

#include <string>
#include <user.h>

class UserSqliteHelper {
public:
  // Check that user table exist
  static std::string checkUserTableExist();
  // Create command for userTable creation
  static std::string createUserTableCommand();
  // Add user command
  static std::string addUserCommand(const User& user);
  // Find user
  static std::string findUserByIdCommand(uint userId);
  // Save user
  static std::string updateUserCommand(uint userId, const User& user);
  // Delete user
  static std::string deleteUserCommand(uint userId);
  // From data to User
  static User userFromData(const std::vector<std::vector<std::string>> &data);
};

#endif // GTEST_DEMO_USER_SQLITE_HELPER_H
