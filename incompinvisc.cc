#include "incompinvisc.h"

IncompInvisc::IncompInvisc()
    : 
{}

IncompInvisc::~IncompInvisc()
{}

int IncompInvisc::update(Particle* part, Kernel* myKer) {
    
    int NumberNeighbors = part->Number_of_Neighbors();  //maybe put in struct
    Particle** neighbors = new Particle*;
    part->GetNeighbors(neighbors);
    
    Properties PartProps;
    part->Get("OLD", &PartProps);
    Vector partLoc = {PartProps.x,PartProps.y};
    
    Properties NeighProps;

    drho = 0.;
    dv = 0.;
    du = 0. ;
    
    PartProps.x;
    for(int i=0; i<NumberNeighbors; i++) {
        
        neighbors[i]->Get("OLD",NeighProps);
        Vector velDiff = {PartProps.u-NeighProps.u,PartProps.v-NeighProps.v};
        Vector neighLoc = {NeighProps.x,NeighProps.y};
        Vector GradKer = myKer->gradW(partloc,neighLoc);
        
		//add contribution to change in density of particle part by neighbors
        drho += NeighProps.mass * (velDiff.x * GradKer.x + velDiff.y * GradKer.y);
        
		//add contribution to change in velocity of particle part by neighbors
        coeff = NeighProps.mass * (PartProps.pressure/ pow(PartProps.density,2)
                                   + NeighProps.pressure/ pow(NeighProps.density,2));
        du += - coeff *GradKer.x;
        dv += - coeff *GradKer.y;
    }
    
    PartProps.density += drho;
    PartProps.u += du;
    PartProps.v += dv;
    part->Set("NEW",PartProps)
    delete neighbors;
  return 0;
}
