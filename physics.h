#ifndef PHYSICS_H_
#define PHYSICS_H_

class Fluid;
class Particle;
class Kernel;
struct Properties;

class Physics {
 public:
  virtual ~Physics() {}

  // general update function
  virtual int rhs(Fluid& fluid, Particle& part, Kernel& myKer,Properties& fx) = 0;
  virtual int update(Particle& part) = 0;
  virtual int calcPressure(Particle& part) = 0;
};

#endif  // PHYSICS_H_
