# Epidemic Spread Simulation

## Overview

This project is a C++ simulation that models how an infectious disease spreads through a population as individuals move randomly and interact with one another. The simulation demonstrates how simple rules governing movement and infection can produce complex patterns of disease transmission over time.

The program tracks key population statistics throughout the simulation, allowing users to observe how the number of healthy, infected, recovered (if implemented), and deceased individuals changes as the outbreak progresses.

## Features

* Random movement of individuals
* Disease transmission through close interactions
* Configurable simulation parameters
* Population statistics tracking
* Time-series data generation
* Data visualization support

## Technologies Used

* C++
* Object-Oriented Programming
* Raylib
* STL
* CSV data export
* Data visualization

## What I Learned

Through this project, I gained experience with:

* Simulation design
* Object-oriented programming
* Stochastic (probabilistic) modeling
* Data collection and analysis
* Managing large numbers of interacting entities
* Handling close proximity interaction
* Using grid based system to check interaction
* Debugging and validating simulation behavior

This project was developed as part of my university coursework and helped strengthen my understanding of simulation techniques and computational modeling.


## Pre-requisites
Cmake 4.2 or above
Visual Studio 18 2026 or MinGW x64

## Quick Build Instructions:
git clone <repo>

cd Project

cmake -B  build -G "Visual Studio 18 2026" -A x64
cmake -B build -G "MinGW Makefiles" (For unix based systems)
cmake --build build

If you are explicitly using MinGWx64 then use 
cmake -B  build  -DCMAKE_BUILD_TYPE=Release (for optimized building)

# You can also use a valid version from the release section