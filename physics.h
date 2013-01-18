/**
 * \file
 *
 * \brief superclass for implementing different fluid physics
 */
#ifndef PHYSICS_H_
#define PHYSICS_H_

class Fluid;
class Particle;
class Kernel;
struct Properties;

/// superclass for implementing different fluid physics
class Physics {
  public:
    /// dtor
    virtual ~Physics() {}

    /// update function
    virtual int rhs(Fluid& fluid, //!< input fluid
        Particle& part,           //!< particular fluid particle
        Kernel& myKer,            //!< kernel to use
        Properties& fx            //!< stores changes of update
        ) = 0;
    /// move part's new properties to old properties
    virtual int update(Particle& part) = 0;
    /// calculates pressure
    virtual int calcPressure(Particle& part) = 0;
    virtual int initPressureParams() = 0;
};

#endif  // PHYSICS_H_
