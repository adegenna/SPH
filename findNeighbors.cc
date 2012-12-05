#include "findNeighbors.h"

void findNeighbors(Particle *particles){
    for(int i=0; i<NUMPARTICLES; ++i){
        for(int j=i; j<NUMPARTICLES; ++j){
            // calculate some distances
            // add particle j to the neighbors of i
            // add particle i to the neighbors of j
        }
    }
}
