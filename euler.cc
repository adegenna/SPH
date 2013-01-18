#include "euler.h"

Euler::Euler(double dt, Fluid& fluid, Physics& physics) :
dt_(dt),
fluid_(fluid),
physics_(physics)
{}

// Step all particles forward using explicit Euler method
int Euler::step(){
  int nparticles = fluid_.getNParticles();
  Fluid::ParticleArray particles = fluid_.getParticles();
  Fluid::ParticleArray boundaries = fluid_.getBoundaries();

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
    Properties props = particles[i]->getOldProperties();

    props.x += props.u * dt_;
    props.y += props.v * dt_;
    props.density += fx_.density * dt_;
    props.u += fx_.u * dt_;
    props.v += fx_.v * dt_;
    particles[i]->setNewProperties(props);
  }

  for(int i=0; i<nparticles; ++i){
    const Properties props = particles[i]->getNewProperties();
    particles[i]->setOldProperties(props);
  }

  fluid_.resetParticles(particles);

  return 0;
}
