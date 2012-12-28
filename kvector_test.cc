#include "kvector_test.h"

TEST (KvectorTest,kvector){
  Kvector k;
  k.x = 1;
  k.y = -294.33;
  EXPECT_EQ(1,k.x);
  EXPECT_EQ(-294.33,k.y);
}
