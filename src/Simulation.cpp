#include "Simulation.h"
using namespace std;

Simulation::Simulation(int amount_of_time, int starting_population, Disease_attributes d = {0, 0, 0, 0})
{
    this->total_time_the_simulation_lasts = amount_of_time;
    this->starting_disease_attributes = d;
    this->time = 0;

    for (int i = 0; i < starting_population; i++)
    {
        Agent a;
        std::cout << "X: " << a.get_position().x << "Y: " << a.get_position().y << std::endl;
        population.push_back(a);
    }
}
void Simulation::interaction(Agent &sick, Agent &other)
{
    if (sick.get_disease() == nullptr)
    {
        return;
    }
    if (find(other.get_immunity_codes().begin(), other.get_immunity_codes().end(), sick.get_disease()->get_code()) != other.get_immunity_codes().end())
    {
        return;
    }
    random_device rd;
    mt19937 gen(rd());
    float infection_chance = (sick.get_disease()->get_infectivity() + other.get_immuno_weakness());
    if ((((float)uniform_int_distribution<int>(1, 10)(gen)) / (10)) <= infection_chance)
    {
        if ((((float)uniform_int_distribution<int>(1, 10)(gen)) / (10)) >= ((1) - (sick.get_disease()->get_mutate_chance())))
        {
            Disease *d = new Disease();
            this->disease_list.push_back(d);
            other.infect(*d);
        }
        else
            other.infect(*(sick.get_disease()));
    }
}

void Simulation::update_grid()
{
    // 1. Wipe the grid clean
    for (int x = 0; x < COLS; x++)
    {
        for (int y = 0; y < ROWS; y++)
        {
            grid[x][y].clear();
        }
    }

    // 2. Put each agent into the correct bucket
    for (auto &agent : population)
    {
        int gx = static_cast<int>(agent.get_position().x / CELL_SIZE);
        int gy = static_cast<int>(agent.get_position().y / CELL_SIZE);

        // Boundary check to prevent crashing if an agent leaves the screen
        if (gx >= 0 && gx < COLS && gy >= 0 && gy < ROWS)
        {
            grid[gx][gy].push_back(&agent);
        }
    }
}

void Simulation::handle_collision()
{
    for (auto &agent : population)
    {
        int gx = static_cast<int>(agent.get_position().x);
        int gy = static_cast<int>(agent.get_position().y);

        for (int x = gx - 1; x < gx + 1; x++)
        {
            for (int y = gy - 1; y < gy + 1; y++)
            {
                if (x >= 0 && x < COLS && y >= 0 && y < ROWS)
                {
                    if (grid[x][y] == grid[gx][gy])
                        continue;

                    if (grid[x][y] != nullptr)
                    {
                        interaction(grid[gx][gy], grid[x][y]);
                    };
                }
            }
        }
    }
}

void Simulation::run_simulation()
{
    
}