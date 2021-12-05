//
// Created by boris on 02.12.2021.
//
#include <user.h>

User UserBuilder::buildUser(){
  return User(id, userName, firstName, lastName, email, phone, userStatus, userRoles);
}
bool User::operator==(const User &rhs) const {
  return id == rhs.id && userName == rhs.userName &&
         firstName == rhs.firstName && lastName == rhs.lastName &&
         email == rhs.email && phone == rhs.phone &&
         userStatus == rhs.userStatus && userRoles == rhs.userRoles;
}
bool User::operator!=(const User &rhs) const { return !(rhs == *this); }
std::ostream &operator<<(std::ostream &os, const User &user) {
  os << "id: " << user.id << " userName: " << user.userName
     << " firstName: " << user.firstName << " lastName: " << user.lastName
     << " email: " << user.email << " phone: " << user.phone
     << " userStatus: " << user.userStatus ;
  return os;
}
