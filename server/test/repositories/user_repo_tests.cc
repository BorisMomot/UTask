//
// Created by boris on 03.12.2021.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <user_repository_interface.h>
#include <db_manager_interface.h>
#include <user_repository.h>

class DBManagerMock: public DBManagerInterface{
public:
  MOCK_METHOD(bool, init, (), (override));
  MOCK_METHOD(bool, executeQuery, (const std::string &query), (override));
  MOCK_METHOD(std::vector<std::vector<std::string>>, getDataFromQuery, (const std::string &query), (override));
};

TEST(user_repo, add_user){
  using ::testing::AtLeast;
  DBManagerMock dbManagerMock;
  EXPECT_CALL(dbManagerMock, executeQuery("")).Times(AtLeast(1));

  UserRepository userRepository;
  userRepository.setDbManagerInterface(&dbManagerMock);
  //
  UserBuilder userBuilder;
  auto user = userBuilder.buildUser();
  userRepository.addUser(user);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}