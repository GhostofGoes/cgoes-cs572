// Project: 	Assignment 4 - Function Regression
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Github:		https://github.com/GhostofGoes/cgoes-cs572
// License:		AGPLv3 until end of Fall 2016 semester. Then will convert to MITv2 once the semester is over.
// If you're in the class, don't copy the code :)
// You're welcome to use it to learn silly things like I/O, C++ syntax, libary functions, etc.

#include <cstdio>

#include "func.h"
#include "tree.h"
#include "opList.h"

// Keeps track of total number of fitness evaluations performed
int numFitnessCalcs = 0; 


// This sets everything up, kicks off evolutions, and prints results
int main() {
    initRand();         // Initialize the random number generator
    int maxGen = 0;
    int popSize = 0;
    int xover = 0;
    int numPairs = 0;   // Number of pairs to be input
    p * data = NULL; // Pairs of real numbers x, f(x)
	
    cin >> numPairs;
    data = new p[numPairs];
    for( int i = 0; i < numPairs; i++ ) {
        cin >> data->x >> data->fx;
    }


	if(TESTING) 
		cout << "Total number of fitness evaluations performed:\t" << numFitnessCalcs << endl;

    // Output for assignment
    printf("MaxGen: %d\tPopSize: %d\tXoverProb: %d", maxGen, popSize, xover);

	return 0;
} // end main
