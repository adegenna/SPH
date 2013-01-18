/**
 * \file
 *
 * \brief Class which outputs current fluid state
 */
#include <fstream>

class Fluid;

/// Class to build output file for fluid state
class Output
{
  public:
    /// create file to hold fluid properties
    Output(const std::string& filename);
    /// write fluid properties
    void write(double t, //!< current time
        const Fluid& fluid);  //!< fluid

  private:
    std::ofstream file_;
};
