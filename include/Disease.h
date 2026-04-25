#pragma once
#include <string>

struct Disease_attributes
{
    float fatality;
    float infectivity;
    float recovery_time;
    float mutate_chance;
};
class Disease
{
private:
    // Identifiers
    int code;
    // Modifier
    float fatality;
    float infectivity;
    float recovery_time;       // time in ticks to recover from disease
    float mutate_chance = 0.1; // chance of mutatuing

public:
    static int strains; // tracks number of active strains
    Disease();
    Disease(float fatality, float infectivity, float recovery_time); // Parameterized constructor to Assign all the modifiers with values
    // getter
    int get_code();
};