#include "Agent.h"

using namespace std;

// #define DEBUG 0

Agent::Agent(std::mt19937 gen, int screen_width, int screen_height, int x, int y)
{
    this->gen = gen;
    this->immuno_weakness = (uniform_real_distribution<float>(0, 0.5)(gen));
    this->infection_time = 0;
    this->infected = false;
    this->disease = nullptr;

    this->position = {
        x, y};
}

void Agent::data_dump()

{

    cout << "Agent immuno_weakness = " << this->immuno_weakness << endl;
    cout << "Agent infection_time = " << this->infection_time << endl;
    cout << "Is the Agent infected = " << this->infected << endl;
    if (infected || disease != nullptr)
    {
        cout << "Disease Name = " << disease->get_code() << endl;
    }
}
void Agent::infect(Disease *disease)
{
    this->disease = disease;
    this->disease->increment_total_Agents_infected();
    this->infection_time = (int)((this->disease->get_recovery_time()) * (1 + this->immuno_weakness));
    this->infected = true;
    this->imunity_codes.push_back(this->disease->get_code());
    sort(this->imunity_codes.begin(), this->imunity_codes.end());
}

Disease *Agent::get_disease()
{
    return this->disease;
}
float Agent::get_immuno_weakness()
{
    return this->immuno_weakness;
}

int Agent::infection_tick()
{
    if (this->infection_time > 0)
    {
        this->infection_time--;
        if (infection_time == 0)
        {
            float fatality_chance = this->immuno_weakness + this->get_disease()->get_fatality_chance();
            if ((uniform_real_distribution<float>(0.0f, 1.1f)(gen)) <= fatality_chance)
            {
                this->get_disease()->increment_total_Agents_killed();
                return 1;
            }
            this->infected = false;
            this->disease = nullptr;
            return 0;
        }
        return -1;
    }
}
// nehan land

void Agent::draw(Color color1, Color color2)
{
    DrawCircleGradient(position.x, position.y, CELL_SIZE, color1, color2);

    std::string s = "( " + std::to_string(position.x) + ", " + std::to_string(position.y) + " )";

#ifdef DEBUG
    DrawText(s.c_str(), position.x + 5, position.y + 10, 20, WHITE);
#endif
}

void Agent::update(int x, int y)
{
    this->position.x = x;
    this->position.y = y;
}

Pos Agent::get_position() const
{
    return position;
}

int Agent::get_velocity() const
{
    return velocity;
}

void Agent::set_position(Pos pos)
{
    this->position = pos;
}

vector<int> &Agent::get_immunity_codes()
{
    return this->imunity_codes;
}

bool Agent::is_sick()
{
    return infected;
}

bool Agent::within_agent(Vector2 mousePosition)
{
    return std::pow(mousePosition.x - this->position.x, 2) + std::pow(mousePosition.y - this->position.y, 2) < CELL_SIZE;
}

void Agent::draw_info_panel()
{
    DrawRectangle(this->position.x - 10, this->position.y - 20, 30, 50, GREEN);
}

bool Agent::is_info_panel_open()
{
    return info_panel_open;
}

void Agent::toggle_info_panel()
{
    if (!info_panel_open)
    {
        this->info_panel_open = true;
        return;
    }
    this->info_panel_open = false;
    return;
}