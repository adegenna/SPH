/**
 * \file
 *
 * \brief Tests SplineKernel and GaussianKernel
 */
#include "kernel_test.h"

/// tests GaussianKernel::W
TEST_F (KernelTest,gaussianW){
  GaussianKernel kernel(h_);
  for(int i=0; i<100; ++i){
    EXPECT_LE(0, kernel.W(r_[i]));
    EXPECT_GE(1, kernel.W(r_[i]));
  }
}

/// tests SplineKernel::W
TEST_F (KernelTest,splineW){
  SplineKernel kernel(h_);
  EXPECT_FLOAT_EQ(0, kernel.W(1.1));
  for(int i=0; i<100; ++i){
    EXPECT_LE(0, kernel.W(r_[i]));
    EXPECT_GE(1, kernel.W(r_[i]));
  }
}

/// tests GaussianKernel::GradW
TEST_F (KernelTest,gaussianGradW){
  Kvector kvec1, kvec2, kvec3;
  GaussianKernel kernel(h_);
  kvec1.x = 1;
  kvec1.y = 0;
  kvec2.x = -1;
  kvec2.y = 0;
  kvec3 = kernel.gradW(kvec1, kvec2);
  EXPECT_NE(0,kvec3.x);
  EXPECT_FLOAT_EQ(0,kvec3.y);

  kvec1.x = 0;
  kvec1.y = 0;
  kvec2.x = 1e-11;
  kvec2.y = 0;
  kvec3 = kernel.gradW(kvec1, kvec2);
  EXPECT_LE(fabs(kvec3.x), 1e-10);
  EXPECT_LE(fabs(kvec3.y), 1e-10);
}

/// tests SplineKernel::GradW
TEST_F (KernelTest,splineGradW){
  Kvector kvec1, kvec2, kvec3;
  SplineKernel kernel(h_);

  kvec1.x = .5;
  kvec1.y = 0;
  kvec2.x = 0;
  kvec2.y = 0;
  kvec3 = kernel.gradW(kvec1, kvec2);
  EXPECT_NE(0,kvec3.x);
  EXPECT_FLOAT_EQ(0,kvec3.y);

  kvec1.x = 1;
  kvec1.y = 0;
  kvec2.x = -1;
  kvec2.y = 0;
  kvec3 = kernel.gradW(kvec1, kvec2);
  EXPECT_FLOAT_EQ(0,kvec3.x);
  EXPECT_FLOAT_EQ(0,kvec3.y);

  kvec1.x = 0;
  kvec1.y = 0;
  kvec2.x = 1e-11;
  kvec2.y = 0;
  kvec3 = kernel.gradW(kvec1, kvec2);
  EXPECT_LE(fabs(kvec3.x), 1e-10);
  EXPECT_LE(fabs(kvec3.y), 1e-10);
}
