#ifndef EULER_H_
#define EULER_H_

#include "integrator.h"
#include "fluid.h"
#include "physics.h"
#include "kernel.h"

class Physics;

class Euler : public Integrator {
 public:
  Euler(double dt,Fluid *fluid,Physics *physics);
  ~Euler();
  int step();
 private:
//  const int dimen_;                     // dimension of state x
    double dt_;                     // timestep
    Fluid *fluid_;                 
    Physics *physics_;
    double *fx_;   						// temporary space to hold f(x,t)
  	Particle** parts_;
};

#endif  // EULER_H
