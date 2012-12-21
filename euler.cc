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
    Particle** particles = new Particle*[nparticles];
    particles = fluid_->getParticles();
    
 //   std::cout <<"hereS1"<<std::endl;
    for(int i=0; i<nparticles; ++i){
      physics_->calcPressure(particles[i]);
      particles[i]->get("OLD", props);
      
      Properties fx;   //struct to store the changes in particle properties,
                       //which itself can be a Properties struct.

        //update pressure. This is passing more info than is necessary. Perhaps
        //create a setPressure function
      particles[i]->set("OLD", props);
      //  std::cout <<"hereS3"<<std::endl;
      physics_->rhs(particles[i],fluid_->getKernel(),fx);
      //std::cout <<"hereS4"<<std::endl;
        
      //Do Euler's method for all properties,
      //maybe there is a nicer way to do this:
      props.x += props.u * dt_;
      props.y += props.v * dt_;
      props.density += fx.density * dt_;
      props.u += fx.u * dt_;
      props.v += fx.v * dt_;
        
     //   std::cout << "fx.u = " <<fx.u<<std::endl;
     //   std::cout << "fx.v = " <<fx.v<<std::endl;

      particles[i]->set("NEW",props);
    }
    
    for(int i=0; i<nparticles; ++i){
        particles[i]->get("NEW", props);
        particles[i]->set("OLD", props);
    }
    return 0;
}
