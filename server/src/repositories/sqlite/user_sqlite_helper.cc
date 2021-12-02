//
// Created by boris on 02.12.2021.
//

#include "user_sqlite_helper.h"

std::string UserSqliteHelper::createUserTableCommand() {
  return "";
}

std::string UserSqliteHelper::addUserCommand(const User &user) {
  return "";
}

std::string UserSqliteHelper::findUserByIdCommand(const uint userId) {
  return "";
}

std::string UserSqliteHelper::updateUserCommand(const uint userId,
                                                const User &user) {
  return "";
}

std::string UserSqliteHelper::deleteUserCommand(const uint userId) {
  return "";
}

std::string UserSqliteHelper::chackUserTableExist() {
  return "";
}

User UserSqliteHelper::userFromData(
    const std::vector<std::vector<std::string>> &data) {

  //
  UserBuilder ub;
  auto user = ub.buildUser();
  return user;
}

