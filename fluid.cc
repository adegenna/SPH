#include "fluid.h"

#include <cmath>
#include "particle.h"


Fluid::Fluid(Kernel& kernel, size_t nparticles, size_t nboundaries, double smoothinglength) :
kernel_(kernel),
nparticles_(nparticles),
nboundaries_(nboundaries),
smoothinglength_(smoothinglength),
particles_(nparticles),
boundaries_(nboundaries)
{}

//should this just be addParticle(Properties props) ?
void Fluid::addParticle(int tag, const Properties& prop)
{
    particles_[tag].reset(new Particle(tag, nparticles_, nboundaries_,prop));
}

void Fluid::addBoundary(int tag, const Properties& prop)
{
    boundaries_[tag].reset(new Particle(tag, nparticles_, nboundaries_, prop));
}

void Fluid::findNeighbors(){
  for(int i=0; i<nparticles_; ++i){
    const Properties propi = particles_[i]->getOldProperties();
    for(int j=i+1; j<nparticles_; ++j){
      const Properties propj = particles_[j]->getOldProperties();
      float dist = sqrt(pow(propi.x-propj.x,2)+pow(propi.y-propj.y,2));
        
        //should this cutoff distance be larger?
      if(dist < 5.*smoothinglength_){  //this is somewhat arbitrary at the moment
        particles_[i]->addNeighbor(*particles_[j]);
        particles_[j]->addNeighbor(*particles_[i]);
      }
    }
  }
  for(int i=0; i<nboundaries_; ++i) {
    const Properties propi = boundaries_[i]->getOldProperties();
    for(int j=0; j<nparticles_; ++j){
      const Properties propj = particles_[j]->getOldProperties();
      float dist = sqrt(pow(propi.x-propj.x,2)+pow(propi.y-propj.y,2));

//      int BN = particles_[j]->numberOfBoundaryNeighbors();

        //should this cutoff distance be larger?
      if(dist < 5.*smoothinglength_){
        particles_[j]->addBoundaryNeighbor(*boundaries_[i]);
      }
    }
  }
}

void Fluid::resetNeighbors(){
  for(int i=0; i<nparticles_; ++i){
    particles_[i]->deleteNeighbors();
  }
}

Kernel& Fluid::getKernel()
{
  return kernel_;
}

size_t Fluid::getNParticles() const
{
  return nparticles_;
}

size_t Fluid::getNBoundaries() const
{
  return nboundaries_;
}

Fluid::ParticleArray Fluid::getParticles() const
{
    return particles_;
}

Fluid::ParticleArray Fluid::getBoundaries() const
{
    return boundaries_;
}

void Fluid::resetParticles(const ParticleArray& newparticles)
{
    particles_ = newparticles;
}
