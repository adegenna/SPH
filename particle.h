#ifndef PARTICLE_H_
#define PARTICLE_H_

class Particle {
 public:
  Particle(int tag, double* x, double* v, double mass, double visc);
  ~Particle();
  double Distance(double* location);    // Return distance to particle
  void GetLocation(double* location);   // Return r_
  void GetVelocity(double* velocity);   // Return v_
  void SetLocation(double* location);   // Update r_
  void SetVelocity(double* velocity);   // Update v_
 private:
  double* x_;     // Location Pointer
  double* v_;     // Velocity Pointer
  double mass_;   // Particle Mass
  double visc_;   // Particle Viscosity
  int tag_;       // Particle identifier
};

#endif  // PARTICLE_H
