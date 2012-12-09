#include "incompinvisc.h"
#include "Vector.h"
IncompInvisc::IncompInvisc()
   // : 
{}

IncompInvisc::~IncompInvisc()
{}

int IncompInvisc::update(Particle* part, Kernel* myKer) {
    
    NumberNeighbors = part->Number_of_Neighbors();  //maybe put in struct
    Particle** neighbors = new Particle*;
    part->GetNeighbors(neighbors);
    
    Properties PartProps;
    part->Get("OLD", PartProps);
    Vector partLoc_ = {PartProps.x,PartProps.y};
    
    Properties NeighProps;

    drho_ = 0.;
    dv_ = 0.;
    du_ = 0. ;

    for(int i=0; i<NumberNeighbors; i++) {
        
        neighbors[i]->Get("OLD",NeighProps);
        Vector velDiff_ = {PartProps.u-NeighProps.u,PartProps.v-NeighProps.v};
        Vector neighLoc_ = {NeighProps.x,NeighProps.y};
        Vector gradKer_ = myKer->gradW(partLoc_,neighLoc_);
        
		//add contribution to change in density of particle part by neighbors
        drho_ += NeighProps.mass * (velDiff_.x * gradKer_.x + velDiff_.y * gradKer_.y);
        
		//add contribution to change in velocity of particle part by neighbors
        coeff_ = NeighProps.mass * (PartProps.pressure/ pow(PartProps.density,2)
                                   + NeighProps.pressure/ pow(NeighProps.density,2));
        du_ += - coeff_ *gradKer_.x;
        dv_ += - coeff_ *gradKer_.y;
    }
    
    PartProps.density += drho_;
    PartProps.u += du_;
    PartProps.v += dv_;
    part->Set("NEW",PartProps);
    delete neighbors;
    return 0;
}
