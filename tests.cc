#include <stdlib.h>
#include <iostream>
#include "gtest/gtest.h"

#include "properties_test.h"

using namespace std;

int main(int argc, char** argv){

  cout << "Testing fluid properties: " << endl;

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

  return 0;
}
