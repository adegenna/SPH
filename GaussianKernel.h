#ifndef GAUSSIANKERNEL_H_
#define GAUSSIANKERNEL_H_

#include "Kernel.h"

class GaussianKernel : public Kernel
{
public:
    GaussianKernel(double smoothinglength);
    ~GaussianKernel();
    double W(double r);
    Vector gradW(Vector vec1, Vector vec2);
private:
    double h_;
};

#endif  // GAUSSIANKERNEL_H_
