#ifndef EVOLVE_H
#define EVOLVE_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include "rand.h"
using namespace std;

const int FITNESS_FUNC = 0;
const int CROSSOVER = 0;
const int MUTATION = 0;
const int SELECITON = 0;
const int RUNS = 5;
const int POPSIZE = 5;
const int TSIZE = 3;

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

int convert( char c ); 	// Converts an ASCII letter to an int to be used to index a table
char revert( int i );	// Reverts an int back to the ASCII letter it originally was
void printTable( double table[][26], string name );
void printPopulation( string title );

bool compSelect( indFitType a, indFitType b );

#endif
