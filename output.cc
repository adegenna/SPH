#include "output.h"

using namespace std;

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
}
