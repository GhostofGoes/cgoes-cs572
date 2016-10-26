#ifndef POINTS_H
#define POINTS_H

#include <iostream>
#include <string>
#include <vector>

#include "rand.h"

using namespace std;

#define PI 3.14159265358979323846  /* "good enough" value of pi */
#define TESTING 0
const unsigned int fieldWidth = 10; // For spacing when printing stuff


const double CROSSOVER_PROB = 0.8; // Probability of crossing over selected parents into child
const int MUTATION = 0;     // 0 = Single Swap
const double MUTATION_PROB = 1.0; // Probability of mutating the child
const int EVOLUTIONS = 100000; // # of times steady state algorithm evolves (# of runs)


typedef struct {
    double theta;   // Range: [0, 2PI]
    double r;       // Range: [0, 1]
} point; // Single point using polar notation on a unit circle. theta = angle, r = radius

typedef vector<point> chromosome;

typedef struct {
    double fitness;         // Fitness of the member
    chromosome c;   // Points for the member in polar coordinates
} member; // Member of population

#endif
