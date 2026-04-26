#pragma once
#include <vector>
#include <random>
#include "Agent.h"
#include "Disease.h"
#include "Window.h"
#include <iostream>
#include "raylib.h"
class Simulation
{
private:
    // current population
    std::vector<Agent> population;
    std::vector<Disease*> disease_list;
    int time;
    int total_time_the_simulation_lasts;
    Disease_attributes starting_disease_attributes;

    int CELL_SIZE = 5;
    std::vector<Agent *> grid[COLS][ROWS];


    
public:
    Simulation(int, int, Disease_attributes);
    void interaction(Agent &sick, Agent &other); // infection interaction
    void run_simulation();
    void pause_simulation();
    void stop_simulation();
    void update_grid();
    void handle_collision();
    void run_step();

};