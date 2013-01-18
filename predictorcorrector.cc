#include "predictorcorrector.h"

PredictorCorrector::PredictorCorrector(double dt, 
    Fluid& fluid, 
    Physics& physics) :
  dt_(dt),
  fluid_(fluid),
  physics_(physics)
{}

// Step all particles forward using predictor-corrector method
int PredictorCorrector::step(){
  int nparticles = fluid_.getNParticles();
  Fluid::ParticleArray particles = fluid_.getParticles();
  Fluid::ParticleArray boundaries = fluid_.getBoundaries();
  Properties propsOrig;
  Properties props;

  //Predictor step: 
  for(int i=0; i<nparticles; ++i){
    physics_.calcPressure(*particles[i]);
  }

  for(int i=0; i<nparticles; ++i){
    fx_.x = 0;
    fx_.y = 0;
    fx_.u = 0;
    fx_.v = 0;
    fx_.density = 0;
    fx_.mass = 0;
    fx_.pressure = 0;
    fx_.energy = 0;

    physics_.rhs(fluid_, *particles[i], fluid_.getKernel(), fx_);

    props = particles[i]->getOldProperties();
    props.density += fx_.density * dt_ * 0.5;
    props.u += fx_.u * dt_ * 0.5;
    props.v += fx_.v * dt_ * 0.5;
    //use updated velocity to update position:
    props.x += props.u * dt_ * 0.5;
    props.y += props.v * dt_ * 0.5;
    particles[i]->setNewProperties(props);
  }

  for(int i=0; i<nparticles; ++i){
    props = particles[i]->getNewProperties();
    propsOrig = particles[i]->getOldProperties();
    particles[i]->setOldProperties(props);
    //Storing the original properties in New for the time being,
    //as they will be needed later
    particles[i]->setNewProperties(propsOrig);
  }

  //Corrector step
  for(int i=0; i<nparticles; ++i){ 
    physics_.calcPressure(*particles[i]);
  }

  for(int i=0; i<nparticles; ++i){
    fx_.x = 0;
    fx_.y = 0;
    fx_.u = 0;
    fx_.v = 0;
    fx_.density = 0;
    fx_.mass = 0;
    fx_.pressure = 0;
    fx_.energy = 0;

    physics_.rhs(fluid_, *particles[i], fluid_.getKernel(), fx_);
    props = particles[i]->getNewProperties();  
    props.density += fx_.density * dt_;  
    props.u += fx_.u * dt_;
    props.v += fx_.v * dt_;
    //use updated velocity to update position:
    props.x += props.u * dt_;
    props.y += props.v * dt_;
    particles[i]->setNewProperties(props);
  }

  for(int i=0; i<nparticles; ++i){
    particles[i]->setOldProperties(particles[i]->getNewProperties());
  }

  fluid_.resetParticles(particles);

  return 0;
}
