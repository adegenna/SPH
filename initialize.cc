#include "initialize.h"

//File to load particle locations

using namespace std;

bool getNparticles(const std::string& filename, int& nparticles) {
    FILE* finput;
    finput = fopen(filename.c_str(),"r");
    if (finput==NULL){
        cout << "error, didn't load file" << endl;
        exit(1);
    }
    float nparticlesf_;
    fscanf(finput,"%f",&nparticlesf_);
    nparticles = int(nparticlesf_);
    fclose(finput);
    return true;
}

bool initialize(const std::string& filename, Fluid *fluid, int& nparticles) {
    FILE* finput;
	  finput = fopen(filename.c_str(),"r");
    if (finput==NULL){
        cout << "error, didn't load file" << endl;
        exit(1);
      }
    float nparticlesf_;
    fscanf(finput,"%f",&nparticlesf_);
    nparticles = int(nparticlesf_);
    Properties initProps;
    //Allocate sufficient memory for particles
    //particles = (Particle**) malloc(NParticles);
    
    for (int i=0;i<nparticles;i++){
        fscanf(finput, "%lf %lf %lf %lf %lf %lf %lf",&initProps.x,&initProps.y,
               &initProps.u,&initProps.v,
               &initProps.mass,&initProps.density,&initProps.visc);
        fluid->addParticle(i,initProps);
      //  particles[i] = new Particle(i+1,initProps);
        
    }
    fclose(finput);
    return true;
}
