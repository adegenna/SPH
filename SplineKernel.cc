
#include "SplineKernel.h"
#include <cmath>

SplineKernel::SplineKernel(double smoothinglength)
    : h_(smoothinglength)
{}

SplineKernel::~SplineKernel()
{}

double SplineKernel::W(double r, double h)
{
    const double disthat = r / h;
    const double C = 8 * M_PI /pow(h,3);
    if (disthat <= 0.5)
    {
        return C* (1- 6 * pow(disthat,2)+ 6 * pow(disthat,3));
    }
    else if (disthat <=1)
    {
        return C * 2 * pow(1 -disthat,3);
    }
    else
    {
        return 0;
    }
}

Vector SplineKernel::gradW(Vector vec1, Vector vec2, double h)
{
    const double rMag = hypot(vec2.x-vec1.x, vec2.y-vec1.y);
    const double disthat = rMag / h;
    const double C = 8 * M_PI /pow(h,3);

    Vector K = {0,0};
    double kMag;
    
    if(fabs(rMag)> 1e-10)
    {

        if (disthat <= 0.5)
        {
            kMag = C * (- 12 * disthat /h + 18 * pow(disthat,2)/h );
        }
        else if (disthat <=1)
        {
            kMag = C * -6 * pow(1 -disthat,2)/h;
        }
        else
        {
            kMag = 0;
        }
        K.x = -(vec2.x-vec1.x)/rMag* kMag;
        K.y = -(vec2.y-vec1.y)/rMag* kMag;
    }
    return K;
}
    


