//#ifndef INITIALIZE_H_
//#define INITIALIZE_H_
#include "particle.h"
#include "properties.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "fluid.h"
#include "kvector.h"

bool getNparticles(const std::string& filename, const std::string& boundaryFile, int& nparticles,int& nboundaries);
bool initialize(const std::string& filename, const std::string& boundaryFile, Fluid *fluid, int& nparticles, int& nboundaries);

void rectangleParticles(Kvector p0, Kvector p1, double density, double smoothinglength, Fluid *fluid);
