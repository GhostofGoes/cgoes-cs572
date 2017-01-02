// Project: 	Assignment 4 - Function Regression
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Github:		https://github.com/GhostofGoes/cgoes-cs572
// License:		AGPLv3 until end of Fall 2016 semester. Then will convert to MITv2 once the semester is over.
// Objective of the assignment: Given inputs to a function and results of those inputs, evolve a function that gives the same results the original

#include <iostream>
#include <cstdio>

#include "func.h"
#include "opList.h"
#include "population.h"

// Used for nodeMutate
extern int numOpsTotal;   // total number of ops
extern int numOps0;       // number of nullary ops
extern int numOps1;       // number of unary ops
extern int numOps2;       // number of binary ops
extern Op **opList0;   // Nullary ops
extern Op **opList1;   // Unary ops
extern Op **opList2;   // Binary ops

// This sets everything up, kicks off evolutions, and prints results
int main() {

    // Initialize Tree library (see tree.h, and testTreeLibrary in tree.cpp)
    initOps(10); // 10?
    addOpOrTerm((char * )"+", 2, addOp);
    addOpOrTerm((char * )"-", 2, subOp);
    addOpOrTerm((char * )"*", 2, mulOp);
    addOpOrTerm((char * )"/", 2, divOp);
    addOpOrTerm((char * )"sin", 1, sinOp);
    addOpOrTerm((char * )"x", 0, xOp);
    addOpOrTerm((char * )NULL, 0, constOp);  // WARNING: null name means it is a constant!!!!

    // TODO: do we need to pass by reference or value for CUDA?

    vector<p> data = ingestData();  // Input of dataset a list of pairs of real numbers x, f(x)
    Population p1(data);                // Create a population
    std::cout << "INITIALIZED" << std::endl;
    int p1gens = p1.evolve();
    std::cout << "EVOLVED!!" << std::endl;
    Chromosome p1best = p1.getBest();
    if(LOCALSEARCH) p1best.localSearch( 1000, data ); 

	if(STATS) {
        p1.printTotalStats();
        printf("P1 - Number of Generations done:\t%d\n", p1gens);
    }

    // Output for assignment
    //printf("MaxGen: %d\tPopSize: %d\tXoverProb: %g\tMutateProb: %g\tDesired error: %g\tElites: %d TournySize: %d\n", 
     //   maxGen, popSize, xover, mutateProb, desiredError, elites, tournySize);
    if(STATS) {
        printf("\nDepth: %d\tSize: %d\n", p1best.depth(), p1best.size());
        printf("Error: %g\tFitness: %g\n\n", p1best.error(), p1best.fitness());
    }
    printf("%g\t", p1best.error());
    p1best.printTree();

	return 0;
} // end main


// Input the dataset of function inputs and results
vector<p> ingestData() {
    int numPairs = 0;   // Number of data points to be input
    vector<p> data;     // List of pairs of real numbers x, f(x)

    std::cin >> numPairs;
    for( int i = 0; i < numPairs; i++ ) {
        p point;
        std::cin >> point.x >> point.fx;
        data.push_back(point);
    }

    if(CHECKING) 
        if( data.size() != numPairs )
            std::cerr << "Mismatch in number of datapoints and the actual data input!" << std::endl;

    return data;
}

// Checks if val is in vector t
// TODO: templatize this
bool isIn( const vector<int>& t, int val ) {
    for( int i : t )
        if(i == val) return true;
    return false;
} // end isIn