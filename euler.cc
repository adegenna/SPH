#include "euler.h"
//#include "physics.h"

Euler::Euler(double dt, const Fluid *fluid, const Physics *physics)
    : //dimen_(model.dimen()),
      dt_(dt),
      model_(model) {
 // fx_ = new double[dimen_];
}

Euler::~Euler() {
  delete [] fx_;
}

//Step a single particle
//I don't think we explicitly need time here, as equations are time invariant
int Euler::step(){
    Properties props;
    int nparticles = fluid->getNParticles();
    Particle** particles = new Particle*[nparticles];
    particles = fluid->getParticles();
    for(int i=0; i<nparticles; ++i){
      particles[i]->get("OLD", props);
      
      Properties fx;   //struct to store the changes in particle properties,
                       //which itself can be a Properties struct.
      
      myphysics->rhs(particles[i],kernel_,fx_);
      
      //Do Euler's method for all properties,
      //maybe there is a nicer way to do this:
      props_.x += props_.u * dt_;
      props_.y += props_.v * dt_;
      props_.density += fx_.density * dt_;
      props_.u += fx_.u * dt_;
      props_.v += fx_.v * dt_;
      
      double pressure_;
      myphysics->calcPressure(particles[i],pressure_);
      props_.pressure = pressure_;

      particles[i]->set("NEW",props);
    }
    return 0;
}
