#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <raylib.h>
#include <sstream>
#include <iomanip>
// our own code
#include "Agent.h"

struct info
{
    int ROWS;
    int COLS;
};
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
    void display();
    info get_grid_info();
    ~Grid();
};

class Simulation
{
private:
    // current population
    std::vector<Agent *> population;
    std::vector<Disease *> disease_list;
    int time;
    Disease_attributes starting_disease_attributes;

    // Constant attributes
    const int screen_width;
    const int screen_height;
    const int CELL_SIZE;
    const int tick;
    Grid *grid;
    std::mt19937 gen;

public:
    Simulation(int starting_population, Disease_attributes d = {0, 0, 0, 0}, const int screen_width = 300, const int screen_height = 300, const int CELL_SIZE = 5);

    void interaction(Agent *sick, Agent *other); // infection interaction
    void run_simulation();
    void pause_simulation();
    void stop_simulation();
    void update_grid();
    void draw();
    void run_step();
    void draw_grid();
    int population_count();
    ~Simulation();
};
