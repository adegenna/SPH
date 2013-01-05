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

// Step all particles forward using explicit Euler method
//I don't think we explicitly need time here, as equations are time invariant
int Euler::step(){
    Properties props;
    int nparticles = fluid_->getNParticles();
    int nboundaries = fluid_->getNBoundaries();
    Particle** particles = new Particle*[nparticles];
    Particle** boundaries = new Particle*[nboundaries];
    fluid_->getParticles(particles);
    fluid_->getBoundaries(boundaries);

    for(int i=0; i<nparticles; ++i){
        physics_->calcPressure(particles[i]);
    }
    for(int i=0; i<nboundaries; ++i){
        physics_->calcPressure(boundaries[i]);
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

        //update pressure. This is passing more info than is necessary. Perhaps
        //create a setPressure function

        physics_->rhs(fluid_, particles[i],fluid_->getKernel(),fx);
//        std::cout << "Euler: fx.u = " <<fx.u <<std::endl;
        
        
        //Do Euler's method for all properties,
        //maybe there is a nicer way to do this:
        
        particles[i]->get("OLD", props);
        props.x += props.u * dt_;
        props.y += props.v * dt_;
        props.density += fx.density * dt_;
        props.u += fx.u * dt_;
        props.v += fx.v * dt_;
        particles[i]->set("NEW", props);
        
//        std::cout << "Euler: x = " <<props.x <<std::endl;
//        std::cout << "Euler: u = " <<props.u <<std::endl;
//        std::cout << "Euler: fx.u = " <<fx.u <<std::endl;
//        std::cout << "Euler: fx.density = " <<fx.density <<std::endl;
        
    }
    
    for(int i=0; i<nparticles; ++i){
        particles[i]->get("NEW", props);
        particles[i]->set("OLD", props);
    }
    
    
    fluid_->resetParticles(particles);
    delete particles;
    delete boundaries;
    return 0;
}
