#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <string>
#include <vector>
#include "properties.h"


class Particle {
 public:
  typedef int Tag;
  typedef std::vector<int> TagArray;

  Particle(Tag tag, size_t N, size_t NB, const Properties& properties);

  // Return/Update particle properties
  Properties getOldProperties() const;
  Properties getNewProperties() const;
  void setOldProperties(const Properties& props);
  void setNewProperties(const Properties& props);
  
  void addNeighbor(const Particle& neighbor);         // Add a neighbor tag
  void addBoundaryNeighbor(const Particle& neighbor); // Add boundary tag
  size_t numberOfNeighbors() const;                   // Return neighbors_
  size_t numberOfBoundaryNeighbors() const;           // Return boundaryneighbors_
  TagArray getNeighbors() const;                      // Get neighborarray_
  TagArray getBoundaryNeighbors() const;              // Get boundaryneighborarray_
  Tag getTag() const;                                 // Return tag_
  void deleteNeighbors();                             // Re-initialize neighborarray_
  
 private:
  Tag tag_;                        // Particle identifier
  size_t neighbors_;               // Number of neighbors
  size_t boundaryneighbors_;       // Number of boundary neighbors
  TagArray neighborarray_;         // Array of neighbor tags
  TagArray boundaryneighborarray_; // Array of boundary neighbor tags
  Properties propsold_;            // old properties
  Properties propsnew_;            // new properties

  void initializeNeighborArray();  // Initialize neighbor array
};

#endif  // PARTICLE_H
