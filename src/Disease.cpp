#include "Disease.h"
#include <string>
#include <cstdlib>
using namespace std;
Disease::Disease(string name, float fatality, float infectivity, float recovery_time, float mutate)
{
    this->name = name;
    this->fatality = fatality;
    this->infectivity = infectivity;
    this->recovery_time = recovery_time;
    this->mutate = mutate;
}