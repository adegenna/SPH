#include "timestep.h"

timestep(Particle *particles, float t, const float dt){
    findNeighbors(particles);
    for(int i=0; i < NUMPARTICLES; ++i){
        updateDensity(particle);
        updateVelocity(particle);
    }
    updateAll(particles);
    t = t + dt;
}
