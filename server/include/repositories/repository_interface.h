//
// Created by boris on 02.12.2021.
//

#ifndef GTEST_DEMO_REPOSITORY_INTERFACE_H
#define GTEST_DEMO_REPOSITORY_INTERFACE_H

#include <db_manager_interface.h>

class RepositoryInterface{
protected:
  DBManagerInterface* dbManagerInterface;
public:
  DBManagerInterface *getDbManagerInterface() const {
    return dbManagerInterface;
  }
  void setDbManagerInterface(DBManagerInterface *dbManagerInterface) {
    RepositoryInterface::dbManagerInterface = dbManagerInterface;
  }
};

#endif // GTEST_DEMO_REPOSITORY_INTERFACE_H
