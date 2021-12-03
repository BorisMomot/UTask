//
// Created by boris on 03.12.2021.
//

#include <gtest/gtest.h>

#include <user_sqlite_helper.h>

TEST(user_sqlite_helper, table_exist) {
  std::string checkTableExist("");
  ASSERT_EQ(checkTableExist, UserSqliteHelper::checkUserTableExist());
}

TEST(user_sqlite_helper, create_table) {
  std::string createTable("");
  ASSERT_EQ(createTable, UserSqliteHelper::createUserTableCommand());
}

TEST(user_sqlite_helper, add_user) {
  std::string addUser("");
  UserBuilder ub;
  auto user = ub.buildUser();
  ASSERT_EQ(addUser, UserSqliteHelper::addUserCommand(user));
}

TEST(user_sqlite_helper, find_user) {
  std::string findUser("");
  uint id = 1;
  ASSERT_EQ(findUser, UserSqliteHelper::findUserByIdCommand(id));
}

TEST(user_sqlite_helper, update_user) {
  std::string updateUser("");
  UserBuilder ub;
  auto user = ub.buildUser();
  uint id = 1;
  ASSERT_EQ(updateUser, UserSqliteHelper::updateUserCommand(id, user));
}

TEST(user_sqlite_helper, delete_user) {
  std::string deleteUser("");
  uint id = 1;
  ASSERT_EQ(deleteUser, UserSqliteHelper::deleteUserCommand(id));
}

TEST(user_sqlite_helper, from_data_to_user) {
  //
  std::vector<std::vector<std::string>> data({{""}});
  User user1 = UserSqliteHelper::userFromData(data);
  //
  UserBuilder ub;
  User user2 = ub.buildUser();
  ASSERT_EQ(user1.getId(), user2.getId());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}