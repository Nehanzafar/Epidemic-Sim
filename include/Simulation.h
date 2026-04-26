#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <raylib.h>
// our own code
#include "Agent.h"

constexpr int screen_width = 800;
constexpr int screen_height = 600;

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

class Simulation
{
private:
    // current population
    std::vector<Agent *> population;
    std::vector<Disease *> disease_list;
    int time;
    int total_time_the_simulation_lasts;
    Disease_attributes starting_disease_attributes;

    const int CELL_SIZE = 5;
    const int COLS = screen_width / CELL_SIZE;
    const int ROWS = screen_height / CELL_SIZE;
    Grid *grid;

public:
    Simulation(int amount_of_time, int starting_population, Disease_attributes d = {0, 0, 0, 0});

    void interaction(Agent &sick, Agent &other); // infection interaction
    void run_simulation();
    void pause_simulation();
    void stop_simulation();
    void update_grid();
    void draw();
    void handle_collision(Agent *agent);
    void run_step();
};
