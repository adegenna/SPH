#ifndef INITIALIZE_H_
#define INITIALIZE_H_

#include <string>
#include <stdio.h>

class Fluid;
struct Kvector;

bool getNparticles(const std::string& filename, const std::string& boundaryFile, int& nparticles,int& nboundaries);

bool initialize(const std::string& filename, const std::string& boundaryFile, Fluid& fluid, int& nparticles, int& nboundaries);

void rectangleParticles(Kvector p0, Kvector p1, double density, double smoothinglength, Fluid& fluid);

#endif // INITIALIZE_H_
