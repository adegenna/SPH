#include "initialize.h"

//File to load particle locations

#include <iostream>
#include <cmath>
#include "fluid.h"
#include "properties.h"
#include "kvector.h"


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


bool initialize(const std::string& filename, const std::string& boundaryFile, Fluid& fluid, int& nparticles, int& nboundaries) {
    
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
    
    for (int i=0;i<nparticles;++i){
        fscanf(finput, "%lf %lf %lf %lf %lf %lf %lf",&initProps.x,&initProps.y,
               &initProps.u,&initProps.v,
               &initProps.mass,&initProps.density,&initProps.visc);
        fluid.addParticle(i,initProps);
        
//        cout << "x = " << initProps.x <<endl;
//        cout << "y = " << initProps.y <<endl;
//        cout << "u = " << initProps.u <<endl;
//        cout << "v = " << initProps.u <<endl;
//        cout << "mass = " << initProps.mass <<endl;
//        cout << "density = " << initProps.mass <<endl;
//        cout << "visc = " << initProps.visc <<endl;
    }
    fclose(finput);

    if (nboundaries !=0){
      FILE* fboundary;
      fboundary = fopen(boundaryFile.c_str(),"r");
      float nboundariesf_;
      fscanf(fboundary,"%f",&nboundariesf_);
      nboundaries = int(nboundariesf_);
      for (int i=0; i<nboundaries; ++i) {
          fscanf(fboundary, "%lf %lf %lf %lf %lf %lf %lf",&initProps.x,&initProps.y,
               &initProps.u,&initProps.v,
               &initProps.mass,&initProps.density,&initProps.visc
               );
        fluid.addBoundary(i,initProps);
      }
      fclose(fboundary);
    }
    return true;
}

void rectangleParticles(Kvector p0, Kvector p1, double density, double smoothinglength, Fluid& fluid) {
  p0.x += 0.5*smoothinglength; p0.y += 0.5*smoothinglength;
  p1.x -= 0.5*smoothinglength; p1.y -= 0.5*smoothinglength;
  int xsteps = 1 + (int) floor((p1.x-p0.x)/smoothinglength);
  int ysteps = 1 + (int) floor((p1.y-p0.y)/smoothinglength);
  int counter = 0;
  Properties props;
  double mass = density*pow(smoothinglength,2);
  for(int i=0; i<xsteps; i++) {
    for(int j=0; j<ysteps; j++) {
      props.x = p0.x + i*smoothinglength;
      props.y = p0.y + j*smoothinglength;
      props.u = 0; props.v = 0; props.mass = mass; props.density = 0;
      props.visc = 0;
      fluid.addParticle(counter,props);
      counter += 1;
    }
  }
}
