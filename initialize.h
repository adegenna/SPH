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

bool initialize(std::string& filename, std::string& boundaryFile, Fluid *fluid, int& Nparticles, int nboundaries);
