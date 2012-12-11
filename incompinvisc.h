#ifndef INCOMPINVISC_H_
#define INCOMPINVISC_H_

#include "physics.h"
//#include "kernel.h"
#include "particle.h"
#include "properties.h"
#include "kvector.h"
#include <math.h>

// Class for an incompressibe, inviscid fluid
class IncompInvisc : public Physics
{
public:
    IncompInvisc();
    ~IncompInvisc();
    int advance(Particle* part, Kernel* myKer);
    int update(Particle* part);
 
private:
    int NumberNeighbors;
    double drho_;
    double du_;
    double dv_;
    double coeff_;
    Kvector velDiff_;
    Kvector neighLoc_;
    Kvector gradKer_;
    Kvector partLoc_;
    Properties PartProps_;
    Properties NeighProps_;
};

#endif  // INCOMPINVISC_H_
