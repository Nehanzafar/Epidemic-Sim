#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <raylib.h>
#include <cmath>
// Our own code
#include "Disease.h"
struct Pos
{
    int x;
    int y;
};

const int CELL_SIZE = 5;

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
    Pos last_position;
    const int velocity = 5;

    // flag
    bool info_panel_open = false;
    // rndm function
    std::mt19937 gen;

public:
    Agent(std::mt19937 gen, int screen_width, int screen_height); // Default constructor to assign random values to modifiers
    // helper
    void infect(Disease *); // only infects no checks
    void data_dump();       // outputs the entire stats of agent
    void draw(Color color);
    void draw_info_panel();
    void update(int, int);
    // getter
    float get_immuno_weakness();
    Disease *get_disease();
    Pos get_position() const;
    void set_position(Pos);
    void set_last_position(Pos);
    int get_velocity() const;
    std::vector<int> &get_immunity_codes();
    unsigned int get_infection_time();
    int infection_tick();
    bool is_sick();
    bool within_agent(Vector2 mousePosition);
    bool is_info_panel_open();
    void toggle_info_panel();
};