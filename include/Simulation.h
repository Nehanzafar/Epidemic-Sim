#pragma once
#include <vector>
#include <random>
#include "Agent.h"
#include "Disease.h"
#include <iostream>
#include <raylib.h>
#include "Grid.h"

constexpr int screen_width = 800;
constexpr int screen_height = 600;
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
    Simulation(int, int, Disease_attributes);
    void interaction(Agent &sick, Agent &other); // infection interaction
    void run_simulation();
    void pause_simulation();
    void stop_simulation();
    void update_grid();
    void draw();
    void handle_collision(Agent *agent);
    void run_step();
};