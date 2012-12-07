#ifndef GAUSSIANKERNEL_H_
#define GAUSSIANKERNEL_H_

#include "Kernel.h"

class GaussianKernel : public Kernel
{
public:
    virtual double W(double r, double h);
    virtual Vector gradW(Vector vec1, Vector vec2, double h);

};

#endif  // GAUSSIANKERNEL_H_
