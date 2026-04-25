struct Pos{
    int x;
    int y;
};
class Agent
{
private:
    // Modifiers
    float infection_modifier; // Infection Time ends: The person either lives or dies
    // Random Variables / Probalities
    float immuno_strength; // The person's immune weakness
    // Timers
    float infection_time; // Time remaining the person will remain sick
    // Flags
    bool immune; // If the person is immune he can't get sick
    // position
    Pos position;

public:
};