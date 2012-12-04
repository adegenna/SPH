#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "particle.h"

using namespace std;

int main() {
  double* r1 = new double[2];
  double* v1 = new double[2];
  double* r2 = new double[2];
  double* v2 = new double[2];

  r1[0] = 10; r1[1] = 20;
  r2[0] = 30; r2[1] = 40;

  double mass = 1.0;
  double visc = 2.0;

  Particle* p1;
  p1 = new Particle(r1, v1, mass, visc);
  Particle* p2 = new Particle(r2, v2, mass, visc);

  double* location = new double;
  location = p2->GetLocation();
  double dist = p1->Distance(location);            // Get distance to p2
  printf("Distance = %e \n", dist);

  delete r1; delete r2; delete v1; delete v2; delete location;

  return 0;
}
