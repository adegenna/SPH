#ifndef KERNEL_TEST_H_
#define KERNEL_TEST_H_

#include "kernel.h"
#include "splinekernel.h"
#include "gaussiankernel.h"
#include "kvector.h"
#include "gtest/gtest.h"

class KernelTest : public ::testing::Test{
  protected:
    virtual void SetUp(){
      h_ = 1;
      for(int i=0; i<100; ++i){
        r_[i] = i*.011;
      }
    }
    virtual void TearDown(){ delete kernel_, r_; }

    Kernel *kernel_;
    double r_[100];
    double h_;
};

#endif // KERNEL_TEST_H_
