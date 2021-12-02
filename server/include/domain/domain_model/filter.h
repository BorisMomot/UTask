//
// Created by boris on 15.11.2021.
//

#ifndef GTEST_DEMO_FILTER_H
#define GTEST_DEMO_FILTER_H
#include <string>

class Filter{
  std::string filterField;
  std::string filterValue;

public:
  Filter(const std::string &filterField, const std::string &filterValue)
      : filterField(filterField), filterValue(filterValue) {}
  const std::string &getFilterField() const;
  const std::string &getFilterValue() const;
};


#endif // GTEST_DEMO_FILTER_H
