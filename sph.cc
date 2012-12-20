#include <stdlib.h>
#include <iostream>
#include <string>

#include "fluid.h"
#include "initialize.h"
#include "incompinvisc.h"
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
    const string initFile = argv[1];
    const float tFinal = atof(argv[2]);

    Fluid *fluid;
    int nparticles;
    initialize(initFile,fluid,nparticles); // initializes the fluid from file

    Physics *physics;
    Integrator *integrator;

    physics = new IncompInvisc();
    integrator = new Euler(dt,fluid,physics);
        
    float t = 0;
    while(t < tFinal){
      integrator->Step(fluid);
      t = t + dt;
    }

    output(fluid);

    delete integrator;
    delete physics;
    delete fluid;
    return 0;
}
