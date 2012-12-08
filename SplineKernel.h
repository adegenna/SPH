#ifndef SPLINEKERNEL_H_
#define SPLINEKERNEL_H_

#include "Kernel.h"

class SplineKernel : public Kernel
{
public:
    SplineKernel(double smoothinglength);
    ~SplineKernel();
    double W(double r);
    Vector gradW(Vector vec1, Vector vec2);
private:
    double h_;
};



#endif  // SPLINEKERNEL_H_
