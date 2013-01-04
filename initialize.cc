#include "initialize.h"

//File to load particle locations

using namespace std;


bool getNparticles(const std::string& filename, const std::string& boundaryFile, int& nparticles, int& nboundaries) {
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
    FILE* fboundary;
    fboundary = fopen(boundaryFile.c_str(),"r");
    if (fboundary==NULL){
        nboundaries=0;
    }
    else{
        float nboundariesf_;
        fscanf(fboundary,"%f",&nboundariesf_);
        nboundaries = int(nboundariesf_);
    }
    
    return true;
}


bool initialize(const std::string& filename, const std::string& boundaryFile, Fluid *fluid, int& nparticles, int& nboundaries) {
    
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
    
    //cout <<"Nparticles = " << nparticles <<endl;
    
    //Allocate sufficient memory for particles
    //particles = (Particle**) malloc(NParticles);
    
    for (int i=0;i<nparticles;i++){
        fscanf(finput, "%lf %lf %lf %lf %lf %lf %lf",&initProps.x,&initProps.y,
               &initProps.u,&initProps.v,
               &initProps.mass,&initProps.density,&initProps.visc);
        fluid->addParticle(i,initProps);
        
      //  cout << "x = " << initProps.x <<endl;
      //  cout << "u = " << initProps.u <<endl;
    }
    fclose(finput);

    if (nboundaries !=0){
      FILE* fboundary;
      fboundary = fopen(boundaryFile.c_str(),"r");
      float nboundariesf_;
      fscanf(fboundary,"%f",&nboundariesf_);
      nboundaries = int(nboundariesf_);
      for (int i=0; i<nboundaries; i++) {
          fscanf(fboundary, "%lf %lf %lf %lf %lf %lf %lf",&initProps.x,&initProps.y,
               &initProps.u,&initProps.v,
               &initProps.mass,&initProps.density,&initProps.visc
               );
        fluid->addBoundary(i,initProps);
      }
      fclose(fboundary);
    }
    return true;
}
