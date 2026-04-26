#include "Grid.h"

Grid::Grid(int ROWS, int COLS)
{
    grid = new Agent *[ROWS];
    this->ROWS = ROWS;
    this->COLS = COLS;

    for (int i = 0; i < ROWS; i++)
    {
        grid[i] = new Agent *[COLS];
    }
}

void Grid::clear()
{
    // 1. Wipe the grid clean
    for (int x = 0; x < COLS; x++)
    {
        for (int y = 0; y < ROWS; y++)
        {
            grid[x][y] = nullptr;
        }
    }
}


Agent **Grid::operator[](int i)
{
    return grid[i];
}

Grid::~Grid()
{
    for (int x = 0; x < COLS; x++)
    {
        for (int y = 0; y < ROWS; y++)
        {
            delete grid[x][y];
        }
    }
}