// Project: 	Assignment 4 - Function Regression
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Github:		https://github.com/GhostofGoes/cgoes-cs572
// License:		AGPLv3 until end of Fall 2016 semester. Then will convert to MITv2 once the semester is over.
// If you're in the class, don't copy the code :)
// You're welcome to use it to learn silly things like I/O, C++ syntax, libary functions, etc.

// Objective of the assignment: Given inputs to a function and results of those inputs, evolve a function that gives the same results the original

#include <cstdio>

#include "func.h"
#include "tree.h"
#include "opList.h"

// Keeps track of total number of fitness evaluations performed
int numFitnessCalcs = 0; 


// This sets everything up, kicks off evolutions, and prints results
int main() {
    initRand();         // Initialize the random number generator
    Tree * pop[popSize];
    int numPairs = 0;   // Number of pairs to be input
    p * data = NULL;    // List of pairs of real numbers x, f(x)
	
    cin >> numPairs;
    data = new p[numPairs];
    for( int i = 0; i < numPairs; i++ ) {
        cin >> data[i].x >> data[i].fx;
    }

    //for( int i = 0; i < numPairs; i++ ) {
    //    printf("%f\t%f\n", data[i].x, data[i].fx);
    //}

    initOps(10);
    addOpOrTerm((char * )"+", 2, addOp);
    addOpOrTerm((char * )"-", 2, subOp);
    addOpOrTerm((char * )"*", 2, mulOp);
    addOpOrTerm((char * )"/", 2, divOp);
    addOpOrTerm((char * )"sin", 1, sinOp);
    addOpOrTerm((char * )"x", 0, xOp);
    addOpOrTerm((char * )NULL, 0, constOp);  // WARNING: null name means it is a constant!!!!

    // Initialize the population
    int depth = 10; // TODO: could randomize this?
    for( int i = 0; i < popSize; i++ ) {
        pop[i] = Tree::getRandTree(depth);
    }

    if(TESTING)
        for( int i = 0; i < popSize; i++ ) {
            //pop[i]->printIndent();
            printf("x: %f\tError: %f\n", data[i].x, pop[i]->fitness(data));
        }

	if(TESTING) 
		cout << "\nTotal number of fitness evaluations performed:\t" << numFitnessCalcs << endl;

    // Output for assignment
    printf("MaxGen: %d\tPopSize: %d\tXoverProb: %f\n", maxGen, popSize, xover);

	return 0;
} // end main


double Tree::fitness( p *data ) {
    double error = 0;

    // error = sum from i to N of (f(x_i) - f*(x_i))^2
    for( int i = 0; i < size_; i++ ) {
        setX(data[i].x);
        error += pow((data[i].fx - eval()), 2);
    }

    return error;
} // end fitness



