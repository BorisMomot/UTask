//
// Created by boris on 02.12.2021.
//

#include "user_repository.h"
#include "sqlite/user_sqlite_helper.h"
#include <logger.h>

bool UserSQLiteRepository::addUser(const User &user) {
  if (dbManagerInterface){
    try {
      return addUser_(user);
    } catch (DBCommandFailed& commandFailed) {
      LOG(LOG_ALERT) << " : add user command to db was failed: " << commandFailed.what() << " user param: " << user << std::endl;
      return false;
    } catch (...) {
      LOG(LOG_CRIT) << " : undnown exception when we try to add user to db, user param: " << user << std::endl;
      return false;
    }
  } else {
    LOG(LOG_ALERT) << " : db manager = nullptr" << std::endl;
    throw DBManagerInterfaceNullPtr();
  }
}
bool UserSQLiteRepository::addUser_(const User &user) {
  auto query = UserSqliteHelper::addUserCommand(user);
  auto q_result = dbManagerInterface->executeQuery(query);
  if (q_result) {
    LOG(INFO) << " : user was added to DB: " << user << std::endl;
    return true;
  } else {
    LOG(LOG_ALERT) << " : user doesn't added to DB" << std::endl;
    return false;
  }
}
//------------------------------------------------------------------------------
User UserSQLiteRepository::findById(uint id) {
  if (dbManagerInterface) {
    try {
      return findById_(id);
    } catch (...) {
      LOG(LOG_ALERT) << " : user with this id: " << id << " doesn't found" << std::endl;
      throw UserNotFound(id);
    }
  } else {
    LOG(LOG_ALERT) << " : db manager = nullptr" << std::endl;
    throw DBManagerInterfaceNullPtr();
  }
}
User UserSQLiteRepository::findById_(uint id) {
  auto query = UserSqliteHelper::findUserByIdCommand(id);
  auto q_result = dbManagerInterface->getDataFromQuery(query);
  return UserSqliteHelper::userFromData(q_result);
}
//------------------------------------------------------------------------------
bool UserSQLiteRepository::updateUser(uint id, const User &user) {
  if (dbManagerInterface){
    try {
      return updateUser_(id, user);
    } catch (DBNotFoundItem& dbNotFoundItem) {
      // log - doesn't find item with id
      return false;
    } catch (DBCommandFailed& dbCommandFailed) {
      // log - command failed
      return false;
    } catch (...) {
      // log - unknown exception
      return false;
    }
  } else {
    // log - dbManager == nullptr
    throw DBManagerInterfaceNullPtr();
  }
}
bool UserSQLiteRepository::updateUser_(uint id, const User &user) {
  auto query = UserSqliteHelper::updateUserCommand(id, user);
  auto q_result = dbManagerInterface->executeQuery(query);
  if (q_result) {
    // log - success
    return true;
  } else {
    // log - user doesn't updated
    return false;
  }
}
//------------------------------------------------------------------------------
bool UserSQLiteRepository::deleteUser(uint id) {
  if (dbManagerInterface){
    try {
      return deleteUser_(id);
    } catch (DBNotFoundItem& dbNotFoundItem) {
      // log - doesn't find item with id
      return false;
    } catch (DBCommandFailed& dbCommandFailed) {
      // log - command failed
      return false;
    } catch (...) {
      // log - unknown exception
      return false;
    }
  } else {
    // log - dbManager == nullptr
    throw DBManagerInterfaceNullPtr();
  }
}
bool UserSQLiteRepository::deleteUser_(uint id) {
  auto query = UserSqliteHelper::deleteUserCommand(id);
  auto q_result = dbManagerInterface->executeQuery(query);
  if (q_result) {
    // log user delete:
    return true;
  } else {
    // log user doesn't deleted
    return false;
  }
}
//------------------------------------------------------------------------------
uint UserSQLiteRepository::getUserIdByName(const std::string &name) {
  if (dbManagerInterface){
    try {
      return getUserIdByName_(name);
    } catch (DBNotFoundItem) {
      // log - doesn't find item with name
      return 0;
    } catch (DBCommandFailed) {
      // log - command failed
      return 0;
    } catch (...) {
      // log - unknown exception
      return 0;
    }
  } else {
    // log - dbManager == nullptr
    throw DBManagerInterfaceNullPtr();
  }
}

uint UserSQLiteRepository::getUserIdByName_(const std::string &name) {
  auto query = UserSqliteHelper::getUserIdByUserNameCommand(name);
  auto q_result = dbManagerInterface->getDataFromQuery(query);
  if (!q_result.empty()) {
    // log find userid
    auto res = q_result.begin()->begin();
    return std::stoi(*res);
  } else {
    // log user doesn't find
    return 0;
  }
}
//------------------------------------------------------------------------------
std::list<User> UserSQLiteRepository::getAllUsers() {
  return getAllUsers_(0,0);
}
std::list<User> UserSQLiteRepository::getAllUsers(size_t limit) {
  return getAllUsers_(limit,0);
}
std::list<User> UserSQLiteRepository::getAllUsers(size_t limit, size_t offset) {
  return getAllUsers_(limit,offset);
}

std::list<User> UserSQLiteRepository::getAllUsers_(size_t limit,
                                                   size_t offset) {
  if (dbManagerInterface){
    try{
      std::string query;
      if (limit && offset){
        query = UserSqliteHelper::getAllUserCommand(offset, limit);
      } else if (limit){
        query = UserSqliteHelper::getAllUserCommand(0, limit);
      } else {
        query = UserSqliteHelper::getAllUserCommand();
      }
      auto q_result = dbManagerInterface->getDataFromQuery(query);
      std::list<User> users;
      for (auto const& row:q_result){
        users.emplace_back(userFromRow(row));
      }
    } catch (DBNotFoundItem){
      // log doesn't find any
      return std::list<User>{};
    } catch (DBCommandFailed){
      // log command failed
      return std::list<User>{};
    } catch (...) {
      // log unknown problem
      return std::list<User>{};
    }
  } else {
    throw DBManagerInterfaceNullPtr();
  }
  return std::list<User>{};
}


User UserSQLiteRepository::userFromRow(const std::vector<std::string> &row) {
  auto p = row.begin();
  size_t id = std::stol (*p);
  ++p;
  std::string name = *p;
  ++p;
  std::string firstname = *p;
  ++p;
  std::string lastname = *p;
  ++p;
  std::string email = *p;
  ++p;
  std::string phone = *p;
  ++p;
  int status = std::stoi(*p);
  return User(id, name, firstname, lastname, email, phone, status, std::vector<uint64_t>{});
}

