#include "particle.h"

Particle::Particle(int tag, int N, int NB, Properties& properties) {
  tag_ = tag;
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

int Particle::get(const std::string& ID, Properties& props) {
  if (ID == "OLD") {
    props.x = propsold_.x;
    props.y = propsold_.y;
    props.u = propsold_.u;
    props.v = propsold_.v;
    props.density = propsold_.density;
    props.mass = propsold_.mass;
    props.pressure = propsold_.pressure;
    props.visc = propsold_.visc;
  }
  else if (ID == "NEW") {
    props.x = propsnew_.x;
    props.y = propsnew_.y;
    props.u = propsnew_.u;
    props.v = propsnew_.v;
    props.density = propsnew_.density;
    props.mass = propsnew_.mass;
    props.pressure = propsnew_.pressure;
    props.visc = propsnew_.visc;
  }
  else {
    return 1; // Error
  }
  return 0;
}

int Particle::set(const std::string& ID, Properties& props) {
  if (ID == "OLD") {
    propsold_.x = props.x;
    propsold_.y = props.y;
    propsold_.u = props.u;
    propsold_.v = props.v;
    propsold_.density = props.density;
    propsold_.mass = props.mass;
    propsold_.pressure = props.pressure;
    propsold_.visc = props.visc;
  }
  else if (ID == "NEW") {
    propsnew_.x = props.x;
    propsnew_.y = props.y;
    propsnew_.u = props.u;
    propsnew_.v = props.v;
    propsnew_.density = props.density;
    propsnew_.mass = props.mass;
    propsnew_.pressure = props.pressure;
    propsnew_.visc = props.visc;
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
