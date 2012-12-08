#include "incompinvisc.h"
//#include "Kernel.h"
//#include <math.h>

IncompInvisc::IncompInvisc()
    : //delta_(delta),
      //gamma_(gamma),
      //omega_(omega)
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
    
    // part->Get("OLD",location_,velocity_,density_,mass_,pressure_);
    drho = 0.;
    dv = 0.;
    
    PartProps.x;
    for(int i=0; i<NumberNeighbors; i++) {
        
        neighbors[i]->Get("Old",&NeighProps);
        Vector velDiff = {PartProps.u-NeighProps.u,PartProps.v-NeighProps.v};
        Vector neighLoc = {NeighProps.x,NeighProps.y};
        Vector GradKer = myKer->gradW(partloc,neighLoc,s);
        Vector Kgrad = myKer->gradW(neighLoc,GradKer);
        
        drho += NeighProps.mass * (velDiff.x * Kgrad.x + velDiff.y * Kgrad.y);
        
        drho += massi_ * InnerProduct2D(velocity_-velocityi_,Kgrad);  //,*Kx,*Ky);

        
        
  		drho += x[1];
  		fx[1] = x[0] * (1 - x[0]*x[0]) - delta_ * x[1] + gamma_ * cos(omega_*t);
    }
    
    delete neighbors;
   // part->UpdateNewDensity
   // part->UpdateNewVelocity
  return 0;
}
