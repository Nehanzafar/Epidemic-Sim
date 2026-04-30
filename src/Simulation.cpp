#include "Simulation.h"
using namespace std;

// #define DEBUG 0

Simulation::Simulation(int amount_of_time, int starting_population, Disease_attributes d, const int screen_width, const int screen_height, const int CELL_SIZE)
    : screen_width(screen_width), screen_height(screen_height), CELL_SIZE(CELL_SIZE)
{
    std::cout << "Initalizing the simulation..." << std::endl;
    std::cout << "Initalizing the Parameters..." << std::endl;
    this->total_time_the_simulation_lasts = amount_of_time;
    this->starting_disease_attributes = d;
    this->time = 0;
    random_device rd;
    mt19937 gen(rd());

    this->gen = gen;
    std::cout << "Parameters intialized" << std::endl;

    std::cout << "Deploying population.." << std::endl;
    grid = new Grid(screen_width / CELL_SIZE, screen_height / CELL_SIZE);
    for (int i = 0; i < starting_population; i++)
    {
        Agent *a = new Agent(gen);

        population.push_back(a);
    }
    std::cout << "Population successfully deployed.." << std::endl;
}

// This is fucked
// Ahmed land
void Simulation::interaction(Agent *sick, Agent *other)
{
#ifdef DEBUG
    std::cout << "Checking for disease in the sick agent.." << std::endl;
#endif

    if (!sick->is_sick())
    {
#ifdef DEBUG

        std::cout << "Not Sick.." << std::endl;
#endif
        return;
    }

#ifdef DEBUG
    std::cout << "Checking if target is immune.." << std::endl;
#endif
    const auto &immunity = other->get_immunity_codes(); // store reference, not copies
    if (find(immunity.begin(), immunity.end(), sick->get_disease()->get_code()) != immunity.end())
    {
#ifdef DEBUG
        std::cout << "Target is immune.." << std::endl;
#endif
        return;
    }

#ifdef DEBUG
    std::cout << "Checking infect roll.." << std::endl;
#endif
    float infection_chance = sick->get_disease()->get_infectivity() + other->get_immuno_weakness();
    float roll = uniform_int_distribution<int>(1, 10)(gen) / 10.0f;

    if (roll <= infection_chance)
    {
        float mutate_roll = uniform_int_distribution<int>(1, 10)(gen) / 10.0f;

        if (mutate_roll >= (1.0f - sick->get_disease()->get_mutate_chance()))
        {
#ifdef DEBUG
            std::cout << "Disease Mutated.." << std::endl;
#endif
            Disease *d = new Disease(this->gen);
            this->disease_list.push_back(d);
            other->infect(d);
        }
        else
        {
#ifdef DEBUG
            std::cout << "Disease Not Mutated.." << std::endl;
#endif
            other->infect(sick->get_disease());
        }
    }
}

void Simulation::update_grid()
{
    // 1. wipe the grid clean

    // 2. Put each agent into the correct bucket
    for (Agent *agent : population)
    {
        int gx = static_cast<int>((*agent).get_position().x / CELL_SIZE);
        int gy = static_cast<int>((*agent).get_position().y / CELL_SIZE);

        // Boundary check to prevent crashing if an agent leaves the screen
        if (gx >= 0 && gx < grid->get_grid_info().COLS && gy >= 0 && gy < grid->get_grid_info().ROWS)
        {
            // updates the grid
            ((*grid)[gy])[gx] = agent;
        }
    }
}

// This handles the indivual tick
void Simulation::run_step()
{

    grid->clear();
    int count = 0;

    update_grid();
    for (Agent *agent : population)
    {

        if ((*agent).infection_tick() == 1)
        {
            population.erase(remove(population.begin(), population.end(), agent), population.end());
            delete agent;
            agent = nullptr;
            continue;
        }

        int gx = static_cast<int>((*agent).get_position().x / CELL_SIZE);
        int gy = static_cast<int>((*agent).get_position().y / CELL_SIZE);

        vector<Pos> allowed_pos;

        for (int x = gx - 1; x <= gx + 1; x++)
        {
            for (int y = gy - 1; y <= gy + 1; y++)
            {
                if (x >= 0 && x < grid->get_grid_info().COLS && y >= 0 && y < grid->get_grid_info().ROWS)
                {
                    if (x == gx && y == gy)
                        continue;

                    Agent *other = ((*grid)[x])[y];
                    if (other != nullptr)
                    {
                        if (agent->is_sick())
                        {
#ifdef DEBUG
                            std::cout << "Interaction ocurring..." << std::endl;
#endif
                            interaction(agent, other);
#ifdef DEBUG
                            std::cout << "Interaction ocurred..." << std::endl;
#endif
                        }
                    }
                    else
                    {
                        allowed_pos.push_back({x, y});
                    }
                }
            }
        }

        // move this to class attribute

        // int rndm_num = 0;

        if (allowed_pos.empty())
            continue;

        int rndm_num = uniform_int_distribution<int>(0, static_cast<int>(allowed_pos.size() - 1))(gen);
        int newX = allowed_pos[rndm_num].x * CELL_SIZE;
        int newY = allowed_pos[rndm_num].y * CELL_SIZE;

        if (newX >= 0 && newX <= screen_width &&
            newY >= 0 && newY <= screen_height)
            agent->set_position({newX, newY});

        count++;
    }
    cout << count << endl;
}

void Simulation::draw()
{
    int i = 0;
    for (Agent *a : population)
    {
        Color color = {100, 255, 255, 255};
        if (a->is_sick())
        {
            // color = RED;

            color.b -= a->get_disease()->get_code();
            color.g -= a->get_disease()->get_code();
            color.r -= a->get_disease()->get_code();
        }
        else
        {
            color = WHITE;
        }
        a->draw(color);
        // grid->display();

        // if(a->within_agent(GetMousePosition())){
        //     a->draw_info_panel();
        //     // a->toggle_info_panel();

        // }
    }
}

void Simulation::draw_grid()
{
    int cells = 0;
    Color color = {200, 239, 236, 100};
    for (int i = 0; i < grid->get_grid_info().ROWS; i++)
    {
        cells += CELL_SIZE;
        DrawLine(0, cells, screen_width, cells, color);
    }
    cells = 0;
    for (int j = 0; j < grid->get_grid_info().COLS; j++)
    {
        cells += CELL_SIZE;
        DrawLine(cells, 0, cells, screen_height, color);
    }
}

void Simulation::run_simulation()
{
    std::cout << "The simulation is starting.." << std::endl;
    std::cout << "Population Size: " << population.size() << std::endl;
    Disease *d = new Disease(this->gen);
    disease_list.push_back(d);
    population[0]->infect(d);
    population[1]->infect(d);
    population[2]->infect(d);
}

Simulation::~Simulation()
{
    for (auto &a : population)
    {
        delete a;
    }
}

Grid::Grid(int ROWS, int COLS)
{
    grid = new Agent **[ROWS];
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
    for (int y = 0; y < COLS; y++)
    {
        for (int x = 0; x < ROWS; x++)
        {
            grid[x][y] = nullptr;
        }
    }
}

Agent **Grid::operator[](int i)
{
    return grid[i];
}

void Grid::display()
{
    //     for (int y = 0; y < COLS; y++)
    //     {
    //         for (int x = 0; x < ROWS; x++)
    //         {
    //         //     if (grid[x][y] != nullptr)
    //         //     {

    //         //         // #ifdef DEBUG
    //         //         std::cout << 1 << " ";
    //         //         // #endif
    //         //     }
    //         //     else
    //         //     {
    //         //         // #ifdef DEBUG
    //         //         std::cout << 0 << " ";
    //         //         // #endif
    //         //     }
    //         //     // std::cout << grid[x][y] << " ";
    //         // }
    // #ifdef DEBUG
    //         std::cout << std::endl;
    // #endif
    //     }
    // #ifdef DEBUG
    //     std::cout << std::endl;
    // #endif
}

info Grid::get_grid_info()
{
    info tmp = {ROWS, COLS};
    return tmp;
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

// Things i have noticed
// The simulation is too fast
// the person recovers faster than the screen can display it
// The motion is localized to specific regions for some reason22