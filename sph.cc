#include <stdlib.h>
#include <iostream>
#include <string>

#include "fluid.h"
#include "initialize.h"
#include "incompinvisc.h"
#include "kernel.h"
#include "gaussiankernel.h"
#include "splinekernel.h"
#include "euler.h" // <-- does not exist
#include "output.h" // <-- does not exist

using namespace std;

int main(int argc, char** argv){
    // what is the usage? main <initialFile> <tFinal> ?
    if(argc != 3){
        cout << "USAGE: " << argv[0] << " <initFile> <tFinal>" << endl;
        exit(1);
    }

    const float dt = 0.1; // <-- make into input??
    const double smoothinglength = 1.5;
    const string initFile = argv[1];
    const float tFinal = atof(argv[2]);

    //int nparticles = 15;  //this shouldn't be hard coded,
    int nparticles;
    
    //read in number of particles, so that fluid can be initialized
    getNparticles(initFile, nparticles);
    
    string kerneltype = "Spline";
    
    Fluid *fluid;
    Kernel *myKer;
    
    if (kerneltype=="Spline"){
        myKer = new SplineKernel(smoothinglength);
    }
    else if (kerneltype=="Gaussian"){
        myKer = new GaussianKernel(smoothinglength);
    }
    //initialize fluid, so that initialize will work:
    fluid = new Fluid(myKer,nparticles,smoothinglength);
    
    initialize(initFile,fluid,nparticles); // initializes the fluid from file
    
    Physics *physics;
    Integrator *integrator;

    physics = new IncompInvisc();
    integrator = new Euler(dt,fluid,physics);
    
    float t = 0;
    while(t < tFinal){
      fluid->findNeighbors();
      integrator->step();
      t = t + dt;
      output(t,fluid);
      fluid->resetNeighbors();  // Need to reset after each time step  
    }

    delete integrator;
    delete physics;
    delete fluid;
  //  delete myKer;
    return 0;
}
