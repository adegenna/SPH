#ifndef EULER_H_
#define EULER_H_

#include "integrator.h"
#include "fluid.h"
#include "physics.h"
#include "kernel.h"

class Physics;

class Euler : public Integrator {
 public:
  Euler(double dt, const Fluid &fluid, const Physics &physics);
  ~Euler();
  int Step(Particle* particle);
 private:
//  const int dimen_;                     // dimension of state x
    const double dt_;                     // timestep
    const Fluid fluid_;                 
    double *fx_;   						// temporary space to hold f(x,t)
  	Particle** parts_;
};

#endif  // EULER_H
