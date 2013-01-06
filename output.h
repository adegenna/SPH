#include <fstream>

class Fluid;


class Output
{
public:
    Output(const std::string& filename);

    void write(double t, const Fluid& fluid);

private:
    std::ofstream file_;
};
