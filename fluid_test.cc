#include "fluid_test.h"

TEST_F (FluidTest,checkAddGetParticle){
  fluid_->addParticle(0,props1_);
  fluid_->addParticle(1,props2_);

  Particle **parts = new Particle*[2];
  fluid_->getParticles(parts);

  EXPECT_EQ(0,parts[0]->getTag());
  EXPECT_EQ(1,parts[1]->getTag());

  delete parts;
}

TEST_F (FluidTest,checkAddGetBoundary){
  fluid_->addBoundary(0,propsb_);

  Particle **parts = new Particle*[1];
  fluid_->getBoundaries(parts);

  EXPECT_EQ(0,parts[0]->getTag());

  delete parts;
}

TEST_F (FluidTest,checkFindNeighbors){
  // NOTE: find neighbors is not working like I expected
  // it is working how it is written, but I expected something 
  // more along the lines of it listing all neighbors from lowest
  // tag to highest tag, including the self, which it is not written
  // that way. Need to talk to others about this. -- Kevin
  initFluid();
  Particle **parts = new Particle*[2];
  int neighbors[2];

  fluid_->findNeighbors();
  fluid_->getParticles(parts);

  parts[0]->getNeighbors(neighbors);
  EXPECT_EQ(0,neighbors[0]);
  EXPECT_EQ(1,neighbors[1]);

  parts[1]->getNeighbors(neighbors);
  EXPECT_EQ(0,neighbors[0]);
  EXPECT_EQ(1,neighbors[1]);

  delete parts, neighbors;
}

TEST_F (FluidTest,checkResetNeighbors){
  initFluid();
  Particle **parts = new Particle*[2];
  int neighbors[2];

  // if findNeighbors is working (see above test)
  // then this should produce different data
  fluid_->findNeighbors();
  fluid_->resetNeighbors();
  fluid_->getParticles(parts);

  parts[0]->getNeighbors(neighbors);
  EXPECT_EQ(-1,neighbors[0]);
  EXPECT_EQ(-1,neighbors[1]);

  parts[1]->getNeighbors(neighbors);
  EXPECT_EQ(-1,neighbors[0]);
  EXPECT_EQ(-1,neighbors[1]);

  delete parts, neighbors;
}

TEST_F (FluidTest,checkGetKernel){
  Kernel *kernel;
  kernel = fluid_->getKernel();

  // this is here only to assert that Fluid::getKernel works,
  // as the destructor below is not working (not sure why)
  double x = -99999;
  EXPECT_NE(x,kernel->W(1));

  // the delete below is causing a seg fault
  // the destructors seem to be in place, but there is no kernel
  // constructor, so maybe that's it??

  //delete kernel;
}

TEST_F (FluidTest,checkGetNParticles){
  initFluid();
  EXPECT_EQ(2,fluid_->getNParticles());
}

TEST_F (FluidTest,checkGetNBoundaries){
  initFluid();
  EXPECT_EQ(1,fluid_->getNBoundaries());
}

TEST_F (FluidTest,checkResetParticles){
  initFluid();
  Properties props1 = props1_;
  Properties props2 = props2_;
  Properties props3;

  props1.x = props1_.x + 1;
  props2.density = props2_.density - 1;

  Particle **parts1 = new Particle*[2];
  Particle **parts2 = new Particle*[2];
  parts1[0] = new Particle(0,2,props1);
  parts1[1] = new Particle(1,2,props2);

  fluid_->resetParticles(parts1);
  fluid_->getParticles(parts2);

  parts2[0]->get("OLD",props3);
  EXPECT_FLOAT_EQ(props3.x,props1_.x+1);
  parts2[1]->get("OLD",props3);
  EXPECT_FLOAT_EQ(props3.density,props1_.density-1);

  delete parts1, parts2;
}

