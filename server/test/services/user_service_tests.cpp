//
// Created by boris on 25.12.2021.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <user_repository_interface.h>
#include <db_manager_interface.h>
#include <user_service.h>

class RepoMock: public UserRepositoryInterface{
public:
  MOCK_METHOD(bool, addUser, (const User &user), (override));
  MOCK_METHOD(User, findById, (uint id), (override));
  MOCK_METHOD(bool, updateUser, (uint id, const User &user), (override));
  MOCK_METHOD(bool, deleteUser, (uint id), (override));
  MOCK_METHOD(uint, getUserIdByName, (const std::string& name), (override));
  MOCK_METHOD( std::list<User>, getAllUsers, (), (override));
  MOCK_METHOD( std::list<User>, getAllUsers, (size_t limit), (override));
  MOCK_METHOD( std::list<User>, getAllUsers, (size_t limit, size_t offset), (override));
};

TEST(user_repo, add_user){
  using ::testing::AtLeast;
  auto repoMock = std::make_shared<RepoMock>();
  EXPECT_CALL(*repoMock, addUser).Times(AtLeast(1));

  UserService userService;
  userService.setUserRepository(repoMock);
  UserBuilder userBuilder;
  userBuilder.setId(1);
  userBuilder.setUserName("");
  userBuilder.setFirstName("");
  userBuilder.setLastName("");
  userBuilder.setEmail("");
  userBuilder.setPhone("");
  userBuilder.setUserStatus(1);
  userBuilder.setUserRoles(1);
  auto user= userBuilder.buildUser();
  userService.addUser(user);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}