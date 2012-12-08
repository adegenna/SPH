#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "particle.h"
#include "initialize.h"

//File to load particle locations

using namespace std;

bool initialize(const std::string& filename, Particle** particles) {

    FILE* finput;
	finput = fopen(filename.c_str(),"r");
    if (finput==NULL){
        cout << "error, didn't load file" << endl;
        exit(1);
    }
    float NParticlesf_;
    int NParticles;
    fscanf(finput,"%f",&NParticlesf_);
    NParticles = int(NParticlesf_);
    double mass;
    double density;
    double visc;
    double x1;
    double x2;
    double xdot1;
    double xdot2;
    double** x = new double*[2];
    double** v = new double*[2];
    
    //Allocate sufficient memory for particles
    //particles = (Particle**) malloc(NParticles);
    
    for (int i=0;i<NParticles;i++){
        fscanf(finput, "%lf %lf %lf %lf %lf %lf",&x1,&x2,&xdot1,&xdot2,&mass,&density,&visc); //also put in density
        cout <<"here6" <<endl;
        x[i] = &x1;
        x[i][1] = x2;
        v[i] = &xdot1;
        v[i][1] = xdot2;
        particles[i] = new Particle(i+1,x[i],v[i],mass,density,visc);
    }
    fclose(finput);
    return true;
}