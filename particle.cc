#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "particle.h"
#include "properties.h"
#include <string>

Particle::Particle(int tag, int N, int NB, Properties& properties) {
  tag_ = tag;
  x_ = new double[2]; v_ = new double[2];
  xnew_ = new double[2]; vnew_ = new double[2];
  set("OLD", properties);
  neighbors_ = 0;
  boundaryneighbors_ = 0;
  N_ = N;
  NB_ = NB;
  neighborarray_ = new int[N_];
  boundaryneighborarray_ = new int[NB_];
  
  initializeNeighborArray();
}

Particle::~Particle() {
  delete [] x_; delete [] xnew_;
  delete [] v_; delete [] vnew_;
  delete [] neighborarray_;
  delete [] boundaryneighborarray_;
}

void Particle::addNeighbor(Particle* neighbor) {
  // do we want this to take int tag instead of Particle*?
  neighbors_ += 1;
  int neighbortag = neighbor->getTag();
  neighborarray_[neighbors_-1] = neighbortag;
}

void Particle::addBoundaryNeighbor(Particle* neighbor) {
  boundaryneighbors_ += 1;
  int neighbortag = neighbor->getTag();
  boundaryneighborarray_[boundaryneighbors_-1] = neighbortag;
}

int Particle::numberOfNeighbors() {
  return neighbors_;
}

int Particle::numberOfBoundaryNeighbors() {
  return boundaryneighbors_;
}

void Particle::getNeighbors(int neighbors[]) {
  for (int i = 0; i < N_; i++) {
    neighbors[i] = neighborarray_[i];
  }
}

void Particle::getBoundaryNeighbors(int neighbors[]) {
  for (int i = 0; i < NB_; i++) {
    neighbors[i] = boundaryneighborarray_[i];
  }
}

int Particle::getTag() {
  return tag_;
}

// do we also want the ability to get individual properties directly as well?
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
  for (int i = 0; i < NB_; i++) {
    boundaryneighborarray_[i] = -1;
  }
}

void Particle::deleteNeighbors() {
  neighbors_ = 0;
  boundaryneighbors_ = 0;
  initializeNeighborArray();
}
