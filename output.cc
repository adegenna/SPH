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
=======
void output(const std::string& filename, Fluid *fluid ){
    FILE* outfile = fopen(filename.c_str(),"a+");
    
    Properties props;
    int nparticles = fluid->getNParticles();
    Particle** particles = new Particle*[nparticles];
    particles = fluid->getParticles();
    for(int i=0; i<nparticles; ++i){
        particles[i]->get("OLD", props);
        
        //should also probably output time, but for now:
  		fprintf(outfile,"%d %.5e %.5e %.5e %.5e %.5e %.5e\n",i,props.x,props.y,props.u,props.v,props.density,props.pressure);
    }
>>>>>>> 0af4adba39da15a80ebcf257ef63ea4504c00218
}
