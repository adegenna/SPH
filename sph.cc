#include <stdlib.h>
#include <iostream>
#include <string>

#include "fluid.h"
#include "initialize.h"
#include "incompinvisc.h"
#include "kernel.h"
#include "gaussiankernel.h"
#include "splinekernel.h"
#include "euler.h"
#include "output.h"

using namespace std;

int main(int argc, char** argv){
    // Usage: main <initialFile> <boundaryFile(OPTIONAL)> <tFinal> <timestep>
    string initFile, boundaryFile;
    double tFinal;
    double dt;
    if(argc == 4) {
      initFile = argv[1];
      tFinal = atof(argv[2]);
      dt = atof(argv[3]);
    }
    else if(argc == 5) {
      initFile = argv[1];
      tFinal = atof(argv[3]);
        dt = atof(argv[4]);
      boundaryFile = argv[2];
    }
    else{
        cout << "USAGE: " << argv[0] << " <initFile> <boundaryFile(OPTIONAL)> <tFinal>  <timestep>" << endl;
        exit(1);
    }

    //const double dt = 0.1; // <-- make into input??
    const double smoothinglength = 1;


    //int nparticles = 3;  //this shouldn't be hard coded,
    int nparticles;
    int nboundaries;
    //read in number of particles, so that fluid can be initialized
    getNparticles(initFile,boundaryFile, nparticles,nboundaries);
    //int nparticles = 15;  //this shouldn't be hard coded,
    
    string kerneltype = "Gaussian";
    
    Fluid *fluid;
    Kernel *myKer;
    
    if (kerneltype=="Spline"){
        myKer = new SplineKernel(smoothinglength);
    }
    else if (kerneltype=="Gaussian"){
        myKer = new GaussianKernel(smoothinglength);
    }
    //initialize fluid, so that initialize will work:
    fluid = new Fluid(myKer,nparticles,nboundaries,smoothinglength);
    
    initialize(initFile,boundaryFile,fluid,nparticles,nboundaries); // initializes the fluid from file
    
    Physics *physics;
    Integrator *integrator;

    physics = new IncompInvisc();
    integrator = new Euler(dt,fluid,physics);
    
    double t = 0;
    while(t < tFinal){
        cout << "t =" << t <<endl;
      fluid->findNeighbors();
       // cout <<"found neighbors"<<endl;
      integrator->step();
       // cout <<"stepped"<<endl;
      t = t + dt;
      output(t,fluid);
      fluid->resetNeighbors();  // Need to reset after each time step  
    }

    delete integrator;
    delete physics;
    delete fluid;
    delete myKer;
    return 0;
}
