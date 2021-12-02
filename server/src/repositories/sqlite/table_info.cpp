//
// Created by boris on 16.11.2021.
//
#include <sstream>
#include "table_info.h"
TableInfo::TableInfo(const std::string &tableName,
                     const std::map<std::string, properties> &columnsProperties)
    : tableName(tableName), columnsProperties(columnsProperties) {}
std::string TableInfo::getCreateCommand() {
  std::ostringstream command;

  command << "CREATE TABLE " << tableName << " (";
  for (const auto& p:columnsProperties){
    command << " " <<  p.first << " ";
    for (const auto& s: p.second){
      command << " " << s;
    }
  }
  return command.str();
}
