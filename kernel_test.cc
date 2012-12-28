#include "kernel_test.h"

TEST_F (KernelTest,gaussianW){
  kernel_ = new GaussianKernel(h_);
  for(int i=0; i<100; ++i){
    EXPECT_LE(0,kernel_->W(r_[i]));
    EXPECT_GE(1,kernel_->W(r_[i]));
  }
}

TEST_F (KernelTest,DISABLED_splineW){
  kernel_ = new SplineKernel(h_);
  EXPECT_FLOAT_EQ(0,kernel_->W(1.1));
  for(int i=0; i<100; ++i){
    EXPECT_LE(0,kernel_->W(r_[i]));
    EXPECT_GE(1,kernel_->W(r_[i]));
  }
}

TEST_F (KernelTest,gaussianGradW){
  Kvector kvec1, kvec2, kvec3;
  kernel_ = new GaussianKernel(h_);
  kvec1.x = 1;
  kvec1.y = 0;
  kvec2.x = -1;
  kvec2.y = 0;
  kvec3 = kernel_->gradW(kvec1,kvec2);
  EXPECT_NE(0,kvec3.x);
  EXPECT_FLOAT_EQ(0,kvec3.y);

  kvec1.x = 0;
  kvec1.y = 0;
  kvec2.x = 1e-11;
  kvec2.y = 0;
  kvec3 = kernel_->gradW(kvec1,kvec2);
  EXPECT_FLOAT_EQ(0,kvec3.x);
  EXPECT_FLOAT_EQ(0,kvec3.y);
}

TEST_F (KernelTest,splineGradW){
  Kvector kvec1, kvec2, kvec3;
  kernel_ = new SplineKernel(h_);
  
  kvec1.x = .5;
  kvec1.y = 0;
  kvec2.x = 0;
  kvec2.y = 0;
  kvec3 = kernel_->gradW(kvec1,kvec2);
  EXPECT_NE(0,kvec3.x);
  EXPECT_FLOAT_EQ(0,kvec3.y);

  kvec1.x = 1;
  kvec1.y = 0;
  kvec2.x = -1;
  kvec2.y = 0;
  kvec3 = kernel_->gradW(kvec1,kvec2);
  EXPECT_FLOAT_EQ(0,kvec3.x);
  EXPECT_FLOAT_EQ(0,kvec3.y);

  kvec1.x = 0;
  kvec1.y = 0;
  kvec2.x = 1e-11;
  kvec2.y = 0;
  kvec3 = kernel_->gradW(kvec1,kvec2);
  EXPECT_FLOAT_EQ(0,kvec3.x);
  EXPECT_FLOAT_EQ(0,kvec3.y);
}
