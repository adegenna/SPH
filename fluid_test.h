#ifndef FLUID_TEST_H_
#define FLUID_TEST_H_

#include "properties.h"
#include "particle.h"
#include "fluid.h"
#include "gaussiankernel.h"
#include "gtest/gtest.h"

class FluidTest : public ::testing::Test{
  protected:
    virtual void SetUp(){
      smoothinglength_ = 1;
      kernel_ = new GaussianKernel(smoothinglength_);

      props1_.x = 1;
      props1_.y = -1;
      props1_.u = 0;
      props1_.v = 0.1;
      props1_.density = 1;
      props1_.mass = 1;
      props1_.pressure = 2;
      props1_.visc = 1;

      props2_.x = 1;
      props2_.y = -1.0001;
      props2_.u = 0;
      props2_.v = -0.1;
      props2_.density = 1;
      props2_.mass = 1;
      props2_.pressure = 2;
      props2_.visc = 1;

      props3_.x = 1;
      props3_.y = -1.0005;
      props3_.u = 0;
      props3_.v = -0.1;
      props3_.density = 1;
      props3_.mass = 1;
      props3_.pressure = 2;
      props3_.visc = 1;

      propsb_.x = 0;
      propsb_.y = 0;
      propsb_.u = 0;
      propsb_.v = 0;
      propsb_.density = 100;
      propsb_.mass = 100;
      propsb_.pressure = 0;
      propsb_.visc = 100;

      fluid_ = new Fluid(kernel_,3,1,smoothinglength_);
    }

    virtual void TearDown(){
        delete kernel_;
        delete fluid_;
    }

    virtual void initFluid(){
      // helper function for some tests
      fluid_->addParticle(0,props1_);
      fluid_->addParticle(1,props2_);
      fluid_->addParticle(2,props3_);
      fluid_->addBoundary(0,propsb_);
    }

    Properties props1_, props2_, props3_, propsb_;
    Fluid *fluid_;
    double smoothinglength_;

//  private:
    Kernel *kernel_;
};

#endif // FLUID_TEST_H_
