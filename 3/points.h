#ifndef POINTS_H
#define POINTS_H

#include <iostream>
#include <string>
//#include <cmath>
//#include <vector>
//#include <algorithm>
#include "rand.h"

using namespace std;

const int FITNESS_FUNC = 1; // 0 = Euclidean, 1+ = Bhattacharyya
const double CROSSOVER_PROB = 0.8; // Probability of crossing over selected parents into child
const int MUTATION = 0;     // 0 = Single Swap
const double MUTATION_PROB = 1.0; // Probability of mutating the child
const int EVOLUTIONS = 100000; // # of times steady state algorithm evolves (# of runs)
const int POPSIZE = 256;    // Size of population
const int TSIZE = 3;        // Size of tournament (not really needed, since I assumed a size of 3 at some point during development)

// typedef struct {} treeType ;

double fitness();   // Generic function that allows selection of function using global variable instead of changing the call
double fastFitness();

//void mutate( int chromosome ); // Mutates the chromosome in-place using mutation function selected using global variable
// void printTable( double table[][26], string name ); // Prints a table for debugging, headed by title
// void printPopulation( string title ); // Prints the current population for debugging, headed by title

#endif
