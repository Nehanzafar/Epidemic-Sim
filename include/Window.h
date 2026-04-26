#pragma once
#include <vector>

#include "Agent.h"

const int screen_width = 800;
const int screen_height = 600;

class Window
{
private:
    // Board attributes
    static const int COLS = GetScreenWidth() / CELL_SIZE;
    static const int ROWS = GetScreenHeight() / CELL_SIZE;


public:
    Window();
    // void Run(std::vector<Agent>);
    void Run(std::vector<Agent> a);
};