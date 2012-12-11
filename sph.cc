#include <stdlib.h>
#include <iostream>
#include <string>

#include "particle.h"
#include "kernel.h"
#include "initialize.h"
#include "Fluid.h"
#include "Physics.h"
#include "output.h"

using namespace std;

int main(int argc, char* argv[]){
    // what is the usage? main <initialFile> <tFinal> ?
    if(argc != 3){
        cout << "USAGE: " << argv[0] << " <initFile> <tFinal>" << endl;
        exit(1);
    }

    const float dt = 0.1; // <-- make into input??
    const string initFile = argv[1];
    const float tFinal = atof(argv[2]);

    Fluid *fluid;
    int nparticles;
    initialize(initFile,*fluid,nparticles); // initializes the fluid from file

    Physics *physics;
    Integrator *integrator;

    physics = new IncompInvisc();
    integrator = new Euler(dt,*physics);
        
    float t = 0;
    while(t < tFinal){
      integrator->Step(t,fluid);
      // output??
      t = t + dt;
    }

    delete integrator;
    delete physics;
    delete fluid;
    return 0;
}
