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
    float mutate;        // chance of mutatuing

public:
    Disease(float fatality, float infectivity, float recovery_time, float mutate); // Parameterized constructor to Assign all the modifiers with values
};