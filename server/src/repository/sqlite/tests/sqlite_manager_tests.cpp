//
// Created by boris on 26.11.2021.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../sqlite_repo.h"

using ::testing::AtLeast;

namespace testing{
  class MockDBManager: public DBManager{
  public:
    MOCK_METHOD(std::vector<tableRow>, executeQuery, (std::string query), (override));
  };
}

// Testing Google test
//______________________________________________________________________________
namespace testing{
class Interface{
public:
  virtual int getSomeNumber(std::string in) = 0;
};

class MockClass: public Interface{
public:
  MOCK_METHOD(int, getSomeNumber, (std::string in), (override));
};

class UserImpl{
  Interface& interface_;
public:
  UserImpl(Interface& interface): interface_(interface){}
  int doWork(){
    const auto res = interface_.getSomeNumber("42") +2;
    if (res == 4) {
      std::cout << "Result 4" << std::endl;
    } else {
      std::cout << "Result: " << res << std::endl;
    }

    return res + 2;
  }
};

}

TEST(test_for_tes, first){
  testing::MockClass mockClass;
  testing::UserImpl user(mockClass);

  EXPECT_CALL(mockClass, getSomeNumber("42")) // проверяем, что метод был вызван с параметром 42
      .Times(AtLeast(2)) // проверяем что минимум два раза
      .WillOnce(testing::Return(2)) // первый раз метод возвращает 2
      .WillOnce(testing::Return(3)) // второй раз метод возвращает 3
      .WillRepeatedly(testing::Return(5)); // все последующие 5
  user.doWork();
  user.doWork();
  user.doWork();
}

// Testing Google test
//______________________________________________________________________________





TEST(sqlite_repo, initTables) {
  testing::MockDBManager dbManager;
  SQLiteRepo sqLiteRepo(dbManager);



  // Expect: 4 time call
  //  CREATE TABLE ROLES ( ID INT PRIMARY KEY NOT NULL NAME  TEXT DESCRIPTION  TEXT);
  EXPECT_CALL(dbManager, executeQuery)
      .Times(AtLeast(4));
  sqLiteRepo.init();

//  Project project(2, "232", "test");
//  sqLiteRepo.saveProjectData(std::move(project));
}

TEST(testlib, substract) {
  double res;
  res = 1.0 - 2.0;
  ASSERT_NEAR(res, -1.0, 1.0e-11);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}