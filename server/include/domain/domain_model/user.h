//
// Created by boris on 15.11.2021.
//

#ifndef GTEST_DEMO_USER_H
#define GTEST_DEMO_USER_H
#include <cstdint>
#include <string>
#include <vector>

class User {
  uint64_t id;
  std::string userName;
  std::string firstName;
  std::string lastName;
  std::string email;
  std::string phone;
  uint32_t userStatus;
  std::vector<uint64_t> userRoles;

public:
  User(const uint64_t id, const std::string &userName,
       const std::string &firstName, const std::string &lastName,
       const std::string &email, const std::string &phone,
       const uint32_t userStatus, const std::vector<uint64_t> &userRoles)
      : id(id), userName(userName), firstName(firstName), lastName(lastName),
        email(email), phone(phone), userStatus(userStatus),
        userRoles(userRoles) {}

  const uint64_t getId() const { return id; }
  const std::string &getUserName() const { return userName; }
  const std::string &getFirstName() const { return firstName; }
  const std::string &getLastName() const { return lastName; }
  const std::string &getEmail() const { return email; }
  const std::string &getPhone() const { return phone; }
  const uint32_t getUserStatus() const { return userStatus; }
  const std::vector<uint64_t> &getUserRoles() const { return userRoles; }
};

class UserBuilder{
  uint64_t id{0};
  std::string userName;
  std::string firstName;
  std::string lastName;
  std::string email;
  std::string phone;
  uint32_t userStatus{0};
  std::vector<uint64_t> userRoles{};

public:
  User buildUser();

  void setId(uint64_t id) { UserBuilder::id = id; }
  void setUserName(const std::string &userName) {
    UserBuilder::userName = userName;
  }
  void setFirstName(const std::string &firstName) {
    UserBuilder::firstName = firstName;
  }
  void setLastName(const std::string &lastName) {
    UserBuilder::lastName = lastName;
  }
  void setEmail(const std::string &email) { UserBuilder::email = email; }
  void setPhone(const std::string &phone) { UserBuilder::phone = phone; }
  void setUserStatus(uint32_t userStatus) {
    UserBuilder::userStatus = userStatus;
  }
  void setUserRoles(uint64_t userRole) {
    userRoles.emplace_back(userRole);
  }
};

#endif // GTEST_DEMO_USER_H
