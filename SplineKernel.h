#ifndef SPLINEKERNEL_H_
#define SPLINEKERNEL_H_

#include "Kernel.h"

class SplineKernel : public Kernel
{
public:
    SplineKernel(double smoothinglength);
    ~SplineKernel();
    double W(double r, double h);
    Vector gradW(Vector vec1, Vector vec2, double h);
private:
    double h_;
};



#endif  // SPLINEKERNEL_H_
