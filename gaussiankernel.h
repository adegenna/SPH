/**
 *  \file
 *
 *  \brief implementation of a Gaussian Kernel
 */
#ifndef GAUSSIANKERNEL_H_
#define GAUSSIANKERNEL_H_

#include "kernel.h"

/// Gaussian approximation of point particle
class GaussianKernel : public Kernel
{
public:
    /// ctor
    GaussianKernel(double smoothinglength);
    /// dtor
    ~GaussianKernel();
    /// returns value of Gaussian
    double W(double r);
    /// returns gradient of Gaussian
    Kvector gradW(Kvector vec1, Kvector vec2);
    /// returns value of the Laplacian of Gaussian
    double lapW(double r);

private:
    double h_;
};

#endif  // GAUSSIANKERNEL_H_
