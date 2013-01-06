/**
 * \file
 *
 * \brief implementation of euler integrator
 */
#ifndef EULER_H_
#define EULER_H_

#include "integrator.h"

class Fluid;
class Physics;

/// euler integrator
class Euler : public Integrator {
 public:
  /// ctor
  Euler(double dt, Fluid& fluid, Physics& physics);
  /// advances one timestep
  int step();

 private:
    double dt_;                     // timestep
    Fluid& fluid_;
    Physics& physics_;
};

#endif  // EULER_H
