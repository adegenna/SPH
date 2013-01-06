/**
 *  \file
 *
 *  \brief superclass for kernels
 */
#ifndef KERNEL_H_
#define KERNEL_H_

#include "kvector.h"

/// smooth kernels approximating point particles
class Kernel
{
  public:
    /// ctor
    virtual ~Kernel() {}
    /// returns value of kernel function
    virtual double W(double r) = 0;
    /// returns gradient of kernel function
    virtual Kvector gradW(Kvector vec1, Kvector vec2) = 0;
    /// returns value of the laplacian of the kernel function
    virtual double lapW(double r) = 0;

  private:
    double h_;
};

#endif  // KERNEL_H_
