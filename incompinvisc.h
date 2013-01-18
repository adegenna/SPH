/**
 * \file
 *
 * \brief implementation of Physics for a Fluid which is incompressible and 
 * inviscid
 */
#ifndef INCOMPINVISC_H_
#define INCOMPINVISC_H_

#include "physics.h"
#include "properties.h"
#include "kvector.h"

/// class for an incompressibe, inviscid fluid
class IncompInvisc : public Physics
{
  public:
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
    double B_;
    double gamma_;
    double rho_0_;
    double rx_;
    double ry_;
    double vdotr_;
    double mu_;
    double viscousforce_;
    Kvector veldiff_;
    Kvector neighloc_;
    Kvector gradker_;
    Kvector partloc_;
    Properties partprops_;
    Properties neighprops_;
    Properties bneighprops_;
};

#endif  // INCOMPINVISC_H_
