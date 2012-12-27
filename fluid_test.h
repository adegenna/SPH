#ifndef FLUID_TEST_H_
#define FLUID_TEST_H_

#include "properties.h"
#include "particle.h"
#include "fluid.h"
#include "gaussiankernel.h"
#include "gtest/gtest.h"

class FluidTest : public ::testing::Test{
  protected:
    FluidTest(){}
    ~FluidTest(){}
};

#endif // FLUID_TEST_H_
