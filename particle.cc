#include "particle.h"

#include <algorithm>


Particle::Particle(int tag, size_t N, size_t NB, const Properties& properties) :
tag_(tag),
neighbors_(0),
boundaryneighbors_(0),
neighborarray_(N, -1),
boundaryneighborarray_(NB, -1),
propsold_(properties)
{}

void Particle::addNeighbor(const Particle& neighbor)
{
    neighborarray_[neighbors_++] = neighbor.getTag();
}

void Particle::addBoundaryNeighbor(const Particle& neighbor)
{
    boundaryneighborarray_[boundaryneighbors_++] = neighbor.getTag();
}

size_t Particle::numberOfNeighbors() const
{
    return neighbors_;
}

size_t Particle::numberOfBoundaryNeighbors() const
{
    return boundaryneighbors_;
}

Particle::TagArray Particle::getNeighbors() const
{
    return neighborarray_;
}

Particle::TagArray Particle::getBoundaryNeighbors() const
{
    return boundaryneighborarray_;
}

Particle::Tag Particle::getTag() const
{
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

void Particle::initializeNeighborArray()
{
    std::fill(neighborarray_.begin(), neighborarray_.end(), -1);
    std::fill(boundaryneighborarray_.begin(), boundaryneighborarray_.end(), -1);
}

void Particle::deleteNeighbors() {
  neighbors_ = 0;
  boundaryneighbors_ = 0;
  initializeNeighborArray();
}
