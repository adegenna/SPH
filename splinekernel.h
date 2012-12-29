#ifndef SPLINEKERNEL_H_
#define SPLINEKERNEL_H_

#include "kernel.h"

class SplineKernel : public Kernel
{
public:
    SplineKernel(double smoothinglength);
    ~SplineKernel();
    double W(double r);
    Kvector gradW(Kvector vec1, Kvector vec2);
    double lapW(double r);

private:
    double h_;
};

#endif  // SPLINEKERNEL_H_
