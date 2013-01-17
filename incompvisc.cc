#include "incompvisc.h"

/**
 * \file
 *
 * \brief Physics for an approximately incompressible fluid, with viscosity to damp motion
 */

IncompVisc::IncompVisc(double smoothinglength, double grav, 
                       double pressB, double pressGamma, 
                       double rho_0, 
                       double viscAlpha, double viscEta):
r0_(smoothinglength),
grav_(grav),
pressB_(pressB),
pressGamma_(pressGamma),
rho_0_(rho_0),
viscAlpha_(viscAlpha),
viscEta_(viscEta)
{}

// Evaluate the rate of change of density and velocity
int IncompVisc::rhs(Fluid& fluid, Particle& part, Kernel& myker, Properties& fx) {   // change input to fluid
    
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
        
        //compute viscous force
        rx_ = partprops_.x - neighprops_.x;
        ry_ = partprops_.y - neighprops_.y;
        vdotr_ =  veldiff_.x * rx_  + veldiff_.y * ry_;
        if (vdotr_ < 0.) {
            viscMu_ = viscAlpha_ * vdotr_/(pow(rx_,2)+pow(ry_,2)+viscEta_);
            viscousforce_ = - viscMu_/ (partprops_.density+neighprops_.density);
        }
        else {
            viscousforce_ = 0;
        }
        
		//add contribution to change in velocity of particle part by neighbors
        coeff_ = neighprops_.mass * (partprops_.pressure/ pow(partprops_.density,2)
                                   + neighprops_.pressure/ pow(neighprops_.density,2)+viscousforce_);
        du_ += - coeff_ *gradker_.x;
        dv_ += - coeff_ *gradker_.y;
    }
    
    Fluid::ParticleArray boundaryneighbors = fluid.getBoundaries();
    Particle::TagArray boundaryneighbortags = part.getBoundaryNeighbors(); // Returns tags of all boundary neighbors
    
    //add contribution from boundary neighbors:
    for(int i=0; i<numberboundaryneighbors_; ++i) {
        
        //treating boundary particles as having the same properties as fluid particles:
        neighprops_ = boundaryneighbors[boundaryneighbortags[i]]->getOldProperties();
        neighloc_.x = neighprops_.x;
        neighloc_.y = neighprops_.y;
        
		//add contribution to change in density of particle part by boundary neighbors
        //using a Lennard-Jones type force at the boundary
        //double r0 = 1;
        double r = hypot(partloc_.x-neighloc_.x,partloc_.y-neighloc_.y);
        double r0hat = r0_ / r;
        if ( r0hat > 1) {
            double dmag = 0.000001 * (pow(r0hat,12)-pow(r0hat,6)) / r;
            du_ +=  dmag *(partloc_.x-neighloc_.x)  / r;
            dv_ += dmag *(partloc_.y-neighloc_.y)  / r;
        }
    }

    //add gravitational force (scaled approx value for cm/s^2)
    dv_ += -grav_;    
    
    //update changes as a property struct
    fx.u = du_;
    fx.v = dv_;
    fx.density = drho_;
    //the following assignments are unnecessary, but set them to 0 for clarity:
    fx.mass = 0;
    fx.visc = 0;
    fx.x = 0;
    fx.y = 0;

    return 0;
}


//This function might be obsolete now. I put this directly in the integrator (Euler)
int IncompVisc::update(Particle& part) {
    partprops_ = part.getNewProperties();
    part.setOldProperties(partprops_);
    return 0;
}

int IncompVisc::initPressureParams() {   //this is currently inactive
    return 0;
}


int IncompVisc::calcPressure(Particle& part) {
    //set properties to those which approximate water
//    B_ = 3000;   //this should be changed so the parameters are not set every time
//    gamma_ = 7;
//    rho_0_ = 1000.;
    Properties props = part.getOldProperties();
    props.pressure = pressB_ * (pow(props.density / rho_0_,pressGamma_)-1.);
    part.setOldProperties(props);
    return 0;
}
