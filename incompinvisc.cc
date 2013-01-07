#include "incompinvisc.h"

#include <cmath>
#include "fluid.h"
#include "particle.h"
#include "kernel.h"


int IncompInvisc::rhs(Fluid& fluid, Particle& part, Kernel& myker, Properties& fx) {   // change input to fluid
    
    numberneighbors_ = part.numberOfNeighbors();
    numberboundaryneighbors_ = part.numberOfBoundaryNeighbors();
    
    Particle::TagArray neighbortags = part.getNeighbors();    // Returns tags of all fluid neighbors
    partprops_ = part.getOldProperties();
    partloc_.x = partprops_.x;
    partloc_.y = partprops_.y;
    
    drho_ = 0.;
    dv_ = 0.;
    du_ = 0.;
    
    Fluid::ParticleArray neighbors = fluid.getParticles();
    
    for(int i=0; i<numberneighbors_; ++i) {
        
        neighprops_ = neighbors[neighbortags[i]]->getOldProperties();
        veldiff_.x = partprops_.u-neighprops_.u;
        veldiff_.y = partprops_.v-neighprops_.v;
        neighloc_.x = neighprops_.x;
        neighloc_.y = neighprops_.y;
        
        gradker_ = myker.gradW(partloc_,neighloc_);
        
		//add contribution to change in density of particle part by neighbors
        drho_ += neighprops_.mass * (veldiff_.x * gradker_.x + veldiff_.y * gradker_.y);

		//add contribution to change in velocity of particle part by neighbors
        coeff_ = neighprops_.mass * (partprops_.pressure/ pow(partprops_.density,2)
                                   + neighprops_.pressure/ pow(neighprops_.density,2));

        du_ += - coeff_ *gradker_.x;
        dv_ += - coeff_ *gradker_.y;
    }
    
    Fluid::ParticleArray boundaryneighbors = fluid.getBoundaries();
    Particle::TagArray boundaryneighbortags = part.getBoundaryNeighbors(); // Returns tags of all boundary neighbors
    
    //add contribution from boundary neighbors:
    for(int i=0; i<numberboundaryneighbors_; ++i) {
        
        //treating boundary particles as having the same properties as fluid particles:
        neighprops_ = boundaryneighbors[boundaryneighbortags[i]]->getOldProperties();
        
        veldiff_.x = partprops_.u-neighprops_.u;
        veldiff_.y = partprops_.v-neighprops_.v;
        neighloc_.x = neighprops_.x;
        neighloc_.y = neighprops_.y;
        gradker_ = myker.gradW(partloc_,neighloc_);
        
		//add contribution to change in density of particle part by boundary neighbors
        //do we want to include this or not? Seems to work better without
        //drho_ += neighprops_.mass * (veldiff_.x * gradker_.x + veldiff_.y * gradker_.y);
        
		//add contribution to change in velocity of particle part by boundary neighbors
        //coeff_ = neighprops_.mass * (partprops_.pressure/ pow(partprops_.density,2)
        //                             + neighprops_.pressure/ pow(neighprops_.density,2));
        
        //Change to use a Lennard-Jones type force at the boundary
        double r0 = 1;
        double r = hypot(partloc_.x-neighloc_.x,partloc_.y-neighloc_.y);
        double r0hat = r0 / r;
        if ( r0hat > 1) {
            double dmag = 0.000001 * (pow(r0hat,12)-pow(r0hat,6)) / r;
            du_ +=  dmag *(partloc_.x-neighloc_.x)  / r;
            dv_ += dmag *(partloc_.y-neighloc_.y)  / r;
        }
    }

    //add gravitational force (scaled down for now)
    dv_ += -0.1;    
    
    //update changes as a property struct
    fx.u = du_;
    fx.v = dv_;
    fx.density = drho_;
    //the following are unnecessary, but I set them to 0 for clarity:
    fx.mass = 0;
    fx.visc = 0;
    fx.x = 0;
    fx.y = 0;

    return 0;
}


//This function might be obsolete now. I put this directly in the integrator (Euler)
int IncompInvisc::update(Particle& part) {
    partprops_ = part.getNewProperties();
    part.setOldProperties(partprops_);
    return 0;
}

int IncompInvisc::initPressureParams() {   //this is currently inactive
    B_ = 3000; 
    gamma_ = 7;
    rho_0_ = 1000.;
    return 0;
}


int IncompInvisc::calcPressure(Particle& part) {
    //set properties to those which approximate water
    B_ = 3000;   //this should be changed so the parameters are not set every time
    gamma_ = 7;
    rho_0_ = 1000.;
    Properties props = part.getOldProperties();
    props.pressure = B_ * (pow(props.density / rho_0_,gamma_)-1.);
    part.setOldProperties(props);
    return 0;
}
