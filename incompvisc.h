/**
 * \file
 *
 * \brief implementation of Physics for a fluid which is incompressible and viscous
 */
#ifndef INCOMPVISC_H_
#define INCOMPVISC_H_

#include "physics.h"
#include "properties.h"
#include "kvector.h"
#include "fluid.h"
#include "particle.h"
#include "kernel.h"
#include <cmath>

/// class for an incompressible fluid with the inclusion of viscous forces
class IncompVisc : public Physics
{
public:
    /// ctor
    IncompVisc(double smoothinglength,  //!< input smoothinglength of fluid
               double grav,             //!< input gravitational acceleration
               double pressB,           //!< input pressure coefficient B
               double pressGamma,       //!< input pressure exponent Gamma
               double rho_0,            //!< input reference density
               double viscMu,           //!< input viscosity parameter mu
               double viscEta           //!< inpu tviscosity parameter eta
               );
    
    /// update function
    int rhs(Fluid& fluid, //!< input fluid
        Particle& part,   //!< particular fluid particle
        Kernel& myker,    //!< kernel to use
        Properties& fx    //!< stores changes of update
        );
    /// move part's new properties to old properties
    int update(Particle& part);
    /// calculates pressure
    int calcPressure(Particle& part);
    int initPressureParams();
private:
    int numberneighbors_;
    int numberboundaryneighbors_;
    double drho_;
    double du_;
    double dv_;
    double dt_;
    double coeff_;
    double r0_;
    double grav_;
    double pressB_;
    double pressGamma_;
    double rho_0_;
    double viscAlpha_;
    double viscMu_;
    double viscEta_;
    double viscousforce_;
    double rx_;
    double ry_;
    double vdotr_;    
    Kvector veldiff_;
    Kvector neighloc_;
    Kvector gradker_;
    Kvector partloc_;
    Properties partprops_;
    Properties neighprops_;
    Properties bneighprops_;
};

#endif  // INCOMPVISC_H_
