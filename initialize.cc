#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


include "initialize.h"
include "particle.h"

//File to load particle locations


bool initialize(const std::string& filename, Particle** particles) {

    FILE* finput;
	finput = fopen(filename.c_str(),"r");

    if (fss==NULL){
        cout << "error, didn't load file" << endl;
        exit(1);
    }
    
    fscanf(finput,"%f",&NParticlesf_);
    NParticles_ = int(NParticlesf_);
    
    
    double mass; // = 1.0;
    double visc; // = 2.0;
    double x1;
    double x2;
    double xdot1;
    double xdot2;
    double** x = new double*[2]; // Pointer to the pointers r1 and r2
    double** v = new double*[2]; // Pointer to the pointers v1 and v2
    
    
    for (i=0;i<NParticles_;i++){
        fscanf(finput, "%f %f %f %f %f %f %f",x[0],x[1],xdot[0],xdot[1],mass,density,visc);
        x[i] = &x1;
        x[i][1] = x2;
        v[i] = &xdot1;
        v[i][1] = xdot2;
        particles[i] = new Particle(i+1,x,xdot,mass,density,visc);
    }
    fclose(finput);
    return true;
}