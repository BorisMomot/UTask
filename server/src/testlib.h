//
// Created by boris on 13.10.2021.
//

#ifndef GTEST_DEMO_TESTLIB_H
#define GTEST_DEMO_TESTLIB_H

//#include "logger.h"

class TestLib {
public:
  double add_numbers(const double f1, const double f2);
  double subtract_numbers(const double f1, const double f2);
  double multiply_numbers(const double f1, const double f2);

private:
//    Logger logger;
};

#endif // GTEST_DEMO_TESTLIB_H
