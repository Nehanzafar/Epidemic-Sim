#pragma once
#include <vector>
#include "Simulation.h"
#include <raylib.h>
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