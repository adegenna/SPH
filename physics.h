#ifndef PHYSICS_H_
#define PHYSICS_H_
#include "particle.h"
#include "Kernel.h"

class Physics {
 public:
  virtual ~Physics() {}

  // general update function
    virtual int advance(Particle* part, Kernel* myKer) = 0;
    virtual int update(Particle* part) = 0;
  // number of states (size of x)
  //virtual int dimen() const = 0;
};

#endif  // PHYSICS_H_
