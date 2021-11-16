//
// Created by boris on 15.11.2021.
//

#ifndef GTEST_DEMO_SQLITE_REPO_H
#define GTEST_DEMO_SQLITE_REPO_H

#include <iostream>
#include <cstring>
#include <sqlite3.h>
#include <list>
#include <map>
#include <functional>


#include "filter.h"
#include "project.h"
#include "role.h"
#include "task.h"
#include "user.h"

#include "table_info_creator.h"

class SQLiteManager{
  const std::string db_address;
  sqlite3* db;

  void init(){
    // Init connection
    auto rc = sqlite3_open(db_address.c_str(), &db);
    if (rc){
      std::cerr << "Couldn't open db" << std::endl;
    } else {
      std::cout << "Open successfully" << std::endl;
    }
    //--------------------------------------------------------------------------

  }



public:
  virtual ~SQLiteManager() {
    sqlite3_close(db);
  }
  SQLiteManager(const std::string &dbAddress) : db_address(dbAddress) {


  }
  typedef std::vector<std::string> tableRow;

  std::vector<tableRow> executeQuery(std::string query){
    std::vector<tableRow> result;

    // Execute SQL query
    char *errorMsg = 0;
    auto callback_l = [](void* data, int argc, char** argv, char** azColName) -> int {
      auto res = reinterpret_cast<std::vector<SQLiteManager::tableRow>&> (data);
      SQLiteManager::tableRow row;
      for(int i=0; i < argc; ++i){
//        std::cout << azColName[i] << " = " << (argv[i] ? argv[i]: "NULL") << std::endl;
        row.emplace_back((argv[i] ? argv[i]: "NULL"));
      }
      res.emplace_back(row);
      return 0;
    };

    auto rc = sqlite3_exec(db, query.c_str(), callback_l , (void*)&result, &errorMsg);
    if ( rc != SQLITE_OK) {
      std::cerr << "Error: " << errorMsg << std::endl;
      sqlite3_free(errorMsg);
    } else {
      std::cout << "[SUCCESS] Execute:" << query << std::endl;
    }

    return result;
  }
};




class SQLiteRepo final {
  SQLiteManager* manager;
public:
  SQLiteRepo(const std::string &dbAddress);



  bool saveProjectData(const Project role);
  bool saveRoleData(const Role role);
  bool saveUserData(const User user);
  bool saveTaskData(const Project project);

  std::list<Project> getProjects(const Filter& filter );
  std::list<Project> getProjects(const std::string filterField, const std::string FliterValue);
  std::list<Project> getProjects();

  std::list<Role> getRole(const Filter& filter );
  std::list<Role> getRole(const std::string filterField, const std::string FliterValue);
  std::list<Role> getRole();

  std::list<User> getUser(const Filter& filter );
  std::list<User> getUser(const std::string filterField, const std::string FliterValue);
  std::list<User> getUser();

  std::list<Task> getTasks(const Filter& filter );
  std::list<Task> getTasks(const std::string filterField, const std::string FliterValue);
  std::list<Task> getTasks();

  virtual ~SQLiteRepo();
};





//
//
//void executeQuery(sqlite3* db, const std::string& query ){
//  char* sqlRequest = new char[query.length() + 1];
//  std::strcpy(sqlRequest, query.c_str());
//  // Execute SQL query
//  char *errorMsg = 0;
//  auto rc = sqlite3_exec(db, sqlRequest, callback, 0, &errorMsg);
//  if ( rc != SQLITE_OK) {
//    std::cerr << "Error: " << errorMsg << std::endl;
//    sqlite3_free(errorMsg);
//  } else {
//    std::cout << "[SUCCESS] Execute:" << query << std::endl;
//  }
//}
//
//
//int main(int agrc, char** argv){
//  sqlite3* db;
//  auto rc = sqlite3_open("test.db", &db);
//  if (rc){
//    std::cerr << "Couldn't open db" << std::endl;
//  } else {
//    std::cout << "Open successfully" << std::endl;
//  }
//
//  //----------------------------------------------------------------------------
//  // create DB
//  auto query = "CREATE TABLE COMPANY(ID INT PRIMARY KEY NOT NULL, NAME TEXT, AGE INT, ADDRESS CHAR(50), SALARY REAL);";
//  executeQuery(db, query);
//
//  //----------------------------------------------------------------------------
//  // insert data to DB
//  query = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
//                "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
//                "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
//                "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
//                "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
//                "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
//                "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
//                "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";
//  executeQuery(db, query);
//
//  //----------------------------------------------------------------------------
//  // get data from DB
//  query = "SELECT * from COMPANY";
//  executeQuery(db, query);
//
//  //----------------------------------------------------------------------------
//  // update data in database
//  query = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
//        "SELECT * from COMPANY";
//  executeQuery(db, query);
//
//  //----------------------------------------------------------------------------
//  // delete from DB and show results
//  query = "DELETE from COMPANY where ID=2; " \
//          "SELECT * from COMPANY";
//  executeQuery(db, query);
//
//
//  sqlite3_close(db);
//  return EXIT_SUCCESS;
//}

#endif // GTEST_DEMO_SQLITE_REPO_H
