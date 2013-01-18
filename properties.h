/**
 * \file
 *
 * \brief Struct to hold a particle's physical properties
 */
#ifndef PROPERTIES_H_
#define PROPERTIES_H_

/// struct holding physical particle properties
struct Properties
{
    double x;         //!< x position
    double y;         //!< y position
    double u;         //!< x velocity
    double v;         //!< y velocity
    double density;   //!< density at particle
    double mass;      //!< particle mass
    double pressure;  //!< pressure at particle
    double energy;    //!< particle viscosity
};

#endif  // PROPERTIES_H_
