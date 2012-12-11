#include "incompinvisc.h"
#include "kvector.h"
//#include <stdio.h>
//#include <iostream>
//#include <stdlib.h>
IncompInvisc::IncompInvisc()
   // : 
{}

IncompInvisc::~IncompInvisc()
{}

//using namespace std;

int IncompInvisc::advance(Particle* part, Kernel* myker,_dt) {   // change input to fluid
    
    numberneighbors = part->numberOfNeighbors();  //maybe put in struct
    Particle** neighbors = new Particle*;
    part->GetNeighbors(neighbors);
    
    //Properties PartProps_;
    part->get("OLD", partprops_);
    Kvector partloc_ = {partprops_.x,partprops_.y};
    
    //Properties neighprops_;

    drho_ = 0.;
    dv_ = 0.;
    du_ = 0. ;

    for(int i=0; i<numberneighbors; i++) {
        
        neighbors[i]->Get("OLD",neighprops_);
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
        
        //cout << "du = " du_ <<endl;
    }
    
    partprops_.density += drho_ * dt_;
    partprops_.u += du_ * dt_;
    partprops_.v += dv_ * dt_;
    part->set("NEW",partprops_);
    delete neighbors;
    return 0;
}

int IncompInvisc::update(Particle* part) {
    part->get("NEW",partprops_);
    part->set("OLD",partprops_);
    return 0;
}
