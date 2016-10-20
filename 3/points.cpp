// Project: 	Assignment 3
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Github:		https://github.com/GhostofGoes/cgoes-cs572
// License:		AGPLv3 until end of Fall 2016 semester. Then will convert to MITv2 once the semester is over.
// If you're in the class, don't copy the code :)

#include "points.h"
#define TESTING 0
#define PRINT_FITNESS 1

vector< vector<point> > pop[POPSIZE];
unsigned int numPoints = 0;


int main() {
	cin >> numPoints;
	if( numPoints < 2 ) { cout << "wtf" << endl; }
	double fitness = -99.99;

	// TODO: profile and try randf.cpp or randmt.cpp
	initRand();  		// Initialize random number generator
	initPopulation();	// Initialize population with randomly generated members

	printPopulation("Testing");

	return 0;
} // end main



