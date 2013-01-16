#include "predictorcorrector.h"

#include "fluid.h"
#include "physics.h"
#include "particle.h"
#include <iostream>


PredictorCorrector::PredictorCorrector(double dt, Fluid& fluid, Physics& physics) :
dt_(dt),
fluid_(fluid),
physics_(physics)
{}

// Step all particles forward using predictor-corrector method
int PredictorCorrector::step(){
    int nparticles = fluid_.getNParticles();
    Fluid::ParticleArray particles = fluid_.getParticles();
    Fluid::ParticleArray boundaries = fluid_.getBoundaries();
    Properties fx;
    Properties propsPred;
    Properties propsCorr;
    
    //Predictor step: 
    for(int i=0; i<nparticles; ++i){
        physics_.calcPressure(*particles[i]);
    }
    
    for(int i=0; i<nparticles; ++i){
        fx.x = 0;
        fx.y = 0;
        fx.u = 0;
        fx.v = 0;
        fx.density = 0;
        fx.mass = 0;
        fx.pressure = 0;
        fx.visc = 0;

        physics_.rhs(fluid_, *particles[i], fluid_.getKernel(), fx);
        
        propsPred = particles[i]->getOldProperties();
    //    std::cout <<" propsPred.y = " << propsPred.y <<std::endl;
        propsPred.density += fx.density * dt_ * 0.5;
        
    //    propsPred.x += propsPred.u * dt_ * 0.5;
    //    propsPred.y += propsPred.v * dt_ * 0.5;        
        
        propsPred.u += fx.u * dt_ * 0.5;
        propsPred.v += fx.v * dt_ * 0.5;
        //use updated velocity to update position:
        propsPred.x += propsPred.u * dt_ * 0.5;
        propsPred.y += propsPred.v * dt_ * 0.5;
        
        particles[i]->setNewProperties(propsPred);
    }
    
    for(int i=0; i<nparticles; ++i){
        const Properties propsPred = particles[i]->getNewProperties();
        particles[i]->setOldProperties(propsPred);
    }
    
    //Corrector step
//    for(int i=0; i<nparticles; ++i){
//        physics_.calcPressure(*particles[i]);
//    }
//    for(int i=0; i<nboundaries; ++i){
//        physics_.calcPressure(*boundaries[i]);
//    }
    
    for(int i=0; i<nparticles; ++i){
        fx.x = 0;
        fx.y = 0;
        fx.u = 0;
        fx.v = 0;
        fx.density = 0;
        fx.mass = 0;
        fx.pressure = 0;
        fx.visc = 0;
        
        physics_.rhs(fluid_, *particles[i], fluid_.getKernel(), fx);
        
        propsCorr = particles[i]->getOldProperties();
        
    //    std::cout <<" propsCorr.y = " << propsCorr.y <<std::endl;
        propsCorr.density += fx.density * dt_*0.5;
        
    //    propsCorr.x += propsCorr.u * dt_*0.5;
    //    propsCorr.y += propsCorr.v * dt_*0.5;       
        propsCorr.u += fx.u * dt_*0.5;
        propsCorr.v += fx.v * dt_*0.5;
        //use updated velocity to update position:
        propsCorr.x += propsCorr.u * dt_*0.5;
        propsCorr.y += propsCorr.v * dt_*0.5;
        
        particles[i]->setNewProperties(propsCorr);
    }
    
    //Update properties
    for(int i=0; i<nparticles; ++i){
        propsPred = particles[i]->getOldProperties();
        propsCorr = particles[i]->getNewProperties();
        Properties props = particles[i]->getOldProperties();
        props.density = 2*propsCorr.density - propsPred.density;
        props.u = 2.*propsCorr.u - propsPred.u;
        props.v = 2.*propsCorr.v - propsPred.v;
        props.x = 2.*propsCorr.x - propsPred.x;
        props.y = 2.*propsCorr.y - propsPred.y;
    
        particles[i]->setNewProperties(propsCorr);
    }
    
    for(int i=0; i<nparticles; ++i){
        const Properties props = particles[i]->getNewProperties();
        particles[i]->setOldProperties(props);  //testing
     //   std::cout <<" props.y = " << props.y <<std::endl;
    }
    
    fluid_.resetParticles(particles);

    return 0;
}
