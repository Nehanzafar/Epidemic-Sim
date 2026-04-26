#include "Simulation.h"

int main()
{
    Simulation sim(20, 20, {0,0,0,0});
    std::cout << "Hello " << std::endl;
    sim.run_simulation();
}