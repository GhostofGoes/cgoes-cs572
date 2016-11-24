#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <string>
#include <vector>

#include "rand.h"

using namespace std;

#define PI 3.14159265358979323846  /* "good enough" value of pi */
#define TESTING 0

const unsigned int fieldWidth = 10; // For spacing when printing stuff

typedef struct {
    double x;   // Input x to f()
    double fx;  // Result of f(x)
} p; // Stores data for given inputs and results for the original function

const int maxGen = 17;     // Maximum number of generations
const int popSize = 10;    // Population size
const double xover = 0.3;      // Crossover Probability

#endif
