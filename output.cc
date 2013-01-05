#include "output.h"

using namespace std;

void output(double t,Fluid *fluid){
  // this should write fluid_<t>.dat
  // which is a list of particle positions
  Properties props;
  int nparticles = fluid->getNParticles();
  Particle **particles = new Particle*[nparticles];
  fluid->getParticles(particles);

  // get the file name in the proper format
  ofstream myfile;
  stringstream ss (stringstream::in | stringstream::out);
  ss << t;
  string fname = "fluid_";
  fname = fname + ss.str() + ".dat";
  char *fnamechar = new char [fname.size()+1];
  strcpy(fnamechar,fname.c_str());

  ofstream file;
  file.open(fnamechar);

  // not sure we need headers
  // should we also include the particle labels??
  file << "x\ty" << endl;
      std::string NEW = "NEW";
  for(int i=0; i<nparticles; ++i){
    particles[i]->get("OLD",props); //this line seg faults...why?
    file << props.x << "\t" << props.y << endl;
  }

  file.close();
  delete particles;
  delete fnamechar; 
}
