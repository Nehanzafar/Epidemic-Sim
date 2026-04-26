#pragma once
#include <vector>
#include "Agent.h"
#include "Simulation.h"

const int screen_width = 800;
const int screen_height = 600;

class Window
{
private:
    // Board attributes
    static const int COLS = screen_width / CELL_SIZE;
    static const int ROWS = screen_height / CELL_SIZE;
    Simulation *sim;

    
public:
    Window();
    // void Run(std::vector<Agent>);
    void Run(std::vector<Agent> a);
};