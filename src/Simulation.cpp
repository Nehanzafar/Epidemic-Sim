#include "Simulation.h"
#include "Grid.h"
using namespace std;

Simulation::Simulation(int amount_of_time, int starting_population, Disease_attributes d = {0, 0, 0, 0})
{
    this->total_time_the_simulation_lasts = amount_of_time;
    this->starting_disease_attributes = d;
    this->time = 0;

    grid = new Grid(ROWS, COLS);
    for (int i = 0; i < starting_population; i++)
    {
        Agent *a = new Agent;
        std::cout << "X: " << a->get_position().x << "Y: " << a->get_position().y << std::endl;
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
    // 1. wipe the grid clean
    grid->clear();

    // 2. Put each agent into the correct bucket
    for (auto &agent : population)
    {
        int gx = static_cast<int>((*agent).get_position().x / CELL_SIZE);
        int gy = static_cast<int>((*agent).get_position().y / CELL_SIZE);

        // Boundary check to prevent crashing if an agent leaves the screen
        if (gx >= 0 && gx < COLS && gy >= 0 && gy < ROWS)
        {
            ((*grid)[gy])[gx] = agent;
        }
    }
}

// This handles the indivual tick
void Simulation::run_step()
{

    for (auto &agent : population)
    {

        if ((*agent).infection_tick() == 1)
        {
            delete[] agent;
            population.erase(remove(population.begin(), population.end(), agent), population.end());
            return;
        }
        vector<Pos> allowed_pos;

        int gx = static_cast<int>(agent->get_position().x) / CELL_SIZE;
        int gy = static_cast<int>(agent->get_position().y) / CELL_SIZE;

        for (int x = gx - 1; x < gx + 1; x++)
        {
            for (int y = gy - 1; y < gy + 1; y++)
            {
                if (x >= 0 && x < COLS && y >= 0 && y < ROWS)
                {
                    if (x == gx && y == gy)
                        continue;

                    if (((*grid)[y])[x] != nullptr && agent->get_disease() != nullptr)
                    {
                        interaction(*((*grid)[gy])[gx], *((*grid)[y])[x]);
                    }
                    else
                    {
                        allowed_pos.push_back({x, y});
                    }
                }
            }
        }
        random_device rd;
        mt19937 gen(rd());

        int rndm_num = uniform_int_distribution<int>(0, allowed_pos.size())(gen);
        if ((allowed_pos[rndm_num].x + CELL_SIZE > 0) || (allowed_pos[rndm_num].x + CELL_SIZE <= screen_width) && (allowed_pos[rndm_num].y + CELL_SIZE > 0) || (allowed_pos[rndm_num].y + CELL_SIZE <= screen_height))
            agent->set_position(allowed_pos[rndm_num]);
    }
}

void Simulation::draw()
{
    for (auto &a : population)
    {
        Color color = {200, 200, 200};
        if (a->is_sick())
        {
            color.b -= a->get_disease()->get_code();
            color.g -= a->get_disease()->get_code();
            color.r -= a->get_disease()->get_code();
        }
        else
        {
            color = WHITE;
        }
        a->draw(color);
    }
}

void Simulation::run_simulation()
{
    std::cout << "The simulation is starting.." << std::endl;
}