
#include "GaussianKernel.h"
#include <cmath>

GaussianKernel::GaussianKernel(double smoothinglength)
    : h_(smoothinglength)
{}

GaussianKernel::~GaussianKernel()
{}

double GaussianKernel::W(double r)
{
    const double disthat = r / h_;
    const double rtpi = sqrt(M_PI);
    return exp(-pow(disthat,2))/h_/rtpi;
}

Vector GaussianKernel::gradW(Vector vec1, Vector vec2)
{
    const double rMag = hypot(vec2.x-vec1.x, vec2.y-vec1.y);
    const double kMag = 2* rMag/h_/h_ * W(rMag); //took out -ve
    Vector K = {0.,0.};

    if(fabs(rMag)> 1e-10)
    {
        K.x = -(vec2.x-vec1.x)/rMag* kMag;
        K.y = -(vec2.y-vec1.y)/rMag* kMag;
    }
    return K;
}


