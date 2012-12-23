#ifndef FLUID_H_
#define FLUID_H_

#include <stdlib.h>
#include "kvector.h"
#include "kernel.h"
#include "properties.h"
#include "particle.h"
#include "math.h"

class Fluid {
  public:
    Fluid(Kernel *kernel, int nparticles, double smoothinglength);
    ~Fluid();
    void getParticles(Particle** particles);
    void addParticle(int tag,Properties prop);
    void findNeighbors();
    void resetNeighbors();
    Kernel* getKernel();
    int getNParticles();
    void resetParticles(Particle** newparticles); // Global particle update
    
  private:
    Particle **particles_;
    Kernel *kernel_;
    int nparticles_;  // number of particles
    double smoothinglength_;
};
#endif // FLUID_H
