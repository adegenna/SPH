#ifndef PARTICLE_TEST_H_
#define PARTICLE_TEST_H_

#include <boost/shared_ptr.hpp>
#include "properties.h"
#include "particle.h"
#include "gtest/gtest.h"

class ParticleTest : public ::testing::Test{
  protected:
    virtual void SetUp(){
      props1_.x = 1.25;
      props1_.y = -12.4;
      props1_.u = -.5;
      props1_.v = 0.0003;
      props1_.density = 1.0;
      props1_.mass = 0.0;
      props1_.pressure = -2039;
      props1_.energy = 13;
      props2_.x = -3.25;
      props2_.y = 1.34;
      props2_.u = -98;
      props2_.v = -1.22;
      props2_.density = 2.7;
      props2_.mass = 1.005;
      props2_.pressure = 0.005;
      props2_.energy = 2;

      part1_.reset(new Particle(1,2,0,props1_));
      part2_.reset(new Particle(2,2,0,props2_));
    }

    Properties props1_, props2_;
    boost::shared_ptr<Particle> part1_, part2_;
};

#endif // PARTICLE_TEST_H_
