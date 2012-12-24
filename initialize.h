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

bool initialize(const std::string& filename, Fluid *fluid, int& Nparticles);
bool getNparticles(const std::string& filename, int& Nparticles);
