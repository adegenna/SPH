#ifndef FLUID_H_
#define FLUID_H_

#include <stdlib.h>
#include "particle.h"
#include "properties.h"

class Fluid {
  public:
    Fluid(Kernel *kernel, int nparticles, double smoothingLength);
    ~Fluid();
    Particle* getParticles();
    void addParticle(Properties properties);
    void findNeighbors();
    void resetNeighbors();
    Kernel getKernel();
    
  private:
    Particle **particles_;
    const Kernel *kernel_;
    const int nparticles_;  // number of particles
    double smoothingLength_;

#endif // FLUID_H
