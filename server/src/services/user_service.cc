//
// Created by boris on 06.12.2021.
//

#include <cstdlib>
#include "user_service.h"
#include "../repositories/user_repository.h"
#include "../repositories/sqlite/sqlite_manager.h"
#include <logger.h>

//#include <sqlite_manager.h>

UserService::UserService() {
}

std::list<User> UserService::getUsers() {
  if (!userRepository) { throw UserRepositoryUnset(); }
  try{
    return userRepository->getAllUsers();
  } catch (...) {
    LOG(LOG_ALERT) << "Internal error in user repository" << std::endl;
    throw UserRepositoryException();
  }
}

std::vector<std::string> UserService::getUserFilters() {
  return std::vector<std::string>{"userName", "firstname", "lastname", "email", "phone", "userStatus"};
}

bool UserService::addUser(const User &user) {
  if (!userRepository) { throw UserRepositoryUnset(); }
  try{
    return userRepository->addUser(user);
  } catch (...) {
    LOG(LOG_ALERT) << "Internal error in user repository" << std::endl;
    throw UserRepositoryException();
  }
}

uint UserService::getUserId(const std::string &userName) {
  if (!userRepository) { throw UserRepositoryUnset(); }
  try{
    return userRepository->getUserIdByName(userName);
  } catch (...) {
    LOG(LOG_ALERT) << "Internal error in user repository" << std::endl;
    throw UserRepositoryException();
  }
}

User UserService::getUser(uint userId) {
  if (!userRepository) { throw UserRepositoryUnset(); }
  try{
    return userRepository->findById(userId);
  }
  catch(...){
    LOG(LOG_ALERT) << "Internal error in user repository" << std::endl;
    throw UserRepositoryException();
  }
}
bool UserService::updateUserInfo(uint userId, const User &user) {
  if (!userRepository) { throw UserRepositoryUnset(); }
  try{
    return userRepository->updateUser(userId, user);
  }
  catch(...){
    LOG(LOG_ALERT) << "Internal error in user repository" << std::endl;
    throw UserRepositoryException();
  }
}

bool UserService::deleteUser(uint userId) {
  if (!userRepository) { throw UserRepositoryUnset(); }
  try{
    return userRepository->deleteUser(userId);
  }
  catch(...){
    LOG(LOG_ALERT) << "Internal error in user repository" << std::endl;
    throw UserRepositoryException();
  }
}

void UserService::setUserRepository(
    const std::shared_ptr<UserRepositoryInterface> &userRepository) {
  UserService::userRepository = userRepository;
}
