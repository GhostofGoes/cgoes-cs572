#ifndef FUNC_H
#define FUNC_H

#include <vector>
#include "rand.h"

#define TESTING 0
#define STATS 0
#define DUMP 0

// Stores data for given inputs and results for the original function (basically a tuple)
typedef struct {
    double x;   // Input x to f()
    double fx;  // Result of f(x)
} p; 

const int maxGen = 100;     // Maximum number of generations
const int popSize = 256;    // Population size

const double xover = 0.5;       // Crossover Probability of an individual
const double mutateProb = 0.3;  // Mutation probability of an individual
const int tournySize = 3;       // Tournament size
const int elites = 20;          // Number of elites that persist between generations (NOTE: must be less tahn popSize!)

const int startingDepthRange = 10;  // Range of initial depths of the trees in population
const int minStartingDepth = 3;     // Lowest value for the range
const int growthFactor = 1;         // Factor by which crossed over trees grow

const double punishment = 0.05;     // Punishment scalar to limit tree growth (fitness += depth * punishment)

#endif
