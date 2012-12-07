#ifndef KERNEL_H_
#define KERNEL_H_

#include "Vector.h"

class Kernel
{
public:
    virtual ~Kernel() {}
    virtual double W(double r, double h) = 0;
    virtual Vector gradW(Vector vec1, Vector vec2, double h) = 0;

};

#endif  // KERNEL_H_
