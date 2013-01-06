#ifndef FLUID_H_
#define FLUID_H_

#include <vector>
#include <boost/shared_ptr.hpp>

#include "properties.h"

class Kernel;
class Particle;


class Fluid {
  public:
    typedef std::vector< boost::shared_ptr<Particle> > ParticleArray;

    Fluid(Kernel& kernel, size_t nparticles, size_t nboundaries, double smoothinglength);
    ParticleArray getParticles() const;
    void addParticle(int tag, const Properties& prop);
    ParticleArray getBoundaries() const;
    void addBoundary(int tag, const Properties& prop);
    void findNeighbors();
    void resetNeighbors();
    Kernel& getKernel();
    size_t getNParticles() const;
    size_t getNBoundaries() const;
    void resetParticles(const ParticleArray& newparticles); // Global particle update
    
  private:
    Kernel& kernel_;
    size_t nparticles_;  // number of particles
    size_t nboundaries_; // number of boundaries
    double smoothinglength_;
    ParticleArray particles_;
    ParticleArray boundaries_; // Boundary particles
};
#endif // FLUID_H
