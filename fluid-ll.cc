#include "fluid.h"

#include <cmath>
#include <map>
#include "particle.h"

using namespace std;


Fluid::Fluid(Kernel& kernel, size_t nparticles, size_t nboundaries, double smoothinglength) :
kernel_(kernel),
nparticles_(nparticles),
nboundaries_(nboundaries),
smoothinglength_(smoothinglength),
particles_(nparticles),
boundaries_(nboundaries)
{}

//should this just be addParticle(Properties props) ?
void Fluid::addParticle(int tag, const Properties& prop)
{
    particles_[tag].reset(new Particle(tag, nparticles_, nboundaries_,prop));
}

void Fluid::addBoundary(int tag, const Properties& prop)
{
    boundaries_[tag].reset(new Particle(tag, nparticles_, nboundaries_, prop));
}

void Fluid::findNeighbors(){
  // this is what we are changing to the linked list
  // maximum area needed for temporary grid
  double xmin, xmax, ymin, ymax;
  Properties props = particles_[0]->getOldProperties();
  xmin = props.x;
  xmax = props.x;
  ymin = props.y;
  ymax = props.y;
  for(int i=1; i<nparticles_; ++i){
    props = particles_[i]->getOldProperties();
    if(props.x < xmin){
      xmin = props.x;
    }
    if(props.x > xmax){
      xmax = props.x;
    }
    if(props.y < ymin){
      ymin = props.y;
    }
    if(props.y > ymax){
      ymax = props.y;
    }
  }
  
  // now we need to make the grid with spacing of smoothing length
  int nx = floor((xmax-xmin)/smoothinglength_)+1;
  int ny = floor((ymax-ymin)/smoothinglength_)+1;

  std::multimap<int, int>grid;

  // we now have an nx by ny grid and we need to add particles to
  // the correct cells
  int nxcell, nycell;
  for(int i=0; i<nparticles_; ++i){
    props = particles_[i]->getOldProperties();
    nxcell = floor((props.x - xmin)/smoothinglength_);
    nycell = floor((props.y - ymin)/smoothinglength_);
    grid.insert(std::pair<int,int>(nycell*nx+nxcell,particles_[i].getTag()));
  }

  // with all particles in the grid, we need to iterate through grid cells
  pair<multimap<int,int>::iterator, multimap<int,int>>::iterator> iter;
  for(int i=0; i<nx*ny; ++i){
    iter = grid.equal_range(i);
    for( multimap<int,int>::iterator it2 = iter.first; 
        it2 != iter.second; 
        ++it2 ){
      // start with a particle
      int tag = (*it2).second;
      // add particles from current cell
      for( multimap<int,int>::iterator it3 = iter.first;
            it3 != iter.second;
            ++it3){
        if((*it3).second != tag){
          particles_[tag]->addNeighbor(*particles_[(*it3).second]);
        }
      }
      // add particles from cell to left, if applicable
      if(i%nx != 0){
        for( multimap<int,int>::iterator it3 = iter.first-1;
            it3 != iter.second;
            ++it3){
          particles_[tag]->addNeighbor(*particles_[(*it3).second]);
        }
      }
      // add particles from cell to right, if applicable
      if((i+1)%nx != 0){
        for( multimap<int,int>::iterator it3 = iter.first+1;
            it3 != iter.second;
            ++it3){
          particles_[tag]->addNeighbor(*particles_[(*it3).second]);
        }
      }
      // add particles from cell below, if applicable
      if(i>=nx){
        for( multimap<int,int>::iterator it3 = iter.first-8;
            it3 != iter.second;
            ++it3){
          particles_[tag]->addNeighbor(*particles_[(*it3).second]);
        }
      }
      // add particles from cell above, if applicable
      if(i < nx*(ny-1)){
        for( multimap<int,int>::iterator it3 = iter.first+8;
            it3 != iter.second;
            ++it3){
          particles_[tag]->addNeighbor(*particles_[(*it3).second]);
        }
      }
      // add particles from bot left, if applicable
      if(i%nx != 0 && i>=nx){
        for( multimap<int,int>::iterator it3 = iter.first-9;
            it3 != iter.second;
            ++it3){
          particles_[tag]->addNeighbor(*particles_[(*it3).second]);
        }
      }
      // add particles from bot right, if applicable
      if((i+1)%nx !=0 && i>=nx){
        for( multimap<int,int>::iterator it3 = iter.first-7;
            it3 != iter.second;
            ++it3){
          particles_[tag]->addNeighbor(*particles_[(*it3).second]);
        }
      }
      // add particles from top left, if applicable
      if(i%nx != 0 && i<nx*(ny-1)){
        for( multimap<int,int>::iterator it3 = iter.first+7;
            it3 != iter.second;
            ++it3){
          particles_[tag]->addNeighbor(*particles_[(*it3).second]);
        }
      }
      // add particles from top right, if applicable
      if((i+1)%nx != 0 && i< nx*(ny-1)){
        for( multimap<int,int>::iterator it3 = iter.first+9;
            it3 != iter.second;
            ++it3){
          particles_[tag]->addNeighbor(*particles_[(*it3).second]);
        }
      }
    }
  }


  // not sure what to do about boundaries
  for(int i=0; i<nboundaries_; ++i) {
    const Properties propi = boundaries_[i]->getOldProperties();
    for(int j=0; j<nparticles_; ++j){
      const Properties propj = particles_[j]->getOldProperties();
      float dist = sqrt(pow(propi.x-propj.x,2)+pow(propi.y-propj.y,2));

//      int BN = particles_[j]->numberOfBoundaryNeighbors();

        //should this cutoff distance be larger?
      if(dist < 2.*smoothinglength_){
        particles_[j]->addBoundaryNeighbor(*boundaries_[i]);
      }
    }
  }
}

void Fluid::resetNeighbors(){
  for(int i=0; i<nparticles_; ++i){
    particles_[i]->deleteNeighbors();
  }
}

Kernel& Fluid::getKernel()
{
  return kernel_;
}

size_t Fluid::getNParticles() const
{
  return nparticles_;
}

size_t Fluid::getNBoundaries() const
{
  return nboundaries_;
}

Fluid::ParticleArray Fluid::getParticles() const
{
    return particles_;
}

Fluid::ParticleArray Fluid::getBoundaries() const
{
    return boundaries_;
}

void Fluid::resetParticles(const ParticleArray& newparticles)
{
    particles_ = newparticles;
}
