/**
 * \file
 *
 * \brief Implementation of predictor-corrector integration scheme
 */
#ifndef PREDICTORCORRECTOR_H_
#define PREDICTORCORRECTOR_H_

#include "integrator.h"
#include "fluid.h"
#include "physics.h"
#include "particle.h"

class Fluid;
class Physics;

/// euler integrator
class PredictorCorrector : public Integrator {
 public:
  /// ctor
  PredictorCorrector(double dt, Fluid& fluid, Physics& physics);
  /// advances one timestep
  int step();

 private:
    double dt_;                     // timestep
    Fluid& fluid_;
    Physics& physics_;
    Properties fx_;
};

#endif  // PREDICTORCORRECTOR_H_
