/**
 * \file
 *
 * \brief tests Particle
 */
#include "particle_test.h"

/// tests Particle::getOldProperties and Particle::setNewProperties
TEST_F (ParticleTest,checkGetSet){
  // check Particle::get
  props2_ = part1_->getOldProperties();
  EXPECT_FLOAT_EQ(1.25,props2_.x);
  EXPECT_FLOAT_EQ(-12.4,props2_.y);
  EXPECT_FLOAT_EQ(-.5,props2_.u);
  EXPECT_FLOAT_EQ(0.0003,props2_.v);
  EXPECT_FLOAT_EQ(1.0,props2_.density);
  EXPECT_FLOAT_EQ(0.0,props2_.mass);
  EXPECT_FLOAT_EQ(-2039,props2_.pressure);
  EXPECT_FLOAT_EQ(13,props2_.energy);
  
  // check Particle::set
  props2_.x = 0.0;
  part1_->setNewProperties(props2_);
  props1_ = part1_->getNewProperties();
  EXPECT_EQ(props1_.x,props2_.x);
}

/// tests Particle::numberOfNeighbors, Particle::addNeighbor, Particle::deleteNeighbors
TEST_F (ParticleTest,checkNeighbors){
  // check numberOfNeighbors is initially 0
  EXPECT_EQ(0,part1_->numberOfNeighbors());

  // check that there is now 1 neighbor
  part1_->addNeighbor(*part2_);
  EXPECT_EQ(1,part1_->numberOfNeighbors());

  // check that there are now 0 neighbors
  part1_->deleteNeighbors();
  EXPECT_EQ(0,part1_->numberOfNeighbors());
}

/// tests Particle::getTag
TEST_F (ParticleTest,checkGetTag){

  EXPECT_EQ(1,part1_->getTag());
  EXPECT_EQ(2,part2_->getTag());

}
