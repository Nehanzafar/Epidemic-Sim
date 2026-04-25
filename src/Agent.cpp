#include "Agent.h"
#include <random>
#include <iostream>
// #include <raylib>

using namespace std;
Agent::Agent()
{

    random_device rd;
    mt19937 gen(rd());
    this->immuno_weakness = ((float)uniform_int_distribution<int>(1, 5)(gen)) / 10;
    this->infection_time = 0;
    this->infected = false;
    this->disease = nullptr;
    this->immunity_codes = new int[0];
    this->size_of_codes = 5;
}
void Agent::data_dump()
{
    cout << "Agent immuno_weakness = " << this->immuno_weakness << endl;
    cout << "Agent infection_time = " << this->infection_time << endl;
    cout << "Is the Agent infected = " << this->infected << endl;
    if (infected || disease != nullptr)
    {
        cout << "Disease Name = " << disease->get_code() << endl;
    }
}
