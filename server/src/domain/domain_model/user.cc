//
// Created by boris on 02.12.2021.
//
#include <user.h>

User UserBuilder::buildUser(){
  return User(id, userName, firstName, lastName, email, phone, userStatus, userRoles);
}