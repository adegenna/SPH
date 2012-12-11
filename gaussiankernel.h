#ifndef GAUSSIANKERNEL_H_
#define GAUSSIANKERNEL_H_

#include "kernel.h"

class GaussianKernel : public Kernel
{
public:
    GaussianKernel(double smoothinglength);
    ~GaussianKernel();
    double W(double r);
    Kvector gradW(Kvector vec1, Kvector vec2);
private:
    double h_;
};

#endif  // GAUSSIANKERNEL_H_
