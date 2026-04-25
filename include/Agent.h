#pragma once
#include "Disease.h"

struct Pos
{
    int x;
    int y;
};

class Agent
{
private:
    // Modifiers
    // float infection_modifier; // Infection Time ends: The person either lives or dies
    // Random Variables / Probalities
    float immuno_weakness; // The person's immune weakness
    // Timers
    unsigned int infection_time; // Time remaining the person will remain sick
    // Flags
    bool infected; // is the Agent infected or not
    // immunity codes

    //  Disease storage
    Disease *disease;
    Pos position;

public:
    int *immunity_codes;
    int size_of_codes;
    Agent(); // Default constructor to assign random values to modifiers
    // helper
    int infect(const Agent &other);
    void data_dump(); // outputs the entire stats of agent
};