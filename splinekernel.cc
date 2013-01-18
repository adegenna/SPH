#include "splinekernel.h"
#include <cmath>

  SplineKernel::SplineKernel(double smoothinglength)
: h_(smoothinglength)
{}

SplineKernel::~SplineKernel()
{}

double SplineKernel::W(double r)
{
  const double q = r / h_;
  const double sigma = 10 / (7 * M_PI);

  if (q <= 0 && q < 1)
  {
    return sigma * (1 - 1.5 * pow(q, 2) + 0.75 * pow(q, 4));
  }
  else if (q <= 1 && q < 2)
  {
    return sigma * 0.25 * pow(2 - q, 3);
  }
  else
  {
    return 0;
  }
}

Kvector SplineKernel::gradW(Kvector vec1, Kvector vec2)
{
  const double r = hypot(vec2.x - vec1.x, vec2.y - vec1.y);
  const double q = r / h_;
  const double sigma = 10 / (7 * M_PI);
  double grad = 3 * sigma / (4 * pow(h_, 3));

  if (q <= 0 && q < 1)
  {
    grad *= 3 * r - 4 * h_;
  }
  else if (q <= 1 && q < 2)
  {
    grad *= pow(r - 2 * h_, 2);
  }
  else
  {
    grad = 0;
  }

  Kvector K = {
    grad * (vec2.x - vec1.x),
    grad * (vec2.y - vec1.y)
  };
  return K;
}

double SplineKernel::lapW(double r)
{
  const double q = r / h_;
  const double lap = 15 / (14 * pow(h_, 3) * M_PI);

  if (q <= 0 && q < 1)
  {
    return lap * (9 * r - 8 * h_);
  }
  else if (q <= 1 && q < 2 && r > 1e-10) // Warning: Division by r
  {
    return lap * (8 * h_ - 4 * h_*h_ / r - 3 * r);
  }
  else
  {
    return 0;
  }
}

