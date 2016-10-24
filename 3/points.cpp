// Project: 	Assignment 3 - Evolution Strategies
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Github:		https://github.com/GhostofGoes/cgoes-cs572
// License:		AGPLv3 until end of Fall 2016 semester. Then will convert to MITv2 once the semester is over.
// If you're in the class, don't copy the code :)

#include "points.h"
#define TESTING 0
#define PRINT_FITNESS 1

vector<member> pop[POPSIZE];
unsigned int numPoints = 0;


int main(int argc, char *argv[]) {

	// Is our N being input on commandline or stdin?
	if (argc > 1) { numPoints = stol(argv[1]); }
	else { cin >> numPoints; } // Don't need to cast here since cin does that for us
	if( numPoints < 2 ) { cout << "wtf" << endl; return 1; } // sanity check

	double fitness = -99.99;

	// TODO: profile and try randf.cpp or randmt.cpp
	initRand();  		// Initialize random number generator
	initPopulation();	// Initialize population with randomly generated members

	printPopulation("Testing");

	return 0;
} // end main


// Fitness calculated by finding minimum Euclidean distance between all points
double fitness( vector<point> points ) {
	double fitness = -99.99;  // Weird number for obvious errors

	for(int i = 0; i < points.size(); i++) {

	}

	return fitness;
} // end fitness

// A fast but sloppy fitness. TODO: Not yet implemented
double fastFitness( vector<point> points ) {
	double fitness = -99.99;  // Weird number for obvious errors

	return fitness;
} // end fastFitness


