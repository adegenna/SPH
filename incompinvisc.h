#ifndef INCOMPINVISC_H_
#define INCOMPINVISC_H_

#include "Physics.h"
//#include "Kernel.h"
#include "particle.h"
#include "properties.h"
#include "Vector.h"
#include <math.h>
//#include <stdio.h>
//#include <iostream>
//#include <stdlib.h>


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
    Vector velDiff_;
    Vector neighLoc_;
    Vector gradKer_;
    Vector partLoc_;
    Properties PartProps_;
    Properties NeighProps_;
};

#endif  // INCOMPINVISC_H_
