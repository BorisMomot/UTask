//
// Created by boris on 26.11.2021.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../sqlite_repo.h"

using ::testing::AtLeast;

class MockDBManager: public DBManager{
public:
  MOCK_METHOD(std::vector<tableRow>, executeQuery, (std::string query), (override));
};


TEST(sqlite_repo, create) {
  MockDBManager dbManager;
  SQLiteRepo sqLiteRepo(dbManager);
  sqLiteRepo.init();
  Project project(1, "test", "test only");
//  sqLiteRepo.saveProjectData(project);

  EXPECT_CALL(dbManager, executeQuery)                  // #3
      .Times(AtLeast(1))
      .WillRepeatedly(testing::Return(dbManager.executeQuery("CREATE TABLE ROLES ( DESCRIPTION  TEXT ID  INT PRIMARY KEY NOT NULL NAME  TEXT")))
;

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