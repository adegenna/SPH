#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "particle.h"
#include "properties.h"
#include <string>

Particle::Particle(int tag, Properties& properties) {
  tag_ = tag;
  x_ = new double[2]; x_[0] = properties.x; x_[1] = properties.y;
  v_ = new double[2]; v_[0] = properties.u; v_[1] = properties.v;
  mass_ = properties.mass;
  visc_ = properties.visc;
  density_ = properties.density;
  pressure_ = properties.pressure;
  neighbors_ = 0;
  neighbor_pointer_ = new Particle*;
}

Particle::~Particle() {
  delete [] x_;
  delete [] v_;
}
//perhaps change so we can input 2 particles and return distance
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

int Particle::Get(const std::string& ID, Properties& Prop) {
  if (ID == "OLD") {
    Prop.x = x_[0]; Prop.y = x_[1];
    Prop.u = v_[0]; Prop.v = v_[1];
    Prop.mass = mass_;
    Prop.density = density_;
    Prop.pressure = pressure_;
    Prop.visc = visc_;
  }
  else if (ID == "NEW") {
    Prop.x = xnew_[0]; Prop.y = xnew_[1];
    Prop.u = vnew_[0]; Prop.v = vnew_[1];
    Prop.mass = mass_;
    Prop.density = densitynew_;
    Prop.pressure = pressure_;
    Prop.visc = visc_;
  }
  else {
    return 1; // Error
  }
  return 0;
}
