#ifndef EULER_H_
#define EULER_H_

#include "integrator.h"

class Fluid;
class Physics;

class Euler : public Integrator {
 public:
  Euler(double dt, Fluid& fluid, Physics& physics);
  int step();

 private:
    double dt_;                     // timestep
    Fluid& fluid_;
    Physics& physics_;
};

#endif  // EULER_H
