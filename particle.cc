#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "particle.h"
#include "properties.h"
#include <string>

Particle::Particle(int tag, Properties& properties) {
  tag_ = tag;
  x_ = new double[2]; v_ = new double[2];
  xnew_ = new double[2]; vnew_ = new double[2];
  Set("OLD", properties);
  neighbors_ = 0;
  neighbor_pointer_ = new Particle*;
}

Particle::~Particle() {
  delete [] x_; delete [] xnew_;
  delete [] v_; delete [] vnew_;
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

int Particle::Set(const std::string& ID, Properties& Prop) {
  if (ID == "OLD") {
    x_[0] = Prop.x; x_[1] = Prop.y;
    v_[0] = Prop.u; v_[1] = Prop.v;
    mass_ = Prop.mass;
    density_ = Prop.density;
    pressure_ = Prop.pressure;
    visc_ = Prop.visc;
  }
  else if (ID == "NEW") {
    xnew_[0] = Prop.x; xnew_[1] = Prop.y;
    vnew_[0] = Prop.u; vnew_[1] = Prop.v;
    mass_ = Prop.mass;
    densitynew_ = Prop.density;
    pressure_ = Prop.pressure;
    visc_ = Prop.visc;
  }
  else {
    return 1; // Error
  }
  return 0;
}
