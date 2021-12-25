//
// Created by boris on 02.12.2021.
//

#include "user_repository.h"
#include "sqlite/user_sqlite_helper.h"
#include <logger.h>

bool UserRepository::addUser(const User &user) {
  if (dbManagerInterface){
    try {
      auto query = UserSqliteHelper::addUserCommand(user);
      auto q_result = dbManagerInterface->executeQuery(query);
      if (q_result) {
        LOG(INFO) << "User was added to DB: " << user;
        return true;
      } else {
        // log user doesn't added
        return false;
      }
    } catch (DBCommandFailed) {
      // log - insert command failed
      return false;
    } catch (...) {
      // log - unknown exception
      return false;
    }
  } else {
    // log - dbManager == nullptr
    return false;
  }
}

const User &UserRepository::findById(uint id) {
  if (dbManagerInterface) {
    try {
      auto query = UserSqliteHelper::findUserByIdCommand(id);
      auto q_result = dbManagerInterface->getDataFromQuery(query);
      return UserSqliteHelper::userFromData(q_result);
    } catch (...) {
      throw UserNotFound(id);
    }
  } else {
    // log - dbManager == nullptr
    throw DBManagerInterfaceNullPtr();
  }
}

bool UserRepository::updateUser(uint id, const User &user) {
  if (dbManagerInterface){
    try {
      auto query = UserSqliteHelper::updateUserCommand(id, user);
      auto q_result = dbManagerInterface->executeQuery(query);
      if (q_result) {
        // log - success
        return true;
      } else {
        // log - user doesn't updated
        return false;
      }
    } catch (DBNotFoundItem) {
      // log - doesn't find item with id
      return false;
    } catch (DBCommandFailed) {
      // log - command failed
      return false;
    } catch (...) {
      // log - unknown exception
      return false;
    }
  } else {
    // log - dbManager == nullptr
    return false;
  }
}

bool UserRepository::deleteUser(uint id) {
  if (dbManagerInterface){
    try {
      auto query = UserSqliteHelper::deleteUserCommand(id);
      auto q_result = dbManagerInterface->executeQuery(query);
      if (q_result) {
        // log user delete:
        return true;
      } else {
        // log user doesn't added
        return false;
      }
    } catch (DBNotFoundItem) {
      // log - doesn't find item with id
      return false;
    } catch (DBCommandFailed) {
      // log - command failed
      return false;
    } catch (...) {
      // log - unknown exception
      return false;
    }
  } else {
    // log - dbManager == nullptr
    return false;
  }
}


