#pragma once
#include <vector>

#include "Agent.h"

const int screen_width = 800;
const int screen_height = 600;

class Window
{
public:
    Window();
    // void Run(std::vector<Agent>);
    void Run(std::vector<Agent> a);
};