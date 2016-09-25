#ifndef EVOLVE_H
#define EVOLVE_H

#include <iostream>
#include <string>
#include <cmath>
#include <utility>
#include <vector>
#include "rand.h"
using namespace std;

const bool TESTING = 1;
const int CROSSOVER = 0;
const int MUTATION = 0;
const int SELECITON = 0;

typedef pair<string, double> keyFitType;

inline int encode( int index, char * key ); // index + key -> index
double eFitness( char * key );	// Euclidean distance
double bFitness( char * key );	// Bhatthacaryya distance
string crossover( string parentA, string parentB ); // Returns child that is the crossover of both parents
void mutate( string &chromosome ); // Mutates the chromosome in-place
string select(); // Selects an individual out of the population

int convert( char c ); 	// Converts an ASCII letter to an int to be used to index a table
char revert( int i );	// Reverts an int back to the ASCII letter it originally was
void printTable( double table[][26], string name );

#endif
