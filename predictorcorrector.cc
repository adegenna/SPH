#include "predictorcorrector.h"
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
    //The following is required to keep track of the original particle properties
    //which is needed for the corrector step
    //Fluid::ParticleArray particlesOld = fluid_.getParticles();
    Fluid::ParticleArray boundaries = fluid_.getBoundaries();
    Properties propsOrig;
    Properties propsPred;
    Properties propsCorr;
 //   Properties props;
    
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
        fx_.visc = 0;

        physics_.rhs(fluid_, *particles[i], fluid_.getKernel(), fx_);
        
        propsPred = particles[i]->getOldProperties();
    //    std::cout <<"Orig y= "<< propsPred.y <<std::endl;
        propsPred.density += fx_.density * dt_ * 0.5;
        propsPred.u += fx_.u * dt_ * 0.5;
        propsPred.v += fx_.v * dt_ * 0.5;
        //use updated velocity to update position:
        propsPred.x += propsPred.u * dt_ * 0.5;
        propsPred.y += propsPred.v * dt_ * 0.5;
      //  std::cout <<"Pred y= "<< propsPred.y <<std::endl;
        particles[i]->setNewProperties(propsPred);
    }
    
    for(int i=0; i<nparticles; ++i){
        propsPred = particles[i]->getNewProperties();
        propsOrig = particles[i]->getOldProperties();
        particles[i]->setOldProperties(propsPred);
        //Storing the original properties in New for the time being
        //as they will be needed later
        particles[i]->setNewProperties(propsOrig);
    }
    
    //Corrector step
    for(int i=0; i<nparticles; ++i){  //check if it works better with or without this
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
        fx_.visc = 0;
        
        physics_.rhs(fluid_, *particles[i], fluid_.getKernel(), fx_);
        
        propsCorr = particles[i]->getOldProperties();
      //  std::cout <<"Orig Corr y= "<< propsCorr.y <<std::endl;
        propsCorr.density += fx_.density * dt_*0.5;  
        propsCorr.u += fx_.u * dt_*0.5;
        propsCorr.v += fx_.v * dt_*0.5;
        //use updated velocity to update position:
        propsCorr.x += propsCorr.u * dt_*0.5;
        propsCorr.y += propsCorr.v * dt_*0.5;
        
        propsOrig = particles[i]->getNewProperties();
        propsCorr.u = 2.*propsCorr.u - propsOrig.u;
        propsCorr.v = 2.*propsCorr.v - propsOrig.v;
        propsCorr.x = 2.*propsCorr.x - propsOrig.x;
        propsCorr.y = 2.*propsCorr.y - propsOrig.y;
        particles[i]->setNewProperties(propsCorr);
        
        //particles[i]->setNewProperties(propsCorr);
    }
    
    //Update final properties  - For some reason this makes it less accurate...
//    for(int i=0; i<nparticles; ++i){
//        propsPred = particles[i]->getOldProperties();
//        propsCorr = particles[i]->getNewProperties();
//        props = particles[i]->getNewProperties();
//        props.density = 2*propsCorr.density - propsPred.density;
//        props.u = 2.*propsCorr.u - propsPred.u;
//        props.v = 2.*propsCorr.v - propsPred.v;
//        props.x = 2.*propsCorr.x - propsPred.x;
//        props.y = 2.*propsCorr.y - propsPred.y;
//        particles[i]->setNewProperties(props);
//    }
    
    for(int i=0; i<nparticles; ++i){
        particles[i]->setOldProperties(particles[i]->getNewProperties());
    }
    
    fluid_.resetParticles(particles);

    return 0;
}
