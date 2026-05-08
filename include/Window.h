#pragma once
#include <vector>
#include "Simulation.h"
#include <raylib.h>
#include <iostream>

constexpr int screen_width = 1800;
constexpr int screen_height = 900;
const int tick = 30;

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