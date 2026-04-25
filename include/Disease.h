#include <string>
class Disease
{
private:
    // Identifiers
    std::string name;
    // Modifier
    float fatality;
    float infectivity;
    float recovery_time; // time in ticks to recover from disease
    float mutate_chance; // chance of mutatuing

public:
    static int strains; // tracks number of active strains
    Disease();
    Disease(string name, float fatality, float infectivity, float recovery_time, float mutate); // Parameterized constructor to Assign all the modifiers with values
};