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
    
    //this will change, but I'm not entirely sure how to call it at the moment
    numberneighbors_ = part->numberOfNeighbors();
    numberboundaryneighbors_ = part->numberOfBoundaryNeighbors();
    int N = fluid->getNParticles();
    int NB = fluid->getNBoundaries();
    Particle** neighbors = new Particle*[N];
    Particle** boundaryneighbors = new Particle*[NB];
    
    
    int neighbortags[numberneighbors_];
    
    part->getNeighbors(neighbortags); // Returns tags of all fluid neighbors
  //  cout << "size neighbortags = " <<sizeof(neighbortags)<<endl;
    
    
    int boundaryneighbortags[numberboundaryneighbors_];
//    cout << "size neighbortagsA = " <<sizeof(neighbortags)<<endl;
    //part->getBoundaryNeighbors(boundaryneighbortags); // Returns tags of all boundary neighbors    
    
  //  cout << "size neighbortagsB = " <<sizeof(neighbortags)<<endl;
    part->get("OLD", partprops_);
    //Kvector partloc_ = {partprops_.x,partprops_.y};

    //assign kvector partloc_ appropriately
    partloc_.x = partprops_.x;
    partloc_.y = partprops_.y;
    
    drho_ = 0.;
    dv_ = 0.;
    du_ = 0.;
    
//    std::cout<<"numberneighbors = "<< numberneighbors_<<std::endl;
//    std::cout<<"boundaryneighbors = "<< numberboundaryneighbors_<<std::endl;
//    std::cout<<"xlocation "<< partprops_.x<<std::endl;
//    cout << "x = " << partprops_.x <<endl;
//    cout << "y = " << partprops_.y <<endl;
//    cout << "u = " << partprops_.u <<endl;
//    cout << "v = " << partprops_.v <<endl;
//    cout << "mass = " << partprops_.mass <<endl;
//    cout << "density = " << partprops_.mass <<endl;
//    cout << "visc = " << partprops_.visc <<endl;
    
   // cout << "size neighbortags = " <<sizeof(neighbortags)<<endl;
    
    fluid->getParticles(neighbors);
    
    for(int i=0; i<numberneighbors_; ++i) {
        
//        cout << "i = " << i <<endl;
//        cout << "neighbortags[0] =  " << neighbortags[0] <<endl;
//         cout << "neighbortags[1] =  " << neighbortags[1] <<endl;
//         cout << "neighbortags[2] =  " << neighbortags[2] <<endl;
//         cout << "neighbortags[3] =  " << neighbortags[3] <<endl;
//         cout << "neighbortags[4] =  " << neighbortags[4] <<endl;
//        cout << "neighbortags[5] =  " << neighbortags[5] <<endl;
        
        
        neighbors[neighbortags[i]]->get("OLD",neighprops_);
//        std::cout<<"neighbor xlocation "<<neighprops_.x<<std::endl;
//        std::cout<<"partu "<< partprops_.u<<std::endl;
//        std::cout<<"neighu "<< neighprops_.u<<std::endl;
        
        //these shouldn't be redefined as Kvectors each time, but I seem to get an error otherwise:
//        Kvector veldiff_ = {partprops_.u-neighprops_.u,partprops_.v-neighprops_.v};
//        Kvector neighloc_ = {neighprops_.x,neighprops_.y};
        //I can fix the above problem  with the following:
        veldiff_.x = partprops_.u-neighprops_.u;
        veldiff_.y = partprops_.v-neighprops_.v;
        neighloc_.x = neighprops_.x;
        neighloc_.y = neighprops_.y;
        
        gradker_ = myker->gradW(partloc_,neighloc_);
        
        
		//add contribution to change in density of particle part by neighbors
        drho_ += neighprops_.mass * (veldiff_.x * gradker_.x + veldiff_.y * gradker_.y);
        
//        std::cout<<"veldiff_.x = "<< veldiff_.x<<std::endl;
//        std::cout<<"gradker_.x = "<< gradker_.x<<std::endl;
//        std::cout<<"drho = "<< drho_<<std::endl;

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
        boundaryneighbors[boundaryneighbortags[i]]->get("OLD",neighprops_);
        
        //these should be redefined as Kvectors each time, but I seem to get an error otherwise:
      //  Kvector veldiff_ = {partprops_.u-neighprops_.u,partprops_.v-neighprops_.v};
//        Kvector neighloc_ = {neighprops_.x,neighprops_.y};
//        Kvector gradker_ = myker->gradW(partloc_,neighloc_);
//        
        
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
    part->get("NEW",partprops_);
    part->set("OLD",partprops_);
    return 0;
}

int IncompInvisc::calcPressure(Particle* part) {
    //set properties to those which apparently approximate water
    //renormalize back to 1.
    int B = 1;   //this should be changed so the parameters are not set every time
    int gamma = 7;
    Properties props;
    part->get("OLD",props);
    props.pressure = B * (pow(props.density,gamma)-1.);
    part->set("OLD",props);
    return 0;
}
