#pragma once
#include <vector>
#include "Simulation.h"
#include <raylib.h>

constexpr int screen_width = 800;
constexpr int screen_height = 600;

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