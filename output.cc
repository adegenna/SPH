#include "output.h"

using namespace std;

<<<<<<< HEAD
void output(float t,Fluid *fluid){
  // this should write fluid_<t>.dat
  // which is a list of particle positions
  Properties props;
  int nparticles = fluid->getNParticles();
  Particle **particles = new Particle*[nparticles];
  particles = fluid->getParticles();

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
  myfile << "x\ty" << endl;
  for(int i=0; i<nparticles; ++i){
    particles[i]->get("NEW",props);
    myfile << props.x << "\t" << props.y << endl;
  }

  file.close();

  delete [] fnamechar;
}
