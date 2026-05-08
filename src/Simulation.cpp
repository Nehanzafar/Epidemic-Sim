#include "Simulation.h"
using namespace std;

Simulation::Simulation(int amount_of_time, int starting_population, Disease_attributes d,
                       const int screen_width, const int screen_height, const int CELL_SIZE)
    : screen_width(screen_width), screen_height(screen_height), CELL_SIZE(CELL_SIZE)
{
    this->total_time_the_simulation_lasts = amount_of_time;
    this->starting_disease_attributes = d;
    this->time = 0;

    random_device rd;
    this->gen = mt19937(rd());

    grid = new Grid(screen_height / CELL_SIZE, screen_width / CELL_SIZE); // ROWS=y, COLS=x

    population.reserve(starting_population);
    for (int i = 0; i < starting_population; i++)
        population.push_back(new Agent(gen, screen_width, screen_height));
}

void Simulation::interaction(Agent *sick, Agent *other)
{
    if (!sick->is_sick())
        return;

    const std::vector<int> &immunity = other->get_immunity_codes();
    if (find(immunity.begin(), immunity.end(), sick->get_disease()->get_code()) != immunity.end())
        return;

    float infection_chance = sick->get_disease()->get_infectivity() + other->get_immuno_weakness();
    float roll = uniform_int_distribution<int>(0, 20)(gen) / 10.0f;

    if (roll <= infection_chance)
    {
        float mutate_roll = uniform_real_distribution<float>(0, 1.0f)(gen);
        if (mutate_roll <= (sick->get_disease()->get_mutate_chance()))
        {
            Disease *d = new Disease(this->gen);
            disease_list.push_back(d);
            other->infect(d);
        }
        else
        {
            other->infect(sick->get_disease());
        }
    }
}

void Simulation::update_grid()
{
    for (Agent *agent : population)
    {
        int gx = static_cast<int>(agent->get_position().x / CELL_SIZE);
        int gy = static_cast<int>(agent->get_position().y / CELL_SIZE);

        auto info = grid->get_grid_info();
        if (gx >= 0 && gx < info.COLS && gy >= 0 && gy < info.ROWS)
            (*grid)[gy][gx] = agent; // [row][col] = [y][x]
    }
}

void Simulation::run_step()
{
    grid->clear();
    update_grid();

    auto info = grid->get_grid_info();
    vector<Agent *> dead;
    vector<Pos> allowed_pos;
    allowed_pos.reserve(8); // at most 8 neighbors
    this->time++;

    for (Agent *agent : population)
    {
        if (agent->infection_tick() == 1)
        {
            dead.push_back(agent);
            continue;
        }

        int gx = static_cast<int>(agent->get_position().x / CELL_SIZE);
        int gy = static_cast<int>(agent->get_position().y / CELL_SIZE);
        bool is_sick = agent->is_sick(); // hoist: check once outside neighbor loop

        allowed_pos.clear();

        for (int dy = -1; dy <= 1; dy++)
        {
            for (int dx = -1; dx <= 1; dx++)
            {
                if (dx == 0 && dy == 0)
                    continue;
                int nx = gx + dx, ny = gy + dy;

                if (nx < 0 || nx >= info.COLS || ny < 0 || ny >= info.ROWS)
                    continue;

                Agent *other = (*grid)[ny][nx]; // consistent [row][col]
                if (other != nullptr)
                {
                    if (!other->is_sick())
                        interaction(agent, other);
                }
                else
                {
                    allowed_pos.push_back({nx, ny});
                }
            }
        }

        if (allowed_pos.empty())
            continue;

        int rndm = uniform_int_distribution<int>(0, (int)allowed_pos.size() - 1)(gen);
        int newX = allowed_pos[rndm].x * CELL_SIZE;
        int newY = allowed_pos[rndm].y * CELL_SIZE;

        if (newX >= 0 && newX <= screen_width && newY >= 0 && newY <= screen_height)
            agent->set_position({newX, newY});

        // agent->data_dump();
    }

    // Safe removal after iteration — avoids UB of erase-during-range-for
    for (Agent *a : dead)
    {
        population.erase(remove(population.begin(), population.end(), a), population.end());
        delete a;
    }
}

void Simulation::draw()
{
    Color color = {100, 255, 255, 255};
    int code;
    string population = "Population: " + to_string(this->population_count());
    string Active_strains = "Total Active Strains: " + to_string(this->disease_list.size());
    string Time = "Time: " + to_string(this->time);

    // Info panel to the right
    int font_size = 40;
    int starting_pos = 30;
    DrawText(Time.c_str(), 30, starting_pos, 30, WHITE);
    starting_pos += font_size;
    DrawText(population.c_str(), 30, starting_pos, 30, WHITE);
    starting_pos += font_size;
    DrawText(Active_strains.c_str(), 30, starting_pos, 30, WHITE);

    DrawCircle((screen_width / 2), (screen_height / 2), 10, WHITE);

    for (Agent *a : this->population)
    {
        if (a->is_sick())
        {
            code = a->get_disease()->get_code() * 5;
            color.r -= code;
            color.g -= code;
            color.b -= code;
        }
        else
        {
            color = WHITE;
        }
        a->draw(color);
    }
}

void Simulation::draw_grid()
{
    Color color = {200, 239, 236, 100};
    int cells = 0;
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
    Disease *d = new Disease(this->gen);
    disease_list.push_back(d);
    population[0]->infect(d);
}

int Simulation::population_count()
{
    return population.size();
}

Simulation::~Simulation()
{
    for (Agent *a : population)
        delete a;

    for (Disease *d : disease_list)
        delete d;

    delete grid;
}

// ---- Grid ----

Grid::Grid(int ROWS, int COLS) : ROWS(ROWS), COLS(COLS)
{
    grid = new Agent **[ROWS];
    for (int i = 0; i < ROWS; i++)
    {
        grid[i] = new Agent *[COLS];
        for (int j = 0; j < COLS; j++)
            grid[i][j] = nullptr;
    }
}

void Grid::clear()
{
    for (int row = 0; row < ROWS; row++)
        for (int col = 0; col < COLS; col++)
            grid[row][col] = nullptr;
}

Agent **Grid::operator[](int i)
{
    return grid[i];
}

info Grid::get_grid_info()
{
    return {ROWS, COLS};
}

Grid::~Grid()
{
    // Grid does NOT own agents — just free the 2D array structure
    for (int i = 0; i < ROWS; i++)
        delete[] grid[i];
    delete[] grid;
}
