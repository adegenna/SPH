#ifndef PHYSICS_H_
#define PHYSICS_H_
#include "particle.h"
#include "kernel.h"

class Fluid;
class Physics {
 public:
  virtual ~Physics() {}

  // general update function
  virtual int rhs(Fluid* fluid, Particle* part, Kernel* myKer,Properties &fx) = 0;
    virtual int update(Particle* part) = 0;
    virtual int calcPressure(Particle* part) = 0;
  // number of states (size of x)
  //virtual int dimen() const = 0;
};

#endif  // PHYSICS_H_
