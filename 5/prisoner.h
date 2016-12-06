#ifndef PRISONER_H
#define PRISONER_H

#include <vector>
#include "rand.h"

#define TESTING 0
#define STATS 0
#define DUMP 0
#define LOCALSEARCH 0

typedef struct {
    unsigned long long int plays;
} game; 

const double desiredError = 0.0001;
const int localSearchLimit = 1000;

const int maxGen = 520;     // Maximum number of generations
const int popSize = 1024;    // Population size

const double xover = 0.5;       // Crossover Probability of an individual
const double mutateProb = 0.7;  // Mutation probability of an individual

const int tournySize = 3;       // Tournament size
const int elites = 20;          // Number of elites that persist between generations (NOTE: must be less tahn popSize!)

#endif
