#include "Disease.h"
using namespace std;
Disease::Disease(mt19937 gen)
{
    this->code = strains++;
    this->fatality = (uniform_real_distribution<float>(0, 0.5)(gen));
    this->infectivity = (uniform_real_distribution<float>(0, 0.5)(gen));
    this->recovery_time = (uniform_real_distribution<float>(120, 600)(gen));
    assign_color();
}

Disease::Disease(float fatality, float infectivity, int recovery_time)
{
    this->code = strains++;
    this->fatality = fatality;
    this->infectivity = infectivity;
    this->recovery_time = recovery_time;
    assign_color();
}

int Disease::get_code()
{
    return this->code;
}
int Disease::get_recovery_time()
{
    return this->recovery_time;
}
int Disease::get_total_Agents_infected()
{
    return this->total_Agents_infected;
}
float Disease::get_infectivity()
{
    return this->infectivity;
}
float Disease::get_mutate_chance()
{
    return this->mutate_chance;
}
float Disease::get_fatality_chance()
{
    return this->fatality;
}
void Disease::increment_total_Agents_infected()
{
    this->total_Agents_infected++;
}
void Disease::increment_total_Agents_killed()
{
    this->total_Agents_kiilled++;
}

void Disease::assign_color()
{
    if (this->fatality > 0.4)
    {
        this->colorScheme.fatality = {
            87, 0, 0, 255};
    }
    else if (this->fatality > 0.3)
    {
        this->colorScheme.fatality = {
            136, 0, 0, 255};
    }
    else if (this->fatality > 0.2)
    {
        this->colorScheme.fatality = {
            170, 0, 0, 255};
    }
    else if (this->fatality > 0.1)
    {
        this->colorScheme.fatality = {
            225, 0, 0, 255};
    }
    else
    {
        this->colorScheme.fatality = {
            230, 0, 0, 255};
    }

    if (this->infectivity > 0.4)
    {
        this->colorScheme.infectivity = {
            0, 77, 0, 255};
    }
    else if (this->infectivity > 0.3)
    {
        this->colorScheme.infectivity = {
            0, 131, 0, 255};
    }
    else if (this->infectivity > 0.2)
    {
        this->colorScheme.infectivity = {
            0, 168, 0, 255};
    }
    else if (this->infectivity > 0.1)
    {
        this->colorScheme.infectivity = {
            0, 201, 0, 255};
    }
    else
    {
        this->colorScheme.infectivity = {
            0, 238, 0, 255};
    }
}

Gradient Disease::get_color()
{
    return colorScheme;
};

int Disease::strains = 0;
