//
// Created by boris on 03.12.2021.
//

#include <gtest/gtest.h>

#include <user_sqlite_helper.h>

//SELECT name FROM sqlite_master WHERE type='table' AND name='USERS';
TEST(user_sqlite_helper, table_exist) {
  std::string checkTableExist("SELECT name FROM sqlite_master WHERE type='table' AND name='USERS';");
  ASSERT_EQ(checkTableExist, UserSqliteHelper::checkUserTableExist());
}

//CREATE table USERS (USERNAME TEXT, FIRSTNAME TEXT, LASTNAME TEXT, EMAIL TEXT, PHONE TEXT, USERSTATUS INT);
TEST(user_sqlite_helper, create_table) {
  std::string createTable("CREATE table USERS (USERNAME TEXT, FIRSTNAME TEXT, LASTNAME TEXT, EMAIL TEXT, PHONE TEXT, USERSTATUS INT);");
  ASSERT_EQ(createTable, UserSqliteHelper::createUserTableCommand());
}

//INSERT INTO USERS (USERNAME, FIRSTNAME, LASTNAME, EMAIL, PHONE, USERSTATUS)
//    VALUES('tom', 'tom', 'mot', 'd@mail', 345, 1 );
TEST(user_sqlite_helper, add_user) {
  std::string addUser("INSERT INTO USERS (USERNAME, FIRSTNAME, LASTNAME, EMAIL, PHONE, USERSTATUS) VALUES('tom', 'Jerry', 'Mot', 'd@mail', 345, 1 );");
  UserBuilder ub;
  ub.setUserName("tom");
  ub.setFirstName("Jerry");
  ub.setLastName("Mot");
  ub.setEmail("d@mail");
  ub.setPhone("345");
  ub.setUserStatus(1);

  auto user = ub.buildUser();
  ASSERT_EQ(addUser, UserSqliteHelper::addUserCommand(user));
}

//Select * FROM USERS WHERE OID=2;
TEST(user_sqlite_helper, find_user) {
  uint id = 2;
  std::string findUser("SELECT * FROM USERS WHERE OID=2;");
  ASSERT_EQ(findUser, UserSqliteHelper::findUserByIdCommand(id));
}

//UPDATE USERS SET USERNAME = 'Kit', FIRSTNAME = 'Fill', LASTNAME = 'BOB', EMAIL = 'p@mail', PHONE = '789', USERSTATUS = 2 WHERE OID=3;
TEST(user_sqlite_helper, update_user) {
  std::string updateUser("UPDATE USERS SET USERNAME = 'Kit', FIRSTNAME = 'Fill', LASTNAME = 'BOB', EMAIL = 'p@mail', PHONE = '789', USERSTATUS = 2 WHERE OID=3;");
  UserBuilder ub;
  ub.setUserName("Kit");
  ub.setFirstName("Fill");
  ub.setLastName("BOB");
  ub.setPhone("789");
  ub.setEmail("p@mail");
  ub.setUserStatus(2);
  auto user = ub.buildUser();
  uint id = 3;
  ASSERT_EQ(updateUser, UserSqliteHelper::updateUserCommand(id, user));
}

//DELETE FROM USERS WHERE OID = 3;
TEST(user_sqlite_helper, delete_user) {
  std::string deleteUser("DELETE FROM USERS WHERE OID = 3;");
  uint id = 3;
  ASSERT_EQ(deleteUser, UserSqliteHelper::deleteUserCommand(id));
}






//  static std::string getUserFilters();
TEST(user_sqlite_helper, get_users_filters) {
  std::string getUsersFilters("");
  ASSERT_EQ(getUsersFilters, UserSqliteHelper::getUserFilters());
}
//  static std::string getUserIdByUserNameCommand(const std::string& userName);
TEST(user_sqlite_helper, get_usersid_by_name) {
  std::string userName("Tom");
  std::string getUserIdCommand("");
  ASSERT_EQ(getUserIdCommand, UserSqliteHelper::getUserIdByUserNameCommand(userName));
}
//  static std::string getAllUserCommand();
TEST(user_sqlite_helper, get_all_users) {
  // check get all users command
  std::string getAllUsersCommand("");
  ASSERT_EQ(getAllUsersCommand, UserSqliteHelper::getAllUserCommand());

  // check get all users command with shift
  uint shift = 5;
  std::string getAllUsersCommandShift("");
  ASSERT_EQ(getAllUsersCommandShift, UserSqliteHelper::getAllUserCommand(shift));

  // check get all users command with shift and limit amount
  uint limit = 10;
  std::string getAllUsersCommandLimit("");
  ASSERT_EQ(getAllUsersCommandLimit, UserSqliteHelper::getAllUserCommand(shift, limit));
}

//  static std::string getAllUsersCommand(std::unordered_map<std::string, std::string> filters);
TEST(user_sqlite_helper, get_filtered_users) {
  std::unordered_map<std::string, std::string> filters {{"", ""}};
  std::string getFilteredUsersCommand("");
  ASSERT_EQ(getFilteredUsersCommand, UserSqliteHelper::getAllUsersCommand(filters));
}

//
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