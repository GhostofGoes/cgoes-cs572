#ifndef EVOLVE_H
#define EVOLVE_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include "rand.h"

#define convert(c) ((int)(c - 97))
#define revert(i) ((char)(i + 97))

using namespace std;

const int FITNESS_FUNC = 1; // 0 = Euclidean, 1+ = Bhatthacaryya
const double CROSSOVER_PROB = 0.9;
const int MUTATION = 0;     // 0 = Single Swap
const double MUTATION_PROB = 0.5;
const int SELECTION = 0;    // Unused currently
const int EVOLUTIONS = 10000; // # of times steady state algorithm evolves (# of runs)
const int POPSIZE = 500;     // Size of population
const int TSIZE = 3;        // Size of tournament

typedef struct {
    string key;
    double fit;
} keyFitType;

typedef struct {
    int index;
    double fit;
} indFitType;

double fitness( string key );
double eFitness( string key );	// Euclidean distance
double bFitness( string key );	// Bhatthacaryya distance

void mutate( int chromosome ); // Mutates the chromosome in-place
int select( int &parentA, int &parentB );

void pmx( int parentA, int parentB, int child );

void printTable( double table[][26], string name );
void printPopulation( string title );

bool compSelect( indFitType a, indFitType b );

#endif
