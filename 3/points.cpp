// Project: 	Assignment 3 - Evolution Strategies
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Github:		https://github.com/GhostofGoes/cgoes-cs572
// License:		AGPLv3 until end of Fall 2016 semester. Then will convert to MITv2 once the semester is over.
// If you're in the class, don't copy the code :)
// You're welcome to use it to get un-stuck on or learn silly things like I/O, C++ syntax, libary functions, etc.

#include <cstdlib>

#include "points.h"
#include "population.h"
#include "chromosome.h"

// Keeps track of total number of fitness evaluations performed
int numFitnessCalcs = 0; 


// TODO: add ability to modify mu 
// TODO: add ability to modify lambda
// TODO: evolve parameters for population
// sigma    Mutation step size (usually 1/5)
// mu       NUMBER OF Current individuals in the population (the set of parents during selection)
// lambda   NUMBER OF Offspring generated in a cycle
// +        Plus operator - selection is done from BOTH the parents and the children
// ,        Comma operator - selection is done from ONLY the children

// This sets everything up, kicks off evolutions, and prints results
// The actual interesting stuff is in population.cpp/h and points.h
int main(int argc, char *argv[]) {
	int numPoints = 0;

	// TODO: arguments to tweak aspects of population or stuff like sigma, for testing
	if (argc > 1) { numPoints = (int) stoul(argv[1]); } 	// It's an argument, convert to unsigned int
	else { cin >> numPoints; } // Don't need to cast for this case since cin does that for us

	// TODO: profile and try randf.cpp or randmt.cpp
	initRand();  // Initialize random number generator

	// ** Example usage **
	// Size of Chromosome = numPoints
	// Population Size = 32, Number of Generations = 10000
	// Mutation Probability = 0.2, Crossover Probability = 0.5
	// Tournament Size = 3
	// Population p1( numPoints, 32, 10000, 0.2, 0.5, 3 );

	Population p1( numPoints, 32, 2000, 1.0, 0.0, 3 );
	Chromosome p1_best = p1.evolve( PLUS );
	p1_best.localSearch(10000);  // Some local search
	p1_best.printResults();

	// p1.resetPop();
	// p1.printPop("COMMA: Pre-evolution");
	// p1.evolve( COMMA );
	// p1.printPop("COMMA: Post-evolution");

	// Add an extra arg to see how many fitness evaluations were performed!
	// TODO: track fitness evaluations per-population and per-chromosome
	if(argc > 2) 
		cout << "Total number of fitness evaluations performed:\t" << numFitnessCalcs << endl;

	return 0;
} // end main
