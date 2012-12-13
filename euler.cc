#include "euler.h"
//#include "physics.h"

Euler::Euler(double dt, const Fluid &fluid, const Physics &physics)
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
int Euler::Step(Particle* particle) {
    Properties props;
    particle->get("OLD", props);
    
    Properties fx;   //struct to store the changes in particle properties,
                     //which itself can be a Properties struct.
    
    myphysics->rhs(particle,kernel_,fx_);
    
    //Do Euler's method for all properties,
    //maybe there is a nicer way to do this:
    props_.x += props_.u * dt_;
    props_.y += props_.v * dt_;
    props_.density += fx_.density * dt_;
    props_.u += fx_.u * dt_;
    props_.v += fx_.v * dt_;
    
    double pressure_;
    myphysics->calcPressure(particle,pressure_);
    props_.pressure = pressure_;

    particle->set("NEW",props);
    return 0;
}