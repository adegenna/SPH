/**
 * \file
 *
 * \brief Definition of the particle class
 */
#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <string>
#include <vector>
#include "properties.h"

/// Properties and functions for individual particles
class Particle {
 public:
  typedef int Tag;
  typedef std::vector<int> TagArray;

  /// ctor
  Particle(Tag tag, size_t N, size_t NB, const Properties& properties);

  /// return old version of particle properties
  Properties getOldProperties() const;
  /// return new version of particle properties
  Properties getNewProperties() const;
  /// set old version of particle properties
  void setOldProperties(const Properties& props);
  /// set new version of particle properties
  void setNewProperties(const Properties& props);
  /// add a neighbor tag
  void addNeighbor(const Particle& neighbor);
  /// add a boundary neighbor tag
  void addBoundaryNeighbor(const Particle& neighbor);
  /// return the number of neighbors (neighbors_)
  size_t numberOfNeighbors() const;
  /// return the number of boundary neighbors (boundaryneighbors_)
  size_t numberOfBoundaryNeighbors() const;
  /// return the array of neighbor tags (neighborarray_)
  TagArray getNeighbors() const;
  /// return the array of boundary neighbor tags (boundaryneighborarray_)
  TagArray getBoundaryNeighbors() const;
  /// return the particle's tag (tag_)
  Tag getTag() const;
  /// re-initiliaze neighborarray_ and boundaryneighborarray_
  void deleteNeighbors();
  
 private:
  Tag tag_;                        // Particle identifier
  size_t neighbors_;               // Number of neighbors
  size_t boundaryneighbors_;       // Number of boundary neighbors
  TagArray neighborarray_;         // Array of neighbor tags
  TagArray boundaryneighborarray_; // Array of boundary neighbor tags
  Properties propsold_;            // Old properties
  Properties propsnew_;            // New properties

  void initializeNeighborArray();  // Initialize neighbor array
};

#endif  // PARTICLE_H
