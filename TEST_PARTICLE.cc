#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "particle.h"
#include "properties.h"
#include "fluid.h"

using namespace std;

int main() {
  const int N = 3; // Number of particles

  double r1[2]; // Position of P1
  double v1[2]; // Velocity of P1
  double r2[2]; // Position of P2
  double v2[2]; // Velocity of P2
  double r3[2]; // Position of P3
  double v3[2]; // Velocity of P3

  double* x[N]; // Pointer to the pointers r_i
  double* v[N]; // Pointer to the pointers v_i

  // **************** Set values ******************
  r1[0] = -7; r1[1] = 20; v1[0] = 5; v1[1] = 6;
  r2[0] = 30; r2[1] = 40; v2[0] = 7; v2[1] = 8;
  r3[0] = 50; r3[1] = 60; v3[0] = 9; v3[1] = 10;

  x[0] = r1; x[1] = r2; x[2] = r3;
  v[0] = v1; v[1] = v2; v[2] = v3;

  double mass = 1.0;
  double visc = 2.0;
  double density = 3.0;
  double pressure = 4.0;
  // **********************************************
  
  // ************** Initialization ****************
    Fluid::ParticleArray particles(N); // Pointer to particle pointers
  Properties initial;
  for (int i = 0; i < N; i++) {
    initial.x = x[i][0]; initial.y = x[i][1];
    initial.u = v[i][0]; initial.v = v[i][1];
    initial.mass = mass; initial.visc = visc; initial.pressure = pressure;
    initial.density = density;
    particles[i].reset(new Particle(i+1, N, 0, initial));
  }
  // *********************************************
  
  // ********* Example Method Usages *************
  Properties p2props = particles[1]->getOldProperties();
  double location2[2] = {p2props.x, p2props.y};
  printf("\nP2 OLD location = %lf %lf\n", location2[0], location2[1]);
  
  // Add neighbors
  particles[0]->addNeighbor(*particles[1]);
  particles[0]->addNeighbor(*particles[2]);
  int numberneighbors = particles[0]->numberOfNeighbors();
  printf("\nP1 Number of neighbors = %d\n",numberneighbors);
  Particle::TagArray neighbors = particles[0]->getNeighbors();
  printf("P1 neighbors are particles %d and %d and %d\n", neighbors[0], neighbors[1], neighbors[2]);

  // Use properties struct for get/set
  Properties properties = particles[0]->getOldProperties();
  printf("\nP1 OLD: x = %lf y = %lf\n", properties.x, properties.y);
  properties.x = -17.0; properties.y = 27.0;
  particles[0]->setNewProperties(properties);
  Properties newprop1 = particles[0]->getNewProperties();
  printf("\nP1 NEW: x = %lf y = %lf\n", newprop1.x, newprop1.y);
  
  // Delete all neighbors
  particles[0]->deleteNeighbors();
  neighbors = particles[0]->getNeighbors();
  numberneighbors = particles[0]->numberOfNeighbors();
  printf("\nP1 now has %d neighbors and the neighbor array is empty: %d %d %d\n\n", numberneighbors, neighbors[0], neighbors[1], neighbors[2]);

  // *********************************************

  return 0;
}
