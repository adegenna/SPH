#include "incompinvisc.h"
#include "kvector.h"
//#include <stdio.h>
#include <iostream>
//#include <stdlib.h>
IncompInvisc::IncompInvisc()
   // : 
{}

IncompInvisc::~IncompInvisc()
{}

using namespace std;

int IncompInvisc::rhs(Fluid* fluid, Particle* part, Kernel* myker, Properties &fx) {   // change input to fluid
    
    numberneighbors_ = part->numberOfNeighbors();
    numberboundaryneighbors_ = part->numberOfBoundaryNeighbors();
    
    Particle** neighbors = new Particle*[fluid->getNParticles()];
    Particle** boundaryneighbors = new Particle*[fluid->getNBoundaries()];
    
    int neighbortags[numberneighbors_];
    part->getNeighbors(neighbortags);    // Returns tags of all fluid neighbors
    int boundaryneighbortags[numberboundaryneighbors_];
    partprops_ = part->getOldProperties();
    partloc_.x = partprops_.x;
    partloc_.y = partprops_.y;
    
    drho_ = 0.;
    dv_ = 0.;
    du_ = 0.;
    
    fluid->getParticles(neighbors);
    
    for(int i=0; i<numberneighbors_; ++i) {
        
        neighprops_ = neighbors[neighbortags[i]]->getOldProperties();
        veldiff_.x = partprops_.u-neighprops_.u;
        veldiff_.y = partprops_.v-neighprops_.v;
        neighloc_.x = neighprops_.x;
        neighloc_.y = neighprops_.y;
        
        gradker_ = myker->gradW(partloc_,neighloc_);
        
        
		//add contribution to change in density of particle part by neighbors
        drho_ += neighprops_.mass * (veldiff_.x * gradker_.x + veldiff_.y * gradker_.y);

		//add contribution to change in velocity of particle part by neighbors
        coeff_ = neighprops_.mass * (partprops_.pressure/ pow(partprops_.density,2)
                                   + neighprops_.pressure/ pow(neighprops_.density,2));

        du_ += - coeff_ *gradker_.x;
        dv_ += - coeff_ *gradker_.y;
    }
    
    fluid->getBoundaries(boundaryneighbors);
    part->getBoundaryNeighbors(boundaryneighbortags); // Returns tags of all boundary neighbors    
    
    //add contribution from boundary neighbors:
    for(int i=0; i<numberboundaryneighbors_; ++i) {
        
        //treating boundary particles as having the same properties as fluid particles:
        neighprops_ = boundaryneighbors[boundaryneighbortags[i]]->getOldProperties();
        
        veldiff_.x = partprops_.u-neighprops_.u;
        veldiff_.y = partprops_.v-neighprops_.v;
        neighloc_.x = neighprops_.x;
        neighloc_.y = neighprops_.y;
        gradker_ = myker->gradW(partloc_,neighloc_);
        
		//add contribution to change in density of particle part by boundary neighbors
        drho_ += neighprops_.mass * (veldiff_.x * gradker_.x + veldiff_.y * gradker_.y);
        
		//add contribution to change in velocity of particle part by boundary neighbors
        coeff_ = neighprops_.mass * (partprops_.pressure/ pow(partprops_.density,2)
                                     + neighprops_.pressure/ pow(neighprops_.density,2));
    
        
        du_ += - coeff_ *gradker_.x;
        dv_ += - coeff_ *gradker_.y;
    }

    //add gravitational force
    dv_ += -1.;    
    
    //update changes as a property struct
    fx.u = du_;
    fx.v = dv_;
    fx.density = drho_;
    //the following are unnecessary, but I set them to 0 for clarity:
    fx.mass = 0;
    fx.visc = 0;
    fx.x = 0;
    fx.y = 0;
    delete neighbors;
    delete boundaryneighbors;
    return 0;
}


//This function might be obsolete now. I put this directly in the integrator (Euler)
int IncompInvisc::update(Particle* part) {
    partprops_ = part->getNewProperties();
    part->setOldProperties(partprops_);
    return 0;
}

int IncompInvisc::calcPressure(Particle* part) {
    //set properties to those which apparently approximate water
    
    int B = 3000;   //this should be changed so the parameters are not set every time
    int gamma = 7;
    double rho_0 = 1000.;
    Properties props = part->getOldProperties();
    props.pressure = B * (pow(props.density / rho_0,gamma)-1.);
    part->setOldProperties(props);
    return 0;
}
