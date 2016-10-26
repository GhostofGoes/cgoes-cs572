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


// This sets everything up, kicks off evolutions, and prints results
// The actual interesting stuff is in population.cpp/h and points.h
int main(int argc, char *argv[]) {
	unsigned int numPoints = 0;

	// Is our N being input on commandline or stdin?
	if (argc > 1) { numPoints = (unsigned int) stoul(argv[1]); } 	// It's an argument, convert to unsigned int
	else { cin >> numPoints; } // Don't need to cast for this case since cin does that for us

	// TODO: profile and try randf.cpp or randmt.cpp
	initRand();  // Initialize random number generator

	Population p1( numPoints, 5, 10 ); // Create a population of size 5 that evolves 10 times
	p1.printPop("Testing");
	p1.evolve();
	p1.printPop("Post-evolution");

	return 0;
} // end main
