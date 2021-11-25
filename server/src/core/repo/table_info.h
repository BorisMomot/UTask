//
// Created by boris on 16.11.2021.
//

#ifndef GTEST_DEMO_TABLE_INFO_H
#define GTEST_DEMO_TABLE_INFO_H

#include <string>
#include <vector>
#include <map>

/// @brief Класс отвечает за хранение информации о таблице в базе данных
/// При создании объекта необходимо передать в конструктор имя таблицы и все поля настройки
/// Для удобства создания был введен класс упрощающий процесс создания
class TableInfo{
public:
  typedef std::vector<std::string> properties;

  /// Получить имя таблицы
  const std::string &getTableName() const { return tableName; }
  /// Получить имена колонок
  std::vector<std::string> getColumsNames(){
    std::vector<std::string> columns;
    for (const auto& c: columnsProperties){
      columns.emplace_back(std::get<0>(c));
    }
    return columns;
  }
  /// Получить имена столбцов и их свойства
  const std::map<std::string, properties> &getColumsProperties() const {
    return columnsProperties;
  }
  /// Проверка, что поля заданы корректно
  bool isValid(){
    if (!tableName.empty() && !columnsProperties.empty()){
      return true;
    } else {
      return false;
    }
  }

  TableInfo(const std::string &tableName,
            const std::map<std::string, properties> &columnsProperties): tableName(tableName), columnsProperties(columnsProperties){}

private:
  const std::string tableName;
  const std::map<std::string, properties> columnsProperties;
};

/// Вспомогательный класс для создания таблиц
class TableInfoBuilder {
  std::string tableName="";
  std::map<std::string, TableInfo::properties> columnsProperties{};

public:
  TableInfoBuilder() {}
  void setTableName(const std::string &tableName) {
    TableInfoBuilder::tableName = tableName;
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
