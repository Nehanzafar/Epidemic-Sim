#include "Disease.h"
#include <string>
#include <cstdlib>
using namespace std;
Disease::Disease()
{
    this->name = "";
    this->fatality = 0;
    this->infectivity = 0;
    this->recovery_time = 0;
    this->mutate_chance = 0;
}

Disease::Disease(string name, float fatality, float infectivity, float recovery_time, float mutate)
{
    this->name = name;
    this->fatality = fatality;
    this->infectivity = infectivity;
    this->recovery_time = recovery_time;
    this->mutate_chance = mutate;
}
int Disease::strains = 0;
