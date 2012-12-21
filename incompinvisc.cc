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

//using namespace std;

int IncompInvisc::rhs(Particle* part, Kernel* myker, Properties fx) {   // change input to fluid
    
    //this will change, but I'm not entirely sure how to call it at the moment
    numberneighbors = part->numberOfNeighbors(); 
    Particle** neighbors = new Particle*;
    

    part->get("OLD", partprops_);
    Kvector partloc_ = {partprops_.x,partprops_.y};

    drho_ = 0.;
    dv_ = 0.;
    du_ = 0.;
    
    for(int i=0; i<numberneighbors; i++) {
        neighbors[i]->get("OLD",neighprops_);
        Kvector velDiff_ = {partprops_.u-neighprops_.u,partprops_.v-neighprops_.v};

        Kvector neighLoc_ = {neighprops_.x,neighprops_.y};
        Kvector gradKer_ = myker->gradW(partloc_,neighloc_);
		//add contribution to change in density of particle part by neighbors
        drho_ += neighprops_.mass * (veldiff_.x * gradker_.x + veldiff_.y * gradker_.y);
		//add contribution to change in velocity of particle part by neighbors
        coeff_ = neighprops_.mass * (partprops_.pressure/ pow(partprops_.density,2)
                                   + neighprops_.pressure/ pow(neighprops_.density,2));
        du_ += - coeff_ *gradker_.x;
        dv_ += - coeff_ *gradker_.y;
        
        
    }
    std::cout << "du = " << du_ <<std::endl;
    //update changes as a property struct
    fx.u = du_;
    fx.v = dv_;
    fx.density = drho_;
    //part->set("NEW",partprops_);
    delete neighbors;
    return 0;
}


//This function might be obsolete now. I put this directly in the integrator (Euler)
int IncompInvisc::update(Particle* part) {
    part->get("NEW",partprops_);
    part->set("OLD",partprops_);
    return 0;
}

int IncompInvisc::calcPressure(Particle* part) {
    int B = 10;   //this should be changed so the parameters are not set every time
    int gamma = 7;
    // SCOTTTTTT
    Properties props;
    part->get("OLD",props);
    props.pressure = B * (pow(props.density,gamma)-1.);
    part->set("OLD",props);
    return 0;
}
