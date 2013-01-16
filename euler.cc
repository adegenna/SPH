#include "euler.h"

/**
 *  \file
 *  
 *  \brief Integrator implimenting the explicit Euler method.
 * */

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
        Properties fx;   //struct to store the changes in particle properties,
                         //which itself can be a Properties struct.
        fx.x = 0;
        fx.y = 0;
        fx.u = 0;
        fx.v = 0;
        fx.density = 0;
        fx.mass = 0;
        fx.pressure = 0;
        fx.visc = 0;

        physics_.rhs(fluid_, *particles[i], fluid_.getKernel(), fx);
        Properties props = particles[i]->getOldProperties();
        
        props.x += props.u * dt_;
        props.y += props.v * dt_;
        props.density += fx.density * dt_;
        props.u += fx.u * dt_;
        props.v += fx.v * dt_;
        particles[i]->setNewProperties(props);
    }
    
    for(int i=0; i<nparticles; ++i){
        const Properties props = particles[i]->getNewProperties();
        particles[i]->setOldProperties(props);
    }
    
    fluid_.resetParticles(particles);

    return 0;
}
