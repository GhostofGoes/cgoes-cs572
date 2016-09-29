#ifndef EVOLVE_H
#define EVOLVE_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include "rand.h"

#define convert(c) ((int)(c - 97))
//#define revert(i) ((char)(i + 97))

using namespace std;

const int FITNESS_FUNC = 1; // 0 = Euclidean, 1+ = Bhattacharyya
const double CROSSOVER_PROB = 0.8; // Probability of crossing over selected parents into child
const int MUTATION = 0;     // 0 = Single Swap
const double MUTATION_PROB = 1.0; // Probability of mutating the child
const int EVOLUTIONS = 100000; // # of times steady state algorithm evolves (# of runs)
const int POPSIZE = 256;    // Size of population
const int TSIZE = 3;        // Size of tournament (not really needed, since I assumed a size of 3 at some point during development)
//const double bPunishment = 0.99;
//const double ePunishment = 1.05;

typedef struct {
    string key;
    double fit;
} keyFitType; // Used for the population to store an individuals key and it's fitness

typedef struct {
    int index;
    double fit;
} indFitType; // Custom type for tournament selection

double fitness( string key );   // Generic function that allows selection of function using global variable instead of changing the call
double eFitness( string key );	// Euclidean distance to evaluate key fitness
double bFitness( string key );	// Bhattacharyya distance to evaluate key fitness

void mutate( int chromosome ); // Mutates the chromosome in-place using mutation function selected using global variable
int select( int &parentA, int &parentB ); // Selection function for choosing parents, returns individiual who lost and will be overwritten by child

void pmx( int parentA, int parentB, int child ); // PMX Crossover

void printTable( double table[][26], string name ); // Prints a table for debugging, headed by title
void printPopulation( string title ); // Prints the current population for debugging, headed by title

bool compSelect( indFitType a, indFitType b ); // Used to sort individuals in tournament selection

#endif
