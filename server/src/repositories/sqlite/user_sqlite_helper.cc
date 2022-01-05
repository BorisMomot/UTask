//
// Created by boris on 02.12.2021.
//

#include "user_sqlite_helper.h"
#include <unordered_map>

std::string UserSqliteHelper::createUserTableCommand() {
  return "CREATE table USERS (USERNAME TEXT, FIRSTNAME TEXT, LASTNAME TEXT, EMAIL TEXT, PHONE TEXT, USERSTATUS INT);";
}

std::string UserSqliteHelper::addUserCommand(const User &user) {
  return "INSERT INTO USERS (USERNAME, FIRSTNAME, LASTNAME, EMAIL, PHONE, USERSTATUS) VALUES('" + user.getUserName()
         + "', '" + user.getFirstName()
         + "', '" + user.getLastName()
         + "', '" + user.getEmail()
         + "', " + user.getPhone()
         + ", " + std::to_string(user.getUserStatus()) + " );";
}

std::string UserSqliteHelper::findUserByIdCommand(const uint userId) {
  return "SELECT * FROM USERS WHERE OID=" + std::to_string(userId) + ";";
}

std::string UserSqliteHelper::updateUserCommand(const uint userId,
                                                const User &user) {
  return "UPDATE USERS SET USERNAME = '" + user.getUserName() + "', FIRSTNAME = '" + user.getFirstName() + "', LASTNAME = '" + user.getLastName() + "', EMAIL = '" + user.getEmail() + "', PHONE = '" + user.getPhone() + "', USERSTATUS = " + std::to_string(user.getUserStatus()) + " WHERE OID=" + std::to_string(userId) + ";";
}

std::string UserSqliteHelper::deleteUserCommand(const uint userId) {
  return "DELETE FROM USERS WHERE OID = " + std::to_string(userId) + ";";
}

std::string UserSqliteHelper::checkUserTableExist() {
  return "SELECT name FROM sqlite_master WHERE type='table' AND name='USERS';";
}

User UserSqliteHelper::userFromData(
    const std::vector<std::vector<std::string>> &data) {

  UserBuilder ub;
  auto user = ub.buildUser();
  return user;
}
std::string UserSqliteHelper::getUserFilters() {
  return "";
}
std::string
UserSqliteHelper::getUserIdByUserNameCommand(const std::string &userName) {
  return "";
}
std::string UserSqliteHelper::getAllUserCommand() {
  return "";
}
std::string UserSqliteHelper::getAllUserCommand(uint shift) {
  return "";
}
std::string UserSqliteHelper::getAllUserCommand(uint shift, uint limit) {
  return "";
}
std::string UserSqliteHelper::getAllUsersCommand(
    std::unordered_map<std::string, std::string> filters) {
  return "";
}
