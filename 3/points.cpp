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

// sigma    Mutation step size (usually 1/5)
// mu       NUMBER OF Current individuals in the population (the set of parents during selection)
// lambda   NUMBER OF Offspring generated in a cycle
// +        Plus operator - selection is done from BOTH the parents and the children
// ,        Comma operator - selection is done from ONLY the children

// This sets everything up, kicks off evolutions, and prints results
// The actual interesting stuff is in population.cpp/h and points.h
int main(int argc, char *argv[]) {
	int numPoints = 0;

	if (argc > 1) { numPoints = (int) stoul(argv[1]); } 	// It's an argument, convert to unsigned int
	else { cin >> numPoints; } // Don't need to cast for this case since cin does that for us

	// TODO: profile and try randf.cpp or randmt.cpp
	initRand();  // Initialize random number generator

	// Population Size = 5, Number of Generations = 10
	// Mutation Probability = 0.5, Crossover Probability = 0.5 (not used currently)
	// Tournament size = 3
	Population p1( numPoints, 32, 1000, 0.5, 0.5, 3 );
	//p1.printPop("PLUS: Pre-evolution");
	p1.evolve( PLUS );
	//p1.printPop("PLUS: Post-evolution");

	// p1.resetPop();
	// p1.printPop("COMMA: Pre-evolution");
	// p1.evolve( COMMA );
	// p1.printPop("COMMA: Post-evolution");

	//p1.getBest().printResults();
	p1.printResults();

	return 0;
} // end main
