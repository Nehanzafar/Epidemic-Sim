#include "Disease.h"
#include <string>
#include <cstdlib>
Disease::Disease()
{
    this->code = strains++;
    this->fatality = 0;
    this->infectivity = 0;
    this->recovery_time = 0;
}

Disease::Disease(float fatality, float infectivity, float recovery_time)
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

int Disease::strains = 0;
