#include "fluid.h"

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

void Fluid::addParticle(int tag, double *x, double *v, double mass, 
    double pressure, double visc){
  Properties props;
  props.x = x[0];
  props.y = x[1];
  props.u = v[0];
  props.v = v[1];
  props.mass = mass;
  props.pressure = pressure;
  props.visc = visc;
  particles_[tag] = new Particle(tag,nparticles_,props);
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
      if(dist < smoothinglength_){
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
