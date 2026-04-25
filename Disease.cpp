#include "Disease.h"
#include <cstdlib>
Disease::Disease(std::string name, float fatality, float infectivity, float recovery_time, float mutate)
{
    this->fatality = fatality;
    this->infectivity = infectivity;
    this->recovery_time = recovery_time;
    this->mutate = mutate;
}