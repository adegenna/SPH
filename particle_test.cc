#include "particle_test.h"

TEST (ParticleTest,checkGetSet){
  Properties props1, props2;
  props1.x = 1.25;
  props1.y = -12.4;
  props1.u = -.5;
  props1.v = 0.0003;
  props1.density = 1.0;
  props1.mass = 0.0;
  props1.pressure = -2039;
  props1.visc = 13;
}

TEST (ParticleTest,checkAddNeighbor){}

TEST (ParticleTest,checkDeleteNeighbors){}

TEST (ParticleTest,checkNumberOfNeighbors){}

TEST (ParticleTest,checkGetNeighbors){}

TEST (ParticleTest,checkGetTag){}
