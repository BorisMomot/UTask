//
// Created by boris on 06.12.2021.
//

#include <cstdlib>
#include "user_service.h"
#include "../repositories/user_repository.h"
#include "../repositories/sqlite/sqlite_manager.h"
//#include <sqlite_manager.h>

UserService::UserService() {
}

std::list<User> UserService::getUsers() {
  if (!userRepository) { throw UserRepositoryUnset(); }
  return std::list<User>{};
}

std::vector<std::string> UserService::getUserFilters() {
  if (!userRepository) { throw UserRepositoryUnset(); }
  return std::vector<std::string>{};
}

bool UserService::addUser(const User &user) {
  if (!userRepository) { throw UserRepositoryUnset(); }
  return userRepository->addUser(user);
}

uint UserService::getUserId(const std::string &userName) {
  if (!userRepository) { throw UserRepositoryUnset(); }
  return 42;
}

User UserService::getUser(uint userId) {
  if (!userRepository) { throw UserRepositoryUnset(); }
  return userRepository->findById(userId);
}
bool UserService::updateUserInfo(uint userId, const User &user) {
  if (!userRepository) { throw UserRepositoryUnset(); }
  return userRepository->updateUser(userId, user);
}

bool UserService::deleteUser(uint userId) {
  if (!userRepository) { throw UserRepositoryUnset(); }
  return userRepository->deleteUser(userId);
}

void UserService::setUserRepository(
    const std::shared_ptr<UserRepositoryInterface> &userRepository) {
  UserService::userRepository = userRepository;
}
