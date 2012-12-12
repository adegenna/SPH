#include "fluid.h"

Fluid::Fluid(Kernel* kernel, int nparticles, double smoothinglength){
  nparticles_ = nparticles;
  smoothinglength_ = smoothinglength;
  Kernel_ = kernel;
  
  // this could change, but currently we are just using a simple
  // array of particles
  particles_ = new Particle[nparticles_];

}

Fluid::~Fluid(){
  delete [] particles_;
  delete kernel_;
}

void Fluid::addParticle(int tag, double *x, double *v, double mass, 
    double pressure, double visc){
  Properties props;
  prop.x = x[0];
  props.y = x[1];
  props.u = v[0];
  props.v = v[1];
  props.mass = mass;
  props.pressure = pressure;
  props.visc = visc;
  particles_[tag] = new Particle(props);
  delete props;
}

void Fluid::findNeighbors(){
  Properties propi, propj;
  for(int i=0; i<nparticles_; ++i){
    particles_[i].get("OLD",&propi);
    for(int j=i+1; j<nparticles_; ++j){
      // old or new?
      particles_[j].get("OLD",&propj);
      float dist = sqrt(pow(propi.x[0]-propj.x[0],2)+
        pow(propi.x[1]-propj.x[1],2));
      if(dist < smoothinglenght_){
        particles_[i].addNeighbor(particles_[j]);
        particles_[j].addNeighbor(particles_[i]);
      }
    }
  }
  delete propi;
  delete propj;
}

void Fluid::resetNeighbors(){
  for(int i=0; i<nparticles_; ++i){
    particles_[i].deleteNeighbors();
  }
}

Kernel Fluid::getKernel(){
  return kernel_;
}
