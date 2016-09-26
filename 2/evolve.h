#ifndef EVOLVE_H
#define EVOLVE_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include "rand.h"
using namespace std;

const int FITNESS_FUNC = 0; // 0 = Euclidean, 1+ = Bhatthacaryya
const int CROSSOVER = 1;    // 0 = Order One, 1 = PMX
const int MUTATION = 0;     // 0 = Single Swap
const int SELECTION = 0;    // Unused currently
const int EVOLUTIONS = 10000; // # of times steady state algorithm evolves (# of runs)
const int POPSIZE = 10;     // Size of population
const int TSIZE = 3;        // Size of tournament

typedef struct {
    string key;
    double fit;
} keyFitType;

typedef struct {
    int index;
    double fit;
} indFitType;

inline int encode( int index, string key ); // index + key -> index
double fitness( string key );
double eFitness( string key );	// Euclidean distance
double bFitness( string key );	// Bhatthacaryya distance

void crossover( int parentA, int parentB, int child ); // Returns child that is the crossover of both parents
void mutate( int chromosome ); // Mutates the chromosome in-place
int select( int &parentA, int &parentB );

void orderOne( int parentA, int parentB, int child );
void pmx( int parentA, int parentB, int child );

int convert( char c ); 	// Converts an ASCII letter to an int to be used to index a table
char revert( int i );	// Reverts an int back to the ASCII letter it originally was
void printTable( double table[][26], string name );
void printPopulation( string title );

bool compSelect( indFitType a, indFitType b );

#endif
