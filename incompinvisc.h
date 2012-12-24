#ifndef INCOMPINVISC_H_
#define INCOMPINVISC_H_

#include "physics.h"
//#include "kernel.h"
#include "particle.h"
#include "properties.h"
#include "kvector.h"
#include <math.h>
#include "fluid.h"

// Class for an incompressibe, inviscid fluid
class IncompInvisc : public Physics
{
public:
    IncompInvisc();
    ~IncompInvisc();
    int rhs(Fluid* fluid, Particle* part, Kernel* myker,Properties* fx);
    int update(Particle* part);
    int calcPressure(Particle* part); 
private:
    int numberneighbors;
    double drho_;
    double du_;
    double dv_;
    double dt_;
    double coeff_;
    Kvector veldiff_;
    Kvector neighloc_;
    Kvector gradker_;
    Kvector partloc_;
    Properties partprops_;
    Properties neighprops_;
};

#endif  // INCOMPINVISC_H_