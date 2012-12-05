#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "particle.h"

Particle::Particle(int tag, double* x, double* v, double mass, double visc) {
  tag_ = tag;
  x_ = new double[2]; SetLocation(x);
  v_ = new double[2]; SetVelocity(v);
  mass_ = mass;
  visc_ = visc;
}

Particle::~Particle() {
  delete [] x_;
  delete [] v_;
}

double Particle::Distance(double* location) {
  double norm;
  for (int i = 0; i < 2; i++) {
    norm += pow((x_[i] - location[i]), 2);
  }
  norm = sqrt(norm);
  return norm;
}

void Particle::GetLocation(double* location) {
  for (int i = 0; i < 2; i++) {
    location[i] = x_[i];
  }
}

void Particle::GetVelocity(double* velocity) {
  for (int i = 0; i < 2; i++) {
    velocity[i] = v_[i];
  }
}

void Particle::SetLocation(double* location) {
  for (int i = 0; i < 2; i++) {
    x_[i] = location[i];
  }
}

void Particle::SetVelocity(double* velocity) {
  for (int i = 0; i < 2; i++) {
    v_[i] = velocity[i];
  }
}
