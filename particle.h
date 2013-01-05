#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "particle.h"
#include "properties.h"

struct Properties;
class Particle {
 public:
  Particle(int tag, int N, int NB, Properties& properties);
  ~Particle();

  // Return/Update particle properties
  // ID is either "OLD" or "NEW"
  int get(const std::string& ID, Properties& props); 
  int set(const std::string& ID, Properties props);
  
  void addNeighbor(Particle* neighbor);         // Add a neighbor tag
  void addBoundaryNeighbor(Particle* neighbor); // Add boundary tag
  int numberOfNeighbors();                      // Return neighbors_
  int numberOfBoundaryNeighbors();              // Return boundaryneighbors_
  void getNeighbors(int neighbors[]);           // Get neighborarray_
  void getBoundaryNeighbors(int neighbors[]);   // Get boundaryneighborarray_
  int getTag();                                 // Return tag_
  void deleteNeighbors();                       // Re-initialize neighborarray_
  
 private:
  Properties propsold_;           // old properties
  Properties propsnew_;           // new properties
  int tag_;                       // Particle identifier
  int neighbors_;                 // Number of neighbors
  int boundaryneighbors_;         // Number of boundary neighbors
  int* neighborarray_;            // Array of neighbor tags
  int* boundaryneighborarray_;    // Array of boundary neighbor tags
  int N_;                         // Global Number of Particles
  int NB_;                        // Global Number of Boundary Particles
  void initializeNeighborArray(); // Initialize neighbor array
};

#endif  // PARTICLE_H
