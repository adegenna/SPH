#ifndef PARTICLE_H_
#define PARTICLE_H_

class Particle {
 public:
  Particle(double* r, double* v, double mass, double visc);
  ~Particle();
  double Distance(double* location);   // Return distance to particle
  double* GetLocation();               // Return [r_]
  double* GetVelocity();               // Return [v_]
 private:
  double* r_;     // Location Pointer
  double* v_;     // Velocity Pointer
  double mass_;   // Particle Mass
  double visc_;   // Particle Viscosity
  
  int N_;       // Dimension of Position Vector (Calculated)
};

#endif  // PARTICLE_H
