
#include "Simulation.h"
using namespace std;

Simulation::Simulation(int starting_population, Disease_attributes d,
                       const int screen_width, const int screen_height, const int CELL_SIZE, const int tick)
    : screen_width(screen_width), screen_height(screen_height), CELL_SIZE(CELL_SIZE), tick(tick)
{
    this->starting_population = starting_population;
    this->starting_disease_attributes = d;
    this->time = 0; // in ticks which should be divided by the number of ticks of the window
    this->amount_of_recovered = 0;

    random_device rd;
    this->gen = mt19937(rd());

    grid = new Grid(screen_height / CELL_SIZE, screen_width / CELL_SIZE); // ROWS=y, COLS=x

    population.reserve(starting_population);
    for (int i = 0; i < starting_population; i++)
    {

        do
        {
            int x = static_cast<int>(normal_distribution<float>(static_cast<float>(screen_width / 2), 80.0f)(gen));
            int y = static_cast<int>(normal_distribution<float>(static_cast<float>(screen_height / 2), 80.0f)(gen));

            int gx = x / CELL_SIZE;
            int gy = y / CELL_SIZE;

            if (x < 0 || x >= screen_width || y < 0 || y >= screen_height)
                continue; // skip out of bounds values

            if ((*grid)[gy][gx] == nullptr)
            {
                Agent *a = new Agent(gen, screen_width, screen_height, x, y);
                (*grid)[gy][gx] = a;
                population.push_back(a);
                break;
            }
        } while (true);
    }

    ofstream myfile("outputData.csv");
    myfile << "time,population,deaths,sick,diseases,recovered" << endl;
    myfile.close();
}

void Simulation::interaction(Agent *sick, Agent *other)
{
    if (!sick->is_sick())
        return;

    const std::vector<int> &immunity = other->get_immunity_codes();
    if (find(immunity.begin(), immunity.end(), sick->get_disease()->get_code()) != immunity.end())
        return;

    float infection_chance = sick->get_disease()->get_infectivity() + other->get_immuno_weakness();
    float roll = uniform_real_distribution<float>(0, 2.0)(gen);

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

int Simulation::run_step()
{
    grid->clear();
    update_grid();

    auto info = grid->get_grid_info();
    vector<Agent *> dead;
    vector<Pos> allowed_pos;
    allowed_pos.reserve(8); // at most 8 neighbors
    this->time++;
    int sick_count = 0;
    bool any_sick =false;
    bool should_write_to_file = false;

    if (time % (this->tick / 2) == 0)
        should_write_to_file = true;

    for (Agent *agent : population)
    {
        if (agent->is_sick()==1)
            any_sick = true;
        if (agent->infection_tick() == 1)
        {
            dead.push_back(agent);
            continue;
        }
        else if (agent->infection_tick() == 0)
        {
            this->amount_of_recovered++;
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

        if (should_write_to_file && agent->is_sick())
            sick_count++;
        // agent->data_dump();
    }

    // Safe removal after iteration — avoids UB of erase-during-range-for
    for (Agent *a : dead)
    {
        population.erase(remove(population.begin(), population.end(), a), population.end());
        delete a;
    }

    if (should_write_to_file)
<<<<<<< HEAD
        write_to_file(time, population.size(), starting_population - population.size(), sick_count, disease_list.size());
    if(any_sick == false)
        return 1;
    return 0;
=======
        write_to_file(time, population.size(), starting_population - population.size(), sick_count, disease_list.size(), this->amount_of_recovered);
>>>>>>> 12601d535d20912eb99eb00c44ab970fcd726e87
}

void Simulation::draw()
{
    Color color = {100, 255, 255, 255};
    int code;
    string population = "Population: " + to_string(this->population_count());
    string Active_strains = "Total Active Strains: " + to_string(this->disease_list.size());
    string Time = "Time: " + to_string(this->time / this->tick);

    // Info panel to the right
    int font_size = 40;
    int starting_pos = 30;
    DrawText(Time.c_str(), 30, starting_pos, 30, WHITE);
    starting_pos += font_size;
    DrawText(population.c_str(), 30, starting_pos, 30, WHITE);
    starting_pos += font_size;
    DrawText(Active_strains.c_str(), 30, starting_pos, 30, WHITE);

    for (Agent *a : this->population)
    {
        if (a->is_sick())
        {
            a->draw(a->get_disease()->get_color().infectivity, a->get_disease()->get_color().fatality);
        }
        else
        {
            a->draw(WHITE, WHITE);
        }
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
    Disease *d = new Disease(this->starting_disease_attributes.fatality, this->starting_disease_attributes.infectivity, this->starting_disease_attributes.recovery_time);
    disease_list.push_back(d);
    population[0]->infect(d);
    write_to_file(time, population.size(), starting_population - population.size(), 1, disease_list.size(), this->amount_of_recovered);
}

int Simulation::population_count()
{
    return population.size();
}

void Simulation::write_to_file(int time, int current_population, int amount_of_deaths, int sick_count, int total_number_of_diseases, int amount_of_recovered)
{
    ofstream myfile("outputData.csv", ios::app);

    if (!myfile.is_open())
    {
        cerr << "Error: could not open outputData.csv" << endl;
        return;
    }

    myfile << time / this->tick << ","
           << current_population << ","
           << amount_of_deaths << ","
           << sick_count << ","
           << total_number_of_diseases << ","
           << amount_of_recovered
           << "\n";

    myfile.close();
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
