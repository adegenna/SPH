#include "particle_test.h"

TEST_F (ParticleTest,checkGetSet){
  // check Particle::get
  ASSERT_EQ(0,part1_->get("OLD",props2_));
  EXPECT_FLOAT_EQ(1.25,props2_.x);
  EXPECT_FLOAT_EQ(-12.4,props2_.y);
  EXPECT_FLOAT_EQ(-.5,props2_.u);
  EXPECT_FLOAT_EQ(0.0003,props2_.v);
  EXPECT_FLOAT_EQ(1.0,props2_.density);
  EXPECT_FLOAT_EQ(0.0,props2_.mass);
  EXPECT_FLOAT_EQ(-2039,props2_.pressure);
  EXPECT_FLOAT_EQ(13,props2_.visc);
  
  // check Particle::set
  props2_.x = 0.0;
  ASSERT_EQ(0,part1_->set("NEW",props2_));
  ASSERT_EQ(0,part1_->get("NEW",props1_));
  EXPECT_EQ(props1_.x,props2_.x);
}

TEST_F (ParticleTest,checkNeighbors){
  // check numberOfNeighbors is initially 0
  EXPECT_EQ(0,part1_->numberOfNeighbors());

  // check that there is now 1 neighbor
  part1_->addNeighbor(part2_);
  EXPECT_EQ(1,part1_->numberOfNeighbors());

  // check that there are now 0 neighbors
  part1_->deleteNeighbors();
  EXPECT_EQ(0,part1_->numberOfNeighbors());
}

TEST_F (ParticleTest,checkGetTag){

  EXPECT_EQ(1,part1_->getTag());
  EXPECT_EQ(2,part2_->getTag());

}