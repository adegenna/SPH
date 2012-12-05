#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "particle.h"

using namespace std;

int main() {
  double* r1 = new double[2]; // Position of P1
  double* v1 = new double[2]; // Velocity of P1
  double* r2 = new double[2]; // Position of P2
  double* v2 = new double[2]; // Velocity of P2

  double** x = new double*[2]; // Pointer to the pointers r1 and r2
  double** v = new double*[2]; // Pointer to the pointers v1 and v2

  // **************** Set values ******************
  r1[0] = 10; r1[1] = 20; v1[0] = 5; v1[1] = 6;
  r2[0] = 30; r2[1] = 40; v2[0] = 7; v2[1] = 8;

  x[0] = r1; x[1] = r2;
  v[0] = v1; v[1] = v2;

  double mass = 1.0;
  double visc = 2.0;
  // **********************************************
  
  // ************** Initialization ****************
  int N = 2; // Number of particles
  Particle** particles = new Particle*[N]; // Pointer to particle pointers
  for (int i = 0; i < N; i++) {
    particles[i] = new Particle(i+1, x[i], v[i], mass, visc);
  }
  // *********************************************
  
  // ********* Example Method Usages *************
  double* location1 = new double[2];
  double* location2 = new double[2];
  particles[0]->GetLocation(location1);
  particles[1]->GetLocation(location2);
  
  printf("P1 Location = %e %e \n", location1[0], location1[1]);
  printf("P2 Location = %e %e \n", location2[0], location2[1]);

  double dist = particles[0]->Distance(location2);  // Get distance to p2
  printf("Distance = %e \n", dist);

  double* velocity1 = new double[2];
  double* velocity2 = new double[2];
  particles[0]->GetVelocity(velocity1);
  particles[1]->GetVelocity(velocity2);
  printf("P1 Velocity = %e %e \n", velocity1[0], velocity1[1]);
  printf("P2 Velocity = %e %e \n", velocity2[0], velocity2[1]);

  delete r1; delete r2; delete v1; delete v2;
  delete location1; delete location2; delete velocity1; delete velocity2;
  delete particles;
  // *********************************************

  return 0;
}
