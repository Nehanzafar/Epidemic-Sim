#pragma once
#include <vector>
#include "Agent.h"
#include "Disease.h"
class Simulation
{
private:
    // current population
    std::vector<Agent> population;
    int time;
    int total_time_the_simulation_lasts;
    Disease_attributes starting_disease_attributes;

public:
    Simulation(int, int , Disease_attributes);
    void run_simulation();
    void pause_simulation();
    void stop_simulation();
    void run_step();
};