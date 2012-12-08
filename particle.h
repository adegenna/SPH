#ifndef PARTICLE_H_
#define PARTICLE_H_

class Particle {
 public:
  Particle(int tag, double* x, double* v, double mass, double visc);
  ~Particle();
  double Distance(double* location);           // Return distance to particle
  void GetLocation(double* location);          // Return r_
  void GetVelocity(double* velocity);          // Return v_
  void SetLocation(double* location);          // Update r_
  void SetVelocity(double* velocity);          // Update v_
    void Get(string blah,Properties Prop);
  void AddNeighbor(Particle* neighbor);        // Add a neighbor
  int Number_of_Neighbors();                // Return neighbors_
  void GetNeighbors(Particle** neighbor);      // Get neighbor_pointer_
  int GetTag();                                // Return tag_
  
 private:
  double* x_;                    // Location Pointer
  double* v_;                    // Velocity Pointer
  double mass_;                  // Particle Mass
  double visc_;                  // Particle Viscosity
  int tag_;                      // Particle identifier
  int neighbors_;                // Number of neighbors
  Particle** neighbor_pointer_;  // Pointer to neighbor chain
};

#endif  // PARTICLE_H
