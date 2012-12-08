#ifndef INCOMPINVISC_H_
#define INCOMPINVISC_H_

#include "Kernel.h"
#include <math.h>
#include "particle.h"

#include "proerties.h"
// Forced Duffing oscillator:
//   \dot x = y
//   \dot y = x - x^3 - delta * y + gamma * cos(omega t)
class IncompInvisc : public Model {
 public:
  IncompInvisc();
  ~IncompInvisc();
  int update(Particle* part);
 
 private:
//  const double delta_;                        // damping constant
//  const double gamma_;                        // amplitude of forcing
//  const double omega_;                        // frequency of forcing
//  static const int kDimen = 2;
};

#endif  // INCOMPINVISC_H_
