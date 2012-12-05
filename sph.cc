#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <string>

#include <particle.h>
#include <kernel.h>
#include <timestep.h>
#include <initialize.h>
#include <output.h>

using namespace std;

int main(int argc, char* argv[]){
    // what is the usage? main <initialFile> <tFinal> ?
    if(argc != 3){
        cout << "USAGE: " << argv[0] << " <initFile> <tFinal>" << endl;
        exit(1);
    }

    const string initFile = argv[1];
    const float tFinal = atof(argv[2]);

    Particle *particles;
    initialize(initFile,particles);
    
    float t = 0;
    while(t < tFinal){
        timestep(particles,t,dt); // timestep had better update t
    }

    return 0;
}
