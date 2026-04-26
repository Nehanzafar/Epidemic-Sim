#pragma once
#include "Disease.h"
#include <vector>
#include <random>
#include <iostream>
#include <raylib.h>
#include <algorithm>

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
    std::vector<int> imunity_codes;
    //  Disease storage
    Disease *disease;

    // Board attributes
    Pos position;
    static const int velocity = 5;
    const int CELL_SIZE = 5;




public:
    Agent(); // Default constructor to assign random values to modifiers
    // helper
    void infect(Disease &); // only infects no checks
    void data_dump();      // outputs the entire stats of agent
    void draw();
    void update();
    //getter
    float get_immuno_weakness();
    Disease *get_disease();
    Pos get_position();
    vector<int> get_immunity_codes();
};