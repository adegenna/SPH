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

    const double smoothinglength = 1;


    //int nparticles = 3;  //this shouldn't be hard coded,
    int nparticles;
    int nboundaries;
    //read in number of particles, so that fluid can be initialized
    getNparticles(initFile,boundaryFile, nparticles,nboundaries);
    //int nparticles = 15;  //this shouldn't be hard coded,
    
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
    fluid = new Fluid(myKer,nparticles,nboundaries,smoothinglength);
    
    string inputtype = "IndivParts";
    
    if (inputtype == "IndivParts") {
        initialize(initFile,boundaryFile,fluid,nparticles,nboundaries); // initializes the fluid from file
    }
    else if (inputtype == "RectangleParticles" ) {
        //
    }
        
    Physics *physics;
    Integrator *integrator;

    physics = new IncompInvisc();
    integrator = new Euler(dt,fluid,physics);

    Output output("fluid.dat");
    
    double t = 0;
    int counter = 0;
    while(t < tFinal){
        cout << "t = " << t <<endl;
      fluid->findNeighbors();
       // cout <<"found neighbors"<<endl;
      integrator->step();
       // cout <<"stepped"<<endl;
      if (counter%10 == 0){  //output every 10 timesteps
        output.write(t, *fluid);
      }
      fluid->resetNeighbors();  // Need to reset after each time step  
      counter += 1;
      t += dt;
    }

    delete integrator;
    delete physics;
    delete fluid;
    delete myKer;
    return 0;
}
