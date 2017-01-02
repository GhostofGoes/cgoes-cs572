#ifndef FUNC_H
#define FUNC_H

#include <vector>
#include "rand.h"
using std::vector;

#define STATS 1
#define DUMP 0
#define LOCALSEARCH 0
#define CHECKING 1

// Stores datapoint for given inputs and results for the original function (basically a tuple)
struct p {
    double x;   // Input x to f()
    double fx;  // Result of f(x)
};

struct Stats {
    int numFitnessEvals;
    int numNodeMutations;
    int numLeafMutations;
};

/***** UTILITY FUNCTIONS *****/

vector<p> ingestData(); // Input the dataset of function inputs and results

// TODO: templatize isIN
bool isIn( const vector<int>& t, int val ); // Checks if val is in vector t


#endif