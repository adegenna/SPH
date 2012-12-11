#ifndef KERNEL_H_
#define KERNEL_H_

#include "vector.h"

class Kernel
{
public:
    virtual ~Kernel() {}
    virtual double W(double r) = 0;
    virtual Vector gradW(Vector vec1, Vector vec2) = 0;
};

#endif  // KERNEL_H_
