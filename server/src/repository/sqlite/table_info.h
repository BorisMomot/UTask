//
// Created by boris on 16.11.2021.
//

#ifndef GTEST_DEMO_TABLE_INFO_H
#define GTEST_DEMO_TABLE_INFO_H

#include <string>
#include <vector>
#include <map>

class TableInfo{
public:
  typedef std::vector<std::string> properties;

  std::string getCreateCommand();
  std::vector<std::string> getColumsNames(){
    std::vector<std::string> columns;
    for (const auto& c: columnsProperties){
      columns.emplace_back(std::get<0>(c));
    }
    return columns;
  }
  const std::string &getTableName() const { return tableName; }
  const std::map<std::string, properties> &getColumsProperties() const {
    return columnsProperties;
  }
    bool isValid(){
    if (!tableName.empty() && !columnsProperties.empty()){
      return true;
    } else {
      return false;
    }
  }
  TableInfo(const std::string &tableName,
            const std::map<std::string, properties> &columnsProperties);

private:
  const std::string tableName;
  const std::map<std::string, properties> columnsProperties;
};

class TableInfoCreator{
  std::string tableName="";
  std::map<std::string, TableInfo::properties> columnsProperties{};

public:
  TableInfoCreator() {}
  void setTableName(const std::string &tableName) {
    TableInfoCreator::tableName = tableName;
  }

  void addColumn(const std::string& columnName, TableInfo::properties properties){
    auto p = std::make_pair(columnName, properties);
    columnsProperties.emplace(p);
  }

  TableInfo createTableInfo(){
    return TableInfo(tableName, columnsProperties);
  }
};






#endif // GTEST_DEMO_TABLE_INFO_H
