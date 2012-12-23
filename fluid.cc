#include "fluid.h"
#include <iostream>

Fluid::Fluid(Kernel* kernel, int nparticles, double smoothinglength){
  nparticles_ = nparticles;
  smoothinglength_ = smoothinglength;
  kernel_ = kernel;
  
  // this could change, but currently we are just using a simple
  // array of particles
  particles_ = new Particle*[nparticles_];

}

Fluid::~Fluid(){
  delete [] particles_;
  delete kernel_;
}

//should this just be addParticle(Properties props) ?
void Fluid::addParticle(int tag, Properties prop){
  particles_[tag] = new Particle(tag,nparticles_,prop);
//  particles_[tag] = new Particle(tag,prop);  
}

void Fluid::findNeighbors(){
  Properties propi, propj;
  // old or new??
  std::string old = "OLD";
  for(int i=0; i<nparticles_; ++i){
    particles_[i]->get(old,propi);
    for(int j=i+1; j<nparticles_; ++j){
      particles_[j]->get(old,propj);
      float dist = sqrt(pow(propi.x-propj.x,2)+
        pow(propi.y-propj.y,2));
        
        //should this cutoff distance be larger?
      if(dist < 5.*smoothinglength_){
        particles_[i]->addNeighbor(particles_[j]);
        particles_[j]->addNeighbor(particles_[i]);
      }
    }
  }
}

void Fluid::resetNeighbors(){
  for(int i=0; i<nparticles_; ++i){
    particles_[i]->deleteNeighbors();
  }
}

Kernel* Fluid::getKernel(){
  // should this just be Kernel Fluid::..?
  return kernel_;
}

int Fluid::getNParticles(){
  return nparticles_;
}

void Fluid::getParticles(Particle** particles){
  for (int i=0; i<nparticles_; i++) {
    particles[i] = particles_[i];
  }
}

void Fluid::resetParticles(Particle** newparticles) {
  delete [] particles_;
  particles_ = new Particle*[nparticles_];
  for(int i=0; i<nparticles_; ++i){
    particles_[i] = newparticles[i];
  }
}
