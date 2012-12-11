#include "Fluid.h"

Fluid::Fluid(Kernel* kernel, int nparticles, double smoothingLength){
  nparticles_ = nparticles;
  smoothingLength_ = smoothingLength;
  Kernel_ = kernel;
  
  // this could change, but currently we are just using a simple
  // array of particles
  particles_ = new Particle[nparticles_];

}

Fluid::~Fluid(){
  delete [] particles_;
}

void Fluid::addParticle(int tag, double *x, double *v, double mass, double visc){
  // add warning for tag >= nparticles_
  // also: what is this about a properties struct? really necessary??
  particles_[tag] = new Particle(tag, x, v, mass, visc);
}

void Fluid::findNeighbors(){
  // need to write this
}

void Fluid::resetNeighbors(){
  for(int i=0; i<nparticles_; ++i){
    particles_[i].noNeighbors(); // <-- this does not exist
  }
}

Kernel getKernel(){
  return kernel_;
}
