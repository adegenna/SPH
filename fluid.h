/**
 * \file
 *
 * \brief Definition of fluid class for packaging together particles, boundary 
 * particles, and their properties.
 */
#ifndef FLUID_H_
#define FLUID_H_

#include <vector>
#include <boost/shared_ptr.hpp>
#include "properties.h"

class Kernel;
class Particle;

/// Holds particles and boundary praticles
class Fluid {
  public:
    typedef std::vector< boost::shared_ptr<Particle> > ParticleArray;

    /// ctor
    Fluid(Kernel& kernel,       //!< Type of kernel to use (GaussianKernel or SplineKernel)
        size_t nparticles,      //!< Number of particles in the fluid (constant)
        size_t nboundaries,     //!< Number of boundary particles in the fluid (constant)
        double smoothinglength  //!< The smoothing length
        );
    /// get the array of particles
    ParticleArray getParticles() const;
    /// add particle to the particle array
    void addParticle(int tag, const Properties& prop);
    /// get the array of boundary particles
    ParticleArray getBoundaries() const;
    /// add particle to the boundary
    void addBoundary(int tag, const Properties& prop);
    /// find neighbors for all particles in the fluid
    void findNeighbors();
    /// reset particles to have no neighbors
    void resetNeighbors();
    /// get the kernel
    Kernel& getKernel();
    /// get the number of particles
    size_t getNParticles() const;
    /// get the number of boundary particles
    size_t getNBoundaries() const;
    /// update all particles with input particle array
    void resetParticles(const ParticleArray& newparticles);
    
  private:
    Kernel& kernel_;
    size_t nparticles_;  // number of particles
    size_t nboundaries_; // number of boundaries
    double smoothinglength_;
    ParticleArray particles_;
    ParticleArray boundaries_; // Boundary particles
};
#endif // FLUID_H
