#ifndef FUNC_H
#define FUNC_H

#include <vector>
#include "rand.h"

#define TESTING 0
#define STATS 1

// Stores data for given inputs and results for the original function (basically a tuple)
typedef struct {
    double x;   // Input x to f()
    double fx;  // Result of f(x)
} p; 

const int maxGen = 100;     // Maximum number of generations
const int popSize = 256;    // Population size

const double xover = 0.4;       // Crossover Probability of an individual
const double mutateProb = 0.5;  // Mutation probability of an individual
const int tournySize = 3;       // Tournament size
const int elites = 5;


const int maxStartingDepth = 15;    // Range of initial depths of the trees in population
const int minStartingDepth = 3;     // Lower end of depth range
const int growthFactor = 1;         // Factor by which crossed over trees grow

#endif
