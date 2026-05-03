#include "Disease.h"
using namespace std;
Disease::Disease(mt19937 gen)
{
    this->code = strains++;
    this->fatality = ((float)uniform_int_distribution<int>(1, 5)(gen)) / 10;

    this->infectivity = ((float)uniform_int_distribution<int>(1, 5)(gen)) / 10;
    this->recovery_time = (uniform_int_distribution<int>(120, 600)(gen));
}

Disease::Disease(float fatality, float infectivity, float recovery_time, std::mt19937 gen)
{
    this->code = strains++;
    this->fatality = fatality;
    this->infectivity = infectivity;
    this->recovery_time = recovery_time;
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
int Disease::strains = 0;
