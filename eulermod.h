/**
 * \file
 *
 * \brief implementation of Euler Integrator, modified so that the position is 
 * updated using the updated velocity
 *        
 */
#ifndef EULERMOD_H_
#define EULERMOD_H_

#include "integrator.h"
#include "fluid.h"
#include "physics.h"
#include "particle.h"

class Fluid;
class Physics;

/// modified Euler integrator
class Eulermod : public Integrator {
  public:
    /// ctor
    Eulermod(double dt, Fluid& fluid, Physics& physics);
    /// advances one timestep
    int step();

  private:
    double dt_;         // timestep
    Fluid& fluid_;
    Physics& physics_;
    Properties fx_;     //struct to store the changes in particle properties,
    //which itself can be a Properties struct.
};

#endif  // EULERMOD_H_
