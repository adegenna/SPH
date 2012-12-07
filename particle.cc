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
  neighbors_ = 0;
  neighbor_pointer_ = new Particle*;
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

void Particle::AddNeighbor(Particle* neighbor) {
  neighbors_ += 1;
  neighbor_pointer_[neighbors_-1] = neighbor;
}

int Particle::Number_of_Neighbors() {
  return neighbors_;
}

void Particle::GetNeighbors(Particle** neighbor) {
  for (int i = 0; i < neighbors_; i++) {
    neighbor[i] = neighbor_pointer_[i];
  }
}

int Particle::GetTag() {
  return tag_;
}
