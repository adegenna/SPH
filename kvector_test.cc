/**
 * \file
 *
 * \brief tests for Kvector
 */
#include "kvector_test.h"

// tests that Kvector initialized properly
TEST (KvectorTest,kvector){
  Kvector k;
  k.x = 1;
  k.y = -294.33;
  EXPECT_EQ(1,k.x);
  EXPECT_EQ(-294.33,k.y);
}
