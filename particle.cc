#include "particle.h"

Particle::Particle(int tag, int N, int NB, Properties& properties) {
  tag_ = tag;
  setOldProperties(properties);
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
  for (int i = 0; i < neighbors_; ++i) {
    neighbors[i] = neighborarray_[i];
  }
}

void Particle::getBoundaryNeighbors(int neighbors[]) {
  for (int i = 0; i < boundaryneighbors_; ++i) {
    neighbors[i] = boundaryneighborarray_[i];
  }
}

int Particle::getTag() {
  return tag_;
}

Properties Particle::getOldProperties() const
{
    return propsold_;
}

Properties Particle::getNewProperties() const
{
    return propsnew_;
}

void Particle::setOldProperties(const Properties& props)
{
    propsold_ = props;
}

void Particle::setNewProperties(const Properties& props)
{
    propsnew_ = props;
}

void Particle::initializeNeighborArray() {
  for (int i = 0; i < N_; ++i) {
    neighborarray_[i] = -1;
  }
  for (int i = 0; i < NB_; ++i) {
    boundaryneighborarray_[i] = -1;
  }
}

void Particle::deleteNeighbors() {
  neighbors_ = 0;
  boundaryneighbors_ = 0;
  initializeNeighborArray();
}
