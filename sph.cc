/**
 *  \file
 *  
 *  \brief Driver program for smoothed particle hydrodynamics solver.
 * */
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <boost/shared_ptr.hpp>

#include "fluid.h"
#include "initialize.h"
#include "incompinvisc.h"
#include "incompvisc.h"
#include "gaussiankernel.h"
#include "splinekernel.h"
#include "euler.h"
#include "eulermod.h"
#include "predictorcorrector.h"
#include "output.h"

using namespace std;

/// Usage: main <initialFile> <boundaryFile(OPTIONAL)> <tFinal> <timestep>
int main(int argc, char** argv){
    string initFile, boundaryFile, kerneltype, integtype;
    double tFinal;
    double dt;
    if(argc == 6) {
      initFile = argv[1];
      tFinal = atof(argv[2]);
      dt = atof(argv[3]);
      integtype = argv[4];
      kerneltype = argv[5];
    }
    else if(argc == 7) {
      initFile = argv[1];
      tFinal = atof(argv[3]);
        dt = atof(argv[4]);
      boundaryFile = argv[2];
      integtype = argv[5];
      kerneltype = argv[6];
    }
    else{
        cout << "USAGE: " << argv[0] << " <initFile> <boundaryFile(OPTIONAL)> "
          "<tFinal> <timestep> <integrator> <kernel>" << endl;
        return 1;
    }

    const double smoothinglength = 1;

    int nparticles;
    int nboundaries;
    // read in number of particles, so that fluid can be initialized
    getNparticles(initFile,boundaryFile, nparticles,nboundaries);


    boost::shared_ptr<Kernel> myKer;
    
    if (kerneltype=="spline"){
        myKer.reset(new SplineKernel(smoothinglength));
    }
    else if (kerneltype=="gaussian"){
        myKer.reset(new GaussianKernel(smoothinglength));
    }
    else{
      cout << "Invalid kernel. Options are spline and gaussian" <<endl;
    }
    // initialize fluid, so that initialize will work:
    Fluid fluid(*myKer, nparticles, nboundaries, smoothinglength);
    
    // initializes the fluid from file
    initialize(initFile,boundaryFile,fluid,nparticles,nboundaries);
    
    boost::shared_ptr<Physics> physics(new IncompVisc(1.,0.1,3000.,7.,1000.,0.3,0.01));

    boost::shared_ptr<Integrator> integrator;
    if (integtype=="euler"){
      integrator.reset(new Euler(dt, fluid, *physics));
    }
    else if (integtype=="pc"){
      integrator.reset(new PredictorCorrector(dt, fluid, *physics));
    }
    else if (integtype=="eulermod"){
      integrator.reset(new Eulermod(dt, fluid, *physics));
    }
    else{
      cout << "Invalid integrator. Options are euler, pc, eulermod." << endl;
      return -1;
    }

    Output output("fluid.dat");
    int outsteps = floor(0.1/dt);
    
    double t = 0;
    for (size_t i = 0; t < tFinal; ++i)
    {
      cout << "t = " << t << endl;

      fluid.findNeighbors();

      integrator->step();

      if (i % outsteps == 0) // output every outsteps timesteps
        output.write(t, fluid);

      fluid.resetNeighbors();  // Need to reset after each time step

      t += dt;
    }

    return 0;
}
/**
 * \mainpage
 *
 * sph is a smoothed particle hydrodynamics solver. This is a Langrangian, i.e.,
 * not a fixed grid, solver which tracks particles and their properties instead
 * of properties at fixed grid spaces. This is useful for investigating free 
 * surface problems and mixing of fluids with different properties.
 *
 * The driver program is sph.cc. Usage: sph <initFile> <boundaryFile(OPTIONAL)> <tFinal> <timestep> <integrator> <kernel>
 *
 * Associated with sph is tests.cc, which is the driver program for testing 
 * classes and structs used by sph.
 *
 * Usage: tests
 *
 * <br /> <br /> <br />
 *
 * Code developed by Scott Dawson, Anthony DeGennaro, Imene Goumiri, and Kevin
 * Nowland as a final project for Princeton University course APC 524: Software 
 * Engineering for Scientific Computiattion during the Fall of 2012. 
 */
