#pragma once
#include <vector>
#include "Agent.h"

class Window
{
private:
    // Board attributes
    static const int COLS = GetScreenWidth() / CELL_SIZE;
    static const int ROWS = GetScreenHeight() / CELL_SIZE;


public:
    Window();
    void Run(std::vector<Agent>);
};