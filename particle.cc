#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "particle.h"
#include "properties.h"
#include <string>

Particle::Particle(int tag, int N, Properties& properties) {
  tag_ = tag;
  x_ = new double[2]; v_ = new double[2];
  xnew_ = new double[2]; vnew_ = new double[2];
  set("OLD", properties);
  neighbors_ = 0;
  N_ = N;
  neighborarray_ = new int[N_];
  initializeNeighborArray();
}

Particle::~Particle() {
  delete [] x_; delete [] xnew_;
  delete [] v_; delete [] vnew_;
  delete [] neighborarray_;
}

void Particle::addNeighbor(Particle* neighbor) {
  neighbors_ += 1;
  int neighbortag = neighbor->getTag();
  neighborarray_[neighbors_-1] = neighbortag;
}

int Particle::numberOfNeighbors() {
  return neighbors_;
}

void Particle::getNeighbors(int neighbors[]) {
  for (int i = 0; i < N_; i++) {
    neighbors[i] = neighborarray_[i];
  }
}

int Particle::getTag() {
  return tag_;
}

int Particle::get(const std::string& ID, Properties& Prop) {
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

int Particle::set(const std::string& ID, Properties& Prop) {
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

void Particle::initializeNeighborArray() {
  for (int i = 0; i < N_; i++) {
    neighborarray_[i] = -1;
  }
}

void Particle::deleteNeighbors() {
  neighbors_ = 0;
  initializeNeighborArray();
}
