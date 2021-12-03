//
// Created by boris on 02.12.2021.
//

#include "user_sqlite_helper.h"

//CREATE table USERS
//    (
//     USERNAME TEXT,
//     FIRSTNAME TEXT,
//     LASTNAME TEXT,
//     EMAIL TEXT,
//     PHONE TEXT,
//     USERSTATUS INT);

// if already exists: [1] [SQLITE_ERROR] SQL error or missing database (table USERS already exists)
std::string UserSqliteHelper::createUserTableCommand() {
  return "";
}

//INSERT INTO USERS (USERNAME, FIRSTNAME, LASTNAME, EMAIL, PHONE, USERSTATUS)
//    VALUES('tom', 'tom', 'mot', 'd@mail', 345, 1 );
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
// SELECT name FROM sqlite_master WHERE type='table' AND name='USERS'; (return USERS/nothing)
std::string UserSqliteHelper::checkUserTableExist() {
  return "";
}

User UserSqliteHelper::userFromData(
    const std::vector<std::vector<std::string>> &data) {

  //
  UserBuilder ub;
  auto user = ub.buildUser();
  return user;
}

