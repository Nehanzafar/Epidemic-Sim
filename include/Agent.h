#pragma once
#include "Disease.h"
<<<<<<< HEAD
#include <vector>
=======
struct Pos{
    int x;
    int y;
};

>>>>>>> f1901e48843657c26e05f89f3ae75acc73276fd3
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
<<<<<<< HEAD
    // immunity codes

    //  Disease storage
    Disease *disease;
=======
    // Disease storage
    Disease disease;
    Pos position;
>>>>>>> f1901e48843657c26e05f89f3ae75acc73276fd3

public:
    int *immunity_codes;
    int size_of_codes;
    Agent(); // Default constructor to assign random values to modifiers
    // helper
    int infect(const Agent &other);
    void data_dump(); // outputs the entire stats of agent
};