#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "particle.h"
#include "properties.h"

using namespace std;

int main() {
  int N = 3; // Number of particles

  double* r1 = new double[2]; // Position of P1
  double* v1 = new double[2]; // Velocity of P1
  double* r2 = new double[2]; // Position of P2
  double* v2 = new double[2]; // Velocity of P2
  double* r3 = new double[2];
  double* v3 = new double[2];

  double** x = new double*[N]; // Pointer to the pointers r_i
  double** v = new double*[N]; // Pointer to the pointers v_i

  // **************** Set values ******************
  r1[0] = 10; r1[1] = 20; v1[0] = 5; v1[1] = 6;
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
  Particle** particles = new Particle*[N]; // Pointer to particle pointers
  Properties initial;
  for (int i = 0; i < N; i++) {
    initial.x = x[i][0]; initial.y = x[i][1];
    initial.u = v[i][0]; initial.v = v[i][1];
    initial.mass = mass; initial.visc = visc; initial.pressure = pressure;
    initial.density = density;
    particles[i] = new Particle(i+1, initial);
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
  
  // Add neighbors
  particles[0]->AddNeighbor(particles[1]);
  particles[0]->AddNeighbor(particles[2]);
  int numberneighbors = particles[0]->Number_of_Neighbors();
  printf("\nP1 Number of neighbors = %d\n",numberneighbors);
  Particle** neighbors = new Particle*;
  particles[0]->GetNeighbors(neighbors);
  printf("P1 neighbors are particles %d and %d\n", neighbors[0]->GetTag(), neighbors[1]->GetTag());


  // Use properties struct for get/set
  Properties properties;
  particles[0]->Get("OLD", properties);
  printf("\nx = %lf y = %lf\n", properties.x, properties.y); 

  delete r1; delete r2; delete v1; delete v2;
  delete location1; delete location2; delete velocity1; delete velocity2;
  delete particles; delete neighbors;
  // *********************************************

  return 0;
}
