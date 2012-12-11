#include "incompinvisc.h"
#include "Vector.h"
//#include <stdio.h>
//#include <iostream>
//#include <stdlib.h>
IncompInvisc::IncompInvisc()
   // : 
{}

IncompInvisc::~IncompInvisc()
{}

//using namespace std;

int IncompInvisc::advance(Particle* part, Kernel* myKer) {
    
    NumberNeighbors = part->Number_of_Neighbors();  //maybe put in struct
    Particle** neighbors = new Particle*;
    part->GetNeighbors(neighbors);
    
    //Properties PartProps_;
    part->Get("OLD", PartProps_);
    Vector partLoc_ = {PartProps_.x,PartProps_.y};
    
    Properties NeighProps_;

    drho_ = 0.;
    dv_ = 0.;
    du_ = 0. ;

    for(int i=0; i<NumberNeighbors; i++) {
        
        neighbors[i]->Get("OLD",NeighProps_);
        Vector velDiff_ = {PartProps_.u-NeighProps_.u,PartProps_.v-NeighProps_.v};
        Vector neighLoc_ = {NeighProps_.x,NeighProps_.y};
        Vector gradKer_ = myKer->gradW(partLoc_,neighLoc_);
        
		//add contribution to change in density of particle part by neighbors
        drho_ += NeighProps_.mass * (velDiff_.x * gradKer_.x + velDiff_.y * gradKer_.y);
        
		//add contribution to change in velocity of particle part by neighbors
        coeff_ = NeighProps_.mass * (PartProps_.pressure/ pow(PartProps_.density,2)
                                   + NeighProps_.pressure/ pow(NeighProps_.density,2));
        du_ += - coeff_ *gradKer_.x;
        dv_ += - coeff_ *gradKer_.y;
        
        //cout << "du = " du_ <<endl;
    }
    
    PartProps_.density += drho_;
    PartProps_.u += du_;
    PartProps_.v += dv_;
    part->Set("NEW",PartProps_);
    delete neighbors;
    return 0;
}

int IncompInvisc::update(Particle* part) {
    part->Get("NEW",PartProps_);
    part->Set("OLD",PartProps_);
    return 0;
}
