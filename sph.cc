/**
 *  \file
 *  
 *  \brief Driver program for smoothed particle hydrodynamics solver.
 * */
#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>

#include "fluid.h"
#include "initialize.h"
#include "incompinvisc.h"
#include "gaussiankernel.h"
#include "splinekernel.h"
#include "euler.h"
#include "output.h"

using namespace std;

/// Usage: main <initialFile> <boundaryFile(OPTIONAL)> <tFinal> <timestep>
int main(int argc, char** argv){
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
        return 1;
    }

    const double smoothinglength = 1;


    int nparticles;
    int nboundaries;
    //read in number of particles, so that fluid can be initialized
    getNparticles(initFile,boundaryFile, nparticles,nboundaries);

    const string kerneltype = "Spline";

    boost::shared_ptr<Kernel> myKer;
    
    if (kerneltype=="Spline"){
        myKer.reset(new SplineKernel(smoothinglength));
    }
    else if (kerneltype=="Gaussian"){
        myKer.reset(new GaussianKernel(smoothinglength));
    }
    //initialize fluid, so that initialize will work:
    Fluid fluid(*myKer, nparticles, nboundaries, smoothinglength);
    
    const string inputtype = "IndivParts";
    
    if (inputtype == "IndivParts") {
        initialize(initFile,boundaryFile,fluid,nparticles,nboundaries); // initializes the fluid from file
    }
    else if (inputtype == "RectangleParticles" ) {
        //
    }
        
    boost::shared_ptr<Physics> physics(new IncompInvisc());
    boost::shared_ptr<Integrator> integrator(new Euler(dt, fluid, *physics));

    Output output("fluid.dat");
    
    double t = 0;
    for (size_t i = 0; t < tFinal; ++i)
    {
      cout << "t = " << t << endl;

      fluid.findNeighbors();

      integrator->step();

      if (i % 10 == 0) //output every 10 timesteps
        output.write(t, fluid);

      fluid.resetNeighbors();  // Need to reset after each time step

      t += dt;
    }

    return 0;
}
/**
 * \mainpage
 *
 * sph is a smoothed particle hydrodynamics solver. The driver program is 
 * sph.cc.
 *
 * Associated with sph is tests.cc, which is the driver program for testing 
 * classes and structs used by sph.
 */
