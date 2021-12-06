//
// Created by boris on 02.12.2021.
//

#ifndef GTEST_DEMO_USER_REPOSITORY_INTERFACE_H
#define GTEST_DEMO_USER_REPOSITORY_INTERFACE_H

#include <user.h>

//GET /users - Print all users in system
//GET /userfilters - Print all available filters for users
//POST /user - Create user
//GET /username/{username} - Get user id by user name
//GET /user/{userId} - Get user by user id
//PATCH /user/{userId} - Updated user
//DELETE /user/{userId} - Delete user


class UserRepositoryInterface{
public:


  virtual bool addUser(const User& user) = 0;
  virtual const User& findById(uint id) = 0;
  virtual bool updateUser(uint id, const User& user) = 0;
  virtual bool deleteUser(uint id)= 0;
};

#endif // GTEST_DEMO_USER_REPOSITORY_INTERFACE_H
