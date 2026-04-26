#pragma once

#include "Agent.h"

class Grid
{
private:
    Agent ***grid;
    int ROWS;
    int COLS;

public:
    Grid(int, int);
    void clear();
    Agent **operator[](int i);
    ~Grid();
};
