//
// Created by boris on 13.10.2021.
//

#include <gtest/gtest.h>
#include "testlib.h"

TEST(testlib, substract) {
  double res;
  TestLib testLib;
  res = testLib.subtract_numbers(1.0, 2.0);
  ASSERT_NEAR(res, -1.0, 1.0e-11);
}

