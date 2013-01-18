/**
 * \file
 *
 * \brief tests for Fluid
 */
#include "fluid_test.h"

Properties pos(double x, double y){
  Properties props;
  props.x = x;
  props.y = y;
  props.u = 0;
  props.v = 0;
  props.density = 0;
  props.energy = 0;
  props.pressure = 0;
  props.mass = 0;
  return props;
}

/// tests Fluid::addBoundary and Fluid::getBoundaries
TEST_F (FluidTest,checkAddGetBoundary){
  fluid_->addBoundary(0,propsb_);

  Fluid::ParticleArray parts = fluid_->getBoundaries();

  EXPECT_EQ(0,parts[0]->getTag());
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

/// tests Fluid::findNeighbors
TEST_F (FluidTest,_checkFindNeighbors){
  double sl = 2;
  int np = 2;
  int nb = 0;
  boost::shared_ptr<Fluid> fl;
  std::vector< boost::shared_ptr<Particle> > parts;
  std::vector<int>neighbs;
  boost::shared_ptr<Kernel> ker;
  ker.reset(new GaussianKernel(sl));

  // check current square is neighbor
  fl.reset(new Fluid(*ker,np,nb,sl));
  fl->addParticle(0,pos(0,0));
  fl->addParticle(1,pos(1,0));
  fl->findNeighbors();

  parts = fl->getParticles();
  neighbs = parts[0]->getNeighbors();
  EXPECT_EQ(neighbs[0],1);
  EXPECT_EQ(neighbs[1],-1);
  neighbs = parts[1]->getNeighbors();
  EXPECT_EQ(neighbs[0],0);
  EXPECT_EQ(neighbs[1],-1);

  fl.reset(new Fluid(*ker,np,nb,sl));
  fl->addParticle(0,pos(0,0));
  fl->addParticle(1,pos(0,1));
  fl->findNeighbors();

  parts = fl->getParticles();
  neighbs = parts[0]->getNeighbors();
  EXPECT_EQ(neighbs[0],1);
  EXPECT_EQ(neighbs[1],-1);
  neighbs = parts[1]->getNeighbors();
  EXPECT_EQ(neighbs[0],0);
  EXPECT_EQ(neighbs[1],-1);
  
  fl.reset(new Fluid(*ker,np,nb,sl));
  fl->addParticle(0,pos(0,0));
  fl->addParticle(1,pos(1,1));
  fl->findNeighbors();

  parts = fl->getParticles();
  neighbs = parts[0]->getNeighbors();
  EXPECT_EQ(neighbs[0],1);
  EXPECT_EQ(neighbs[1],-1);
  neighbs = parts[1]->getNeighbors();
  EXPECT_EQ(neighbs[0],0);
  EXPECT_EQ(neighbs[1],-1);
  
  // check one right is neighbor
  fl.reset(new Fluid(*ker,np,nb,sl));
  fl->addParticle(0,pos(0,0));
  fl->addParticle(1,pos(3,0));
  fl->findNeighbors();

  parts = fl->getParticles();
  neighbs = parts[0]->getNeighbors();
  EXPECT_EQ(neighbs[0],1);
  EXPECT_EQ(neighbs[1],-1);
  neighbs = parts[1]->getNeighbors();
  EXPECT_EQ(neighbs[0],0);
  EXPECT_EQ(neighbs[1],-1);

  // check one up is neighbor
  fl.reset(new Fluid(*ker,np,nb,sl));
  fl->addParticle(0,pos(0,0));
  fl->addParticle(1,pos(0,3));
  fl->findNeighbors();

  parts = fl->getParticles();
  neighbs = parts[0]->getNeighbors();
  EXPECT_EQ(neighbs[0],1);
  EXPECT_EQ(neighbs[1],-1);
  neighbs = parts[1]->getNeighbors();
  EXPECT_EQ(neighbs[0],0);
  EXPECT_EQ(neighbs[1],-1);

  // check one up, one right is neighbor
  fl.reset(new Fluid(*ker,np,nb,sl));
  fl->addParticle(0,pos(0,0));
  fl->addParticle(1,pos(3,3));
  fl->findNeighbors();

  parts = fl->getParticles();
  neighbs = parts[0]->getNeighbors();
  EXPECT_EQ(neighbs[0],1);
  EXPECT_EQ(neighbs[1],-1);
  neighbs = parts[1]->getNeighbors();
  EXPECT_EQ(neighbs[0],0);
  EXPECT_EQ(neighbs[1],-1);

  // check two right has no neighbors
  fl.reset(new Fluid(*ker,np,nb,sl));
  fl->addParticle(0,pos(0,0));
  fl->addParticle(1,pos(5,0));
  fl->findNeighbors();

  parts = fl->getParticles();
  neighbs = parts[0]->getNeighbors();
  EXPECT_EQ(neighbs[0],-1);
  EXPECT_EQ(neighbs[1],-1);
  neighbs = parts[1]->getNeighbors();
  EXPECT_EQ(neighbs[0],-1);
  EXPECT_EQ(neighbs[1],-1);

  // check two above has no neighbors
  fl.reset(new Fluid(*ker,np,nb,sl));
  fl->addParticle(0,pos(0,0));
  fl->addParticle(1,pos(0,5));
  fl->findNeighbors();

  parts = fl->getParticles();
  neighbs = parts[0]->getNeighbors();
  EXPECT_EQ(neighbs[0],-1);
  EXPECT_EQ(neighbs[1],-1);
  neighbs = parts[1]->getNeighbors();
  EXPECT_EQ(neighbs[0],-1);
  EXPECT_EQ(neighbs[1],-1);
  
  // check two right, one up has no neighbors
  fl.reset(new Fluid(*ker,np,nb,sl));
  fl->addParticle(0,pos(0,0));
  fl->addParticle(1,pos(5,3));
  fl->findNeighbors();

  parts = fl->getParticles();
  neighbs = parts[0]->getNeighbors();
  EXPECT_EQ(neighbs[0],-1);
  EXPECT_EQ(neighbs[1],-1);
  neighbs = parts[1]->getNeighbors();
  EXPECT_EQ(neighbs[0],-1);
  EXPECT_EQ(neighbs[1],-1);

  // check two up, one right has no neighbors
  fl.reset(new Fluid(*ker,np,nb,sl));
  fl->addParticle(0,pos(0,0));
  fl->addParticle(1,pos(3,5));
  fl->findNeighbors();

  parts = fl->getParticles();
  neighbs = parts[0]->getNeighbors();
  EXPECT_EQ(neighbs[0],-1);
  EXPECT_EQ(neighbs[1],-1);
  neighbs = parts[1]->getNeighbors();
  EXPECT_EQ(neighbs[0],-1);
  EXPECT_EQ(neighbs[1],-1);

  // check two up, two right has no neighbors
  fl.reset(new Fluid(*ker,np,nb,sl));
  fl->addParticle(0,pos(0,0));
  fl->addParticle(1,pos(5,5));
  fl->findNeighbors();

  parts = fl->getParticles();
  neighbs = parts[0]->getNeighbors();
  EXPECT_EQ(neighbs[0],-1);
  EXPECT_EQ(neighbs[1],-1);
  neighbs = parts[1]->getNeighbors();
  EXPECT_EQ(neighbs[0],-1);
  EXPECT_EQ(neighbs[1],-1);

}
