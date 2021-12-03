//
// Created by boris on 16.11.2021.
//

#ifndef GTEST_DEMO_TABLE_INFO_FACTORY_H
#define GTEST_DEMO_TABLE_INFO_FACTORY_H

#include "table_info.h"

class TableInfoFactory{
  virtual TableInfo createTaskTable() = 0;
  virtual TableInfo createProjectTable() = 0;
  virtual TableInfo createRoleTable() = 0;
  virtual TableInfo createUserTable() = 0;
  virtual TableInfo createUsersRoles() = 0;
};


class TableInfoSQLiteFactory: public TableInfoFactory {
public:
// * Tasks
//      # id: uint64_t
//      # priority:	int64_t
//      # name:	String
//      # status:	String
//      # userCreator:	uint64_t
//      # userExecutor:	uint64_t
//      # description:	String
//      # stored:	String
  TableInfo createTaskTable() override {
    TableInfoBuilder cr;
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

// * Projects
//    # id: uint64_t
//    # name:	String
//    # description:	String
  TableInfo createProjectTable() override {
    TableInfoBuilder cr;
    cr.setTableName("PROJECTS");
    cr.addColumn("ID", {"INT", "PRIMARY KEY","NOT NULL"});
    cr.addColumn("NAME", {"TEXT"});
    cr.addColumn("DESCRIPTION", {"TEXT"});
    return cr.createTableInfo();
  }

// * Roles
//    # id: uint64_t
//    # name:	String
//    # description:	String
  TableInfo createRoleTable() override {
    TableInfoBuilder cr;
    cr.setTableName("ROLES");
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
  TableInfo createUserTable() override {
    TableInfoBuilder cr;
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
  TableInfo createUsersRoles() override {
    TableInfoBuilder cr;
    cr.setTableName("USERSROLES");
    cr.addColumn("ID", {"INT", "PRIMARY KEY","NOT NULL"});
    cr.addColumn("USERID", {"INT"});
    cr.addColumn("ROLEID", {"INT"});
    return cr.createTableInfo();
  }
};

#endif // GTEST_DEMO_TABLE_INFO_FACTORY_H
