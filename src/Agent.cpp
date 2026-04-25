#include "Agent.h"
#include <random>
#include <iostream>
// #include <raylib>

using namespace std;
Agent::Agent()
{

    random_device rd;
    mt19937 gen(rd());
    this->immuno_weakness = ((float)uniform_int_distribution<int>(0, 5)(gen)) / 10;
    this->infection_time = 0;
    this->immune = false;
    this->infected = false;

    // this->position = {
    //     uniform_int_distribution<int>(0, getScreenWidth())(gen),
    //     uniform_int_distribution<int>(0, getScreenHeight())(gen)
    // }


}
void Agent::data_dump()
{
    cout << "Agent immuno_weakness = " << this->immuno_weakness << endl;
    cout << "Agent infection_time = " << this->infection_time << endl;
    cout << "Is Agent immune = " << this->immune << endl;
    cout << "Is the Agent infected = " << this->infected << endl;
}
