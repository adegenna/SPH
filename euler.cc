#include "euler.h"
//#include "physics.h"

Euler::Euler(double dt,Fluid *fluid,Physics *physics){
  dt_ = dt;
  fluid_ = fluid;
  physics_ = physics;
}

Euler::~Euler() {
  delete [] fx_;
}

//Step a single particle
//I don't think we explicitly need time here, as equations are time invariant
int Euler::step(){
    Properties props;
    int nparticles = fluid_->getNParticles();
    Particle** particles = new Particle*[nparticles];
    particles = fluid_->getParticles();
    for(int i=0; i<nparticles; ++i){
      particles[i]->get("OLD", props);
      
      Properties fx;   //struct to store the changes in particle properties,
                       //which itself can be a Properties struct.
      
      physics_->rhs(particles[i],fluid_->getKernel(),fx);
      
      //Do Euler's method for all properties,
      //maybe there is a nicer way to do this:
      props.x += props.u * dt_;
      props.y += props.v * dt_;
      props.density += fx.density * dt_;
      props.u += fx.u * dt_;
      props.v += fx.v * dt_;
      
      double pressure_;
      physics_->calcPressure(particles[i],pressure_);
      props.pressure = pressure_;

      particles[i]->set("NEW",props);
    }
    return 0;
}
