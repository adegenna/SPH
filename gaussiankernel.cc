#include "gaussiankernel.h"
#include <cmath>

  GaussianKernel::GaussianKernel(double smoothinglength)
: h_(smoothinglength)
{}

GaussianKernel::~GaussianKernel()
{}

double GaussianKernel::W(double r)
{
  const double q = r / h_;
  const double sigma = 1 / M_PI;
  return sigma * exp(-q*q) / (h_*h_);
}

Kvector GaussianKernel::gradW(Kvector vec1, Kvector vec2)
{
  const double r = hypot(vec2.x - vec1.x, vec2.y - vec1.y);
  const double grad = -2 * W(r) / (h_*h_);
  Kvector K = {
    grad * (vec2.x - vec1.x),
    grad * (vec2.y - vec1.y)
  };
  return K;
}

double GaussianKernel::lapW(double r)
{
  return 4 * (r*r - h_*h_) * W(r) / pow(h_, 4);
}


