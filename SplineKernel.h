#ifndef SPLINEKERNEL_H_
#define SPLINEKERNEL_H_

#include "Kernel.h"

class SplineKernel : public Kernel
{
public:
    virtual double W(double r, double h);
    virtual Vector gradW(Vector vec1, Vector vec2, double h);

};

#endif  // SPLINEKERNEL_H_
