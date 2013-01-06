/**
 * \file
 *
 * \brief implentation of a cubic spline kernel
 */
#ifndef SPLINEKERNEL_H_
#define SPLINEKERNEL_H_

#include "kernel.h"

/// cubic spline approximation of point particle
class SplineKernel : public Kernel
{
public:
    /// ctor
    SplineKernel(double smoothinglength);
    /// dtor
    ~SplineKernel();
    /// returns value of cubic spline
    double W(double r);
    /// returns gradient of cubic spline
    Kvector gradW(Kvector vec1, Kvector vec2);
    /// returns Laplacian of cubic spline
    double lapW(double r);

private:
    double h_;
};

#endif  // SPLINEKERNEL_H_
