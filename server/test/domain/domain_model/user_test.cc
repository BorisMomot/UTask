//
// Created by boris on 02.12.2021.
//
#include <gtest/gtest.h>
#include <user.h>

TEST(domain_user, create) {
  double res;
  UserBuilder userBuilder;
  userBuilder.setId(1);
  userBuilder.setFirstName("Tot");
  userBuilder.setLastName("DOD");
  userBuilder.setPhone("123");
  userBuilder.setEmail("er");
  userBuilder.setUserStatus(2);
  userBuilder.setUserRoles(3);

  auto user = userBuilder.buildUser();
  ASSERT_EQ(user.getId(),1);
  ASSERT_EQ(user.getFirstName(), "Tot");
  ASSERT_EQ(user.getLastName(), "DOD");
  ASSERT_EQ(user.getPhone(), "123");
  ASSERT_EQ(user.getEmail(), "er");
  ASSERT_EQ(user.getUserStatus(),2);
  ASSERT_EQ(user.getUserRoles().size(), 1);
  ASSERT_EQ(*user.getUserRoles().begin(), 3);
}
