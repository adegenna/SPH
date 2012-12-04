#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "particle.h"

Particle::Particle(double* r, double* v, double mass, double visc) {
  r_ = r;
  v_ = v;
  mass_ = mass;
  visc_ = visc;

  N_ = sizeof(r_);
}

Particle::~Particle() {
  delete [] r_;
  delete [] v_;
}

double Particle::Distance(double* location) {
  double norm;
  for (int i = 0; i < N_; i++) {
    norm += pow((r_[i] - location[i]), 2);
  }
  norm = sqrt(norm);
  return norm;
}

double* Particle::GetLocation() {
  double* location = new double[N_];
  for (int i = 0; i < N_; i++) {
    location[i] = r_[i];
  }
  return location;
}

double* Particle::GetVelocity() {
  double* velocity = new double[N_];
  for (int i = 0; i < N_; i++) {
    velocity[i] = v_[i];
  }
  return velocity;
}

