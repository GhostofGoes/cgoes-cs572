#ifndef FUNC_H
#define FUNC_H

#include "rand.h"


#define PI 3.14159265358979323846  /* "good enough" value of pi */
#define TESTING 1

typedef struct {
    double x;   // Input x to f()
    double fx;  // Result of f(x)
} p; // Stores data for given inputs and results for the original function

const int maxGen = 17;      // Maximum number of generations
const int popSize = 10;     // Population size
const double xover = 0.3;   // Crossover Probability
const double mutateProb = 0.9;   // Mutation probability
const int tournySize = 3; // Tournament size
const int treeDepth = 10; // Initial depth of the trees in population

#endif
