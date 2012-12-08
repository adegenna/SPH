#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <string>

struct Properties;
class Particle {
 public:
  Particle(int tag, Properties& properties);
  ~Particle();
  double Distance(double* location);           // Return distance to particle

  // Return/Update particle properties
  // ID is either "OLD" or "NEW"
  int Get(const std::string& ID, Properties& properties); 
  int Set(const std::string& ID, Properties& properties);
  
  void AddNeighbor(Particle* neighbor);        // Add a neighbor
  int Number_of_Neighbors();                   // Return neighbors_
  void GetNeighbors(Particle** neighbor);      // Get neighbor_pointer_
  int GetTag();                                // Return tag_
  
 private:
  double* x_;                    // Location Pointer
  double* v_;                    // Velocity Pointer
  double* xnew_;
  double* vnew_;
  double mass_;                  // Particle Mass
  double visc_;                  // Particle Viscosity
  double density_;               // Particle Density
  double densitynew_;            // Particle New Density
  double pressure_;              // Particle Pressure
  int tag_;                      // Particle identifier
  int neighbors_;                // Number of neighbors
  Particle** neighbor_pointer_;  // Pointer to neighbor chain
};

#endif  // PARTICLE_H
