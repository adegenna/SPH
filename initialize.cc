include "initialize.h"
//File to load particle locations


bool initialize(const std::string& filename, particle* particles) {

    FILE* finput;
	Finput = fopen(filename.c_str(),"r");

    if (fss==NULL){
        cout << "error, didn't load file" << endl;
        exit(1);
    }
    
    fscanf(finput,"%f",&NParticlesf_);
    NParticles_ = int(NParticlesf_);
    
    
    for (i=0;i<NParticles_;i++){
        fscanf(finput, "%f %f %f %f %f %f %f",x[0],x[1],xdot[0],xdot[1],mass,density,visc);
    	particles[i] = new Particle(i+1,x,xdot,mass,density,visc);
    }
    fclose(finput);
    return true;
}