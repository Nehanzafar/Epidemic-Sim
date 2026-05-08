#pragma once
#include <string>
#include <string>
#include <cstdlib>
#include <random>
#include <raylib.h>

struct Disease_attributes
{
    float fatality;
    float infectivity;
    int recovery_time;
};

struct Gradient
{
    Color fatality;
    Color infectivity;
};
class Disease
{
private:
    // Identifiers
    int code;
    // Modifier
    float fatality;
    float infectivity;
    float recovery_time;              // time in ticks to recover from disease
    float const mutate_chance = 0.05; // chance of mutatuing
    // stats
    int total_Agents_infected = 0;
    int total_Agents_kiilled = 0;
    Gradient colorScheme;

public:
    static int strains; // tracks number of active strains
    Disease(std::mt19937 gen);
    Disease(float fatality, float infectivity, float recovery_time); // Parameterized constructor to Assign all the modifiers with values
    // getter
    int get_code();
    int get_recovery_time();
    int get_total_Agents_infected();
    float get_infectivity();
    float get_mutate_chance();
    float get_fatality_chance();
    // setter
    void increment_total_Agents_infected();
    void increment_total_Agents_killed();
    void assign_color();
    Gradient get_color();
};