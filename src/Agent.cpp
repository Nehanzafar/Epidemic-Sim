#include "Agent.h"
#include <cmath>
#include "raylib.h"
#include "Window.h"
using namespace std;

Agent::Agent()
{

    random_device rd;
    mt19937 gen(rd());
    this->immuno_weakness = ((float)uniform_int_distribution<int>(1, 5)(gen)) / 10;
    this->infection_time = 0;
    this->infected = false;
    this->disease = nullptr;
    this->position = {
        uniform_int_distribution<int>(1, screen_width)(gen),
        uniform_int_distribution<int>(1, screen_height)(gen),
    };
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
void Agent::infect(Disease &disease)
{
    this->disease = &disease;
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
// nehan land

void Agent::draw()
{
    DrawCircle(position.x, position.y, CELL_SIZE, WHITE);
}

void Agent::update()
{

    random_device rd;
    mt19937 gen(rd());
    int angle_in_deg = uniform_int_distribution<int>(0, 360)(gen);
    const double pi = 3.14159265358979323846;
    float angle_in_rad = (angle_in_deg * 180) / pi;

    int newPosX = position.x + velocity * cos(angle_in_rad);
    int newPosY = position.y + velocity * sin(angle_in_rad);
    if ((newPosX + CELL_SIZE > 0) || (newPosX + CELL_SIZE <= GetScreenWidth()))
        position.x = newPosX;
    if ((newPosY + CELL_SIZE > 0) || (newPosY + CELL_SIZE <= GetScreenHeight()))
        position.y = newPosY;
}

Pos Agent::get_position()
{
    return position;
}