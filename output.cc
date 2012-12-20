#include "output.h"

using namespace std;

void output(float t,Fluid *fluid){
  // this should write fluid_<t>.dat
  // which is a list of particle positions
  Properties props;
  int nparticles = fluid->getNParticles();
  Particle **particles = new Particle*[nparticles];
  particles = fluid->getParticles();

  // this is super ugly stuff to get the filename as above. FIX
  ofstream myfile;
  stringstream ss (stringstream::in | stringstream::out);
  ss << t;
  string fname = "fluid_";
  fname = fname + ss.str() + ".dat";
  myfile.open(fname.c_str());

  for(int i=0; i<nparticles; ++i){
    particles[i]->getProps("NEW",props);
    myfile << props.x << "\t" << props.y << endl;
  }

  myfile.close(fname);

    
}
