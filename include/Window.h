#pragma once
#include <vector>
#include "Agent.h"
#include "Simulation.h"
class Window
{
private:
    // Board attributes
    Simulation *sim;

public:
    Window();
    // void Run(std::vector<Agent>);
    void Run();
};