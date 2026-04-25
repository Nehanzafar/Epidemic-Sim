<<<<<<< HEAD
#include "Agent.h"
=======
#include "Agent.h"
#include <random>
#include <iostream>
using namespace std;
Agent::Agent()
{

    random_device rd;
    mt19937 gen(rd());
    this->immuno_weakness = ((float)uniform_int_distribution<int>(0, 5)(gen)) / 10;
    this->infection_time = 0;
    this->immune = false;
    this->infected = false;
}
void Agent::data_dump()
{
    cout << "Agent immuno_weakness = " << this->immuno_weakness << endl;
    cout << "Agent infection_time = " << this->infection_time << endl;
    cout << "Is Agent immune = " << this->immune << endl;
    cout << "Is the Agent infected = " << this->infected << endl;
}
int main()
{
    Agent a;
    a.data_dump();
}
>>>>>>> 5efe4872ab4ea17b8a6d18bb487c100222e3e846
