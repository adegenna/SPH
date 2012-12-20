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
    const double smoothinglength = 20.;
    const string initFile = argv[1];
    const float tFinal = atof(argv[2]);

    int nparticles = 3;  //this shouldn't be hard coded,
    
    
    Fluid *fluid;
    Kernel *myKer;
    myKer = new SplineKernel(smoothinglength);
    //myKer = new GaussianKernel(smoothinglength);
    
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
      output("output.dat",fluid);  //moved output in here so outputs every timestep
      t = t + dt;
    }
<<<<<<< HEAD

    output(t,fluid);
=======
    
>>>>>>> 0af4adba39da15a80ebcf257ef63ea4504c00218

    delete integrator;
    delete physics;
    delete fluid;
  //  delete myKer;
    return 0;
}
