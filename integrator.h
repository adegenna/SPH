/**
 * \file
 *
 * \brief superclass for integrators
 */
#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

/// superclass for integrators
class Integrator {
 public:
  /// dtor
  virtual ~Integrator() {}
  /// required function advancing one timestep
  virtual int step() = 0;
};

#endif  // INTEGRATOR_H_
