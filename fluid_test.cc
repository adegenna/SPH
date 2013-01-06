/**
 * \file
 *
 * \brief tests for Fluid
 */
#include "fluid_test.h"

//TEST_F (FluidTest,checkAddGetParticle){
//  fluid_->addParticle(0,props1_);
//  fluid_->addParticle(1,props2_);
//    std::cout << "here" <<std::endl;
//  Particle **parts = new Particle*[2];
//    std::cout << "here2" <<std::endl;
//  fluid_->getParticles(parts);
//std::cout << "here3" <<std::endl;
//  EXPECT_EQ(0,parts[0]->getTag());
//  EXPECT_EQ(1,parts[1]->getTag());
//std::cout << "here4" <<std::endl;
//  delete parts;
//    std::cout << "here5" <<std::endl;
//}

/// tests Fluid::addBoundary and Fluid::getBoundaries
TEST_F (FluidTest,checkAddGetBoundary){
  fluid_->addBoundary(0,propsb_);

  Fluid::ParticleArray parts = fluid_->getBoundaries();

  EXPECT_EQ(0,parts[0]->getTag());
}

/// tests Fluid::findNeighbors
TEST_F (FluidTest,checkFindNeighbors){
  // NOTE: find neighbors is not working like I expected
  // it is working how it is written, but I expected something 
  // more along the lines of it listing all neighbors from lowest
  // tag to highest tag, including the self, which it is not written
  // that way. Need to talk to others about this. -- Kevin
  initFluid();

  fluid_->findNeighbors();
  Fluid::ParticleArray parts = fluid_->getParticles();
  Fluid::ParticleArray bound = fluid_->getBoundaries();

  const Particle::TagArray neighbors0 = parts[0]->getNeighbors();
  EXPECT_EQ(1,neighbors0[0]);
  EXPECT_EQ(2,neighbors0[1]);
  EXPECT_EQ(-1,neighbors0[2]);

  const Particle::TagArray neighbors1 = parts[1]->getNeighbors();
  EXPECT_EQ(0,neighbors1[0]);
  EXPECT_EQ(2,neighbors1[1]);
  EXPECT_EQ(-1,neighbors1[2]);

  const Particle::TagArray neighbors2 = parts[2]->getNeighbors();
  EXPECT_EQ(0,neighbors2[0]);
  EXPECT_EQ(1,neighbors2[1]);
  EXPECT_EQ(-1,neighbors2[2]);
  
  const Particle::TagArray boundneigh2 = parts[2]->getBoundaryNeighbors();
  EXPECT_EQ(0,boundneigh2[0]);

  fluid_->resetNeighbors();
}

/// tests Fluid::resetNeighbors undoes neighbor tags
TEST_F (FluidTest,checkResetNeighbors){
  initFluid();

  // if findNeighbors is working (see above test)
  // then this should produce different data
  Fluid::ParticleArray parts = fluid_->getParticles();
  fluid_->findNeighbors();
  fluid_->resetNeighbors();

  Particle::TagArray neighbors = parts[0]->getNeighbors();
  EXPECT_EQ(-1,neighbors[0]);
  EXPECT_EQ(-1,neighbors[1]);

  neighbors = parts[1]->getNeighbors();
  EXPECT_EQ(-1,neighbors[0]);
  EXPECT_EQ(-1,neighbors[1]);
}

/// tests Fluid::getKernel
TEST_F (FluidTest,checkGetKernel){
  Kernel &kernel = fluid_->getKernel();
  // this is here only to assert that Fluid::getKernel works,
  double x = -99999;
  EXPECT_NE(x,kernel.W(1));
}

/// tests Fluid::getNParticles
TEST_F (FluidTest,checkGetNParticles){
  initFluid();
  EXPECT_EQ(3,fluid_->getNParticles());
}

/// tests Fluid::getNBoundaries
TEST_F (FluidTest,checkGetNBoundaries){
  initFluid();
  EXPECT_EQ(1,fluid_->getNBoundaries());
}

/// tests Fluid::resetParticles updates particle properties
TEST_F (FluidTest,checkResetParticles){
  initFluid();
  Properties props1 = props1_;
  Properties props2 = props2_;
  Properties props3;

  props1.x = props1_.x + 1;
  props2.density = props2_.density - 1;

  Fluid::ParticleArray parts1(2);
  parts1[0].reset(new Particle(0,2,0,props1));
  parts1[1].reset(new Particle(1,2,0,props2));

  fluid_->resetParticles(parts1);
  Fluid::ParticleArray parts2 = fluid_->getParticles();

  props3 = parts2[0]->getOldProperties();
  EXPECT_FLOAT_EQ(props3.x,props1_.x+1);
  props3 = parts2[1]->getOldProperties();
  EXPECT_FLOAT_EQ(props3.density,props1_.density-1);
}

