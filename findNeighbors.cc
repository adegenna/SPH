#include "findNeighbors.h"

void findNeighbors(Particle *particles){
    float dist;
    for(int i=0; i<NUMPARTICLES; ++i){
        for(int j=i; j<NUMPARTICLES; ++j){
            // calculate some distances
            dist = particles[i]->Distance(particles[j]->GetLocation);
            if(dist < SMOOTHINGLENGTH){
                // add neighbor
                particles[i]->AddNeighbor(particles[j]);
                particles[j]->AddNeighbor(particles[i]);
            }
        }
    }
}
