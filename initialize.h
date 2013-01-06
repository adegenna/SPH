/**
 * \file
 *
 * \brief Code for initialization of fluid and boundary from input files
 */
#ifndef INITIALIZE_H_
#define INITIALIZE_H_

#include <string>
#include <stdio.h>

class Fluid;
struct Kvector;

/// find the number of particles and boundary particles from input files
bool getNparticles(const std::string& filename, //!< file with initial particle properties
    const std::string& boundaryFile,            //!< file with initial boundary particle properties
    int& nparticles,                            //!< address for number of particles
    int& nboundaries                            //!< address for number of boundary particles
    );

/// initializes fluid from input files
bool initialize(const std::string& filename,  //!< file with initial particle properties
    const std::string& boundaryFile,          //!< file with initial boundary particle properties
    Fluid& fluid,                             //!< fluid to be initialized
    int& nparticles,                          //!< address for number of particles
    int& nboundaries                          //!< address for number of boundary particles
    );

/// alternate initialization of fluid in a rectangle
void rectangleParticles(Kvector p0, //!< bottom left corner of fluid rectangle
    Kvector p1,                     //!< top right corner of fluid rectangle
    double density,                 //!< initial density of particles
    double smoothinglength,         //!< smoothing length
    Fluid& fluid                    //!< fluid to be initialized
    );

#endif // INITIALIZE_H_
