#include "Simulation.h"
#include "Agent.h"

Simulation::Simulation(int amount_of_time, int starting_population, Disease_attributes d){
    this->total_time_the_simulation_lasts = amount_of_time;
    this->starting_disease_attributes = d;
    this->time = 0; 

    for(int i = 0; i < starting_population; i++){
        Agent a;
    }
}