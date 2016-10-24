#ifndef POINTS_H
#define POINTS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>
//#include <algorithm>
#include "rand.h"

using namespace std;

# define PI 3.14159265358979323846  /* "good enough" value of pi */
const unsigned int fieldWidth = 10; // For spacing when printing stuff


const int FITNESS_FUNC = 1; // 0 = Euclidean, 1+ = Bhattacharyya
const double CROSSOVER_PROB = 0.8; // Probability of crossing over selected parents into child
const int MUTATION = 0;     // 0 = Single Swap
const double MUTATION_PROB = 1.0; // Probability of mutating the child
const int EVOLUTIONS = 100000; // # of times steady state algorithm evolves (# of runs)
const int POPSIZE = 5;    // Size of population
const int TSIZE = 3;        // Size of tournament (not really needed, since I assumed a size of 3 at some point during development)


typedef struct {
    double theta;   // Range: [0, 2PI]
    double r;       // Range: [0, 1]
} point; // Single point using polar notation on a unit circle. theta = angle, r = radius

typedef struct {
    double fitness;         // Fitness of the member
    vector<point> points;   // Points for the member in polar coordinates
} member; // Member of population


/* points.cpp */
double fitness( vector<point> points );  // Fitness is calculated by finding minimum Euclidean distance between all points
double fastFitness( vector<point> points ); // A fast but sloppy fitness. Not yet implemented.


/* points_lib.cpp */
void initPopulation();          // Initializes the global population. Relies on global numPoints.
vector<point> genRandVec();     // Generates a random point vector based on the value of global numPoints

void printPopulation( string title );   // Prints the current population for debugging, headed by title
void printPoints( vector<point> ps );   // Prints all the points in the point vector



#endif
