//
// Created by boris on 16.11.2021.
//

#ifndef GTEST_DEMO_TABLE_INFO_CREATOR_H
#define GTEST_DEMO_TABLE_INFO_CREATOR_H

#include "table_info.h"

namespace tablesInfoCreation {

//ID INT PRIMARY KEY NOT NULL, NAME TEXT, AGE INT, ADDRESS CHAR(50), SALARY REAL

// * Tasks
//      # id: uint64_t
//      # priority:	int64_t
//      # name:	String
//      # status:	String
//      # userCreator:	uint64_t
//      # userExecutor:	uint64_t
//      # description:	String
//      # stored:	String
TableInfo createTasksTable(){
  TableInfoCreator cr;
  cr.setTableName("TASKS");
  cr.addColumn("ID", {"INT", "PRIMARY KEY","NOT NULL"});
  cr.addColumn("PRIORITY", {"INT"});
  cr.addColumn("NAME", {"TEXT"});
  cr.addColumn("STATUS", {"TEXT"});
  cr.addColumn("USERCREATOR", {"INT"});
  cr.addColumn("USEREXECUTOR", {"INT"});
  cr.addColumn("DESCRIPTION", {"TEXT"});
  cr.addColumn("STORED", {"TEXT"});
  return cr.createTableInfo();
}

// * Roles
//    # id: uint64_t
//    # name:	String
//    # description:	String
TableInfo createRoleTable(){
  TableInfoCreator cr;
  cr.setTableName("ROLES");
  cr.addColumn("ID", {"INT", "PRIMARY KEY","NOT NULL"});
  cr.addColumn("NAME", {"TEXT"});
  cr.addColumn("DESCRIPTION", {"TEXT"});
  return cr.createTableInfo();
}

// * Projects
//    # id: uint64_t
//    # name:	String
//    # description:	String
TableInfo createProjectTable(){
  TableInfoCreator cr;
  cr.setTableName("PROJECTS");
  cr.addColumn("ID", {"INT", "PRIMARY KEY","NOT NULL"});
  cr.addColumn("NAME", {"TEXT"});
  cr.addColumn("DESCRIPTION", {"TEXT"});
  return cr.createTableInfo();
}
// * Users
//    # id: uint64_t
//    # userName:	String
//    # firstName:	String
//    # lastName:	String
//    # email:	String
//    # phone:	String
//    # userStatus:	uint32_t
TableInfo createUserTable(){
  TableInfoCreator cr;
  cr.setTableName("USERS");
  cr.addColumn("ID", {"INT", "PRIMARY KEY","NOT NULL"});
  cr.addColumn("USERNAME", {"TEXT"});
  cr.addColumn("FIRSTNAME", {"TEXT"});
  cr.addColumn("LASTNAME", {"TEXT"});
  cr.addColumn("EMAIL", {"TEXT"});
  cr.addColumn("PHONE", {"TEXT"});
  cr.addColumn("USERSTATUS", {"INT"});
  return cr.createTableInfo();
}

// * UsersRoles
//    # id: uint64_t
//    # userId: uint64_t
//    # roleId: uint64_t
TableInfo createUsersRoles(){
  TableInfoCreator cr;
  cr.setTableName("USERSROLES");
  cr.addColumn("ID", {"INT", "PRIMARY KEY","NOT NULL"});
  cr.addColumn("USERID", {"INT"});
  cr.addColumn("ROLEID", {"INT"});
  return cr.createTableInfo();
}
}

#endif // GTEST_DEMO_TABLE_INFO_CREATOR_H
