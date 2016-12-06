// Project: 	Assignment 5 - Iterated Prisoner's Delimma - EXTRA CREDIT
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Github:		https://github.com/GhostofGoes/cgoes-cs572
// License:		AGPLv3 until end of Fall 2016 semester. Then will convert to MITv2 once the semester is over.
// If you're in the class, don't copy the code :)
// You're welcome to use it to learn silly things like I/O, C++ syntax, libary functions, etc.

// Objective of the assignment: Explore the idea of evolution without an explicit fitness function, but rather a "fitness relation"

#include <iostream>
#include <cstdio>
#include <algorithm>
using std::vector;

#include "prisoner.h"

// Trackers for number of core operations performed (fitness evals, mutations, etc.)
int numFitnessEvals = 0; // Keeps track of total number of fitness evaluations performed
int numMutations = 0;
int numXovers = 0;
int numSelections = 0;
double preLocalSearchError = 0.0;
int localSearchImprovements = 0;

// Simple helper functions
bool isIn( const vector<int>& t, int val ); // Used for selection

// This sets everything up, kicks off evolutions, and prints results
int main( int argc, char * argv[] ) {
    initRand();         // Initialize the random number generator

    // Initialize the population

    // Generational loop
    int GEN;
    for( GEN = 0; GEN < maxGen; GEN++ ) {

    } // end generational loop

    // **** OUTPUT ****

	if(STATS) {
		printf("\nFitness evaluations:\t%d\n", numFitnessEvals);
        printf("Total mutations: \t%d\n", numMutations);
        printf("Total crossovers:\t%d\n", numXovers);
        printf("Total selections:\t%d\n", numSelections);
        printf("Generations done:\t%d\n", GEN);
        if(LOCALSEARCH) {
            printf("\nPre-LocalSearch Error: %g\n", preLocalSearchError);
            printf("Local Search Improvements: %d\n", localSearchImprovements);
        }
        printf("\n");
    }

    // Output for assignment
    printf("MaxGen: %d\tPopSize: %d\tXoverProb: %g\tMutateProb: %g\tDesired error: %g\tElites: %d TournySize: %d\n", 
        maxGen, popSize, xover, mutateProb, desiredError, elites, tournySize);

	return 0;
} // end main


// Checks if val is in vector t
bool isIn( const vector<int>& t, int val ) {
    for( int i : t )
        if(i == val) return true;
    return false;
} // end isIn
