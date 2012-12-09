#ifndef INCOMPINVISC_H_
#define INCOMPINVISC_H_

#include "Fluid.h"
//#include "Kernel.h"
#include "particle.h"
#include "properties.h"
#include "Vector.h"
#include <math.h>


// Class for an incompressibe, inviscid fluid
class IncompInvisc : public Fluid
{
public:
    IncompInvisc();
    ~IncompInvisc();
    int update(Particle* part, Kernel* myKer);
 
private:
    int NumberNeighbors;
    double drho_;
    double du_;
    double dv_;
    double coeff_;
    Vector velDiff_;
    Vector neighLoc_;
    Vector gradKer_;
    Vector partLoc_;
};

#endif  // INCOMPINVISC_H_
