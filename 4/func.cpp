// Project: 	Assignment 4 - Function Regression
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Github:		https://github.com/GhostofGoes/cgoes-cs572
// License:		AGPLv3 until end of Fall 2016 semester. Then will convert to MITv2 once the semester is over.
// If you're in the class, don't copy the code :)
// You're welcome to use it to learn silly things like I/O, C++ syntax, libary functions, etc.

// Objective of the assignment: Given inputs to a function and results of those inputs, evolve a function that gives the same results the original

#include <iostream>
#include <cstdio>
#include <algorithm>

#include "func.h"
#include "tree.h"
#include "opList.h"

// Keeps track of total number of fitness evaluations performed
int numFitnessCalcs = 0; 
int numMutations = 0;
int numXovers = 0;

Tree * select( vector<Tree *> population ); // Selects a tree out of the population
bool compTrees( Tree * a, Tree * b) { return a->getFitness() < b->getFitness(); }

// This sets everything up, kicks off evolutions, and prints results
int main() {
    initRand();         // Initialize the random number generator

    vector<Tree *> pop(popSize);
    int numPairs = 0;   // Number of pairs to be input
    p * data = NULL;    // List of pairs of real numbers x, f(x)
	
    cin >> numPairs;
    data = new p[numPairs];
    for( int i = 0; i < numPairs; i++ )
        cin >> data[i].x >> data[i].fx;

    initOps(10); // TODO: why 10?
    addOpOrTerm((char * )"+", 2, addOp);
    addOpOrTerm((char * )"-", 2, subOp);
    addOpOrTerm((char * )"*", 2, mulOp);
    addOpOrTerm((char * )"/", 2, divOp);
    addOpOrTerm((char * )"sin", 1, sinOp);
    addOpOrTerm((char * )"x", 0, xOp);
    addOpOrTerm((char * )NULL, 0, constOp);  // WARNING: null name means it is a constant!!!!

    // Initialize the population
    for( int i = 0; i < popSize; i++ )
        pop[i] = Tree::getRandTree(treeDepth);

    // **** MAIN EVOLUTION LOOP ****

    // TODO: why is it "max" generations?
    // Generations
    for( int i = 0; i < maxGen; i++ ) {
        
        for( int j = 0; j < popSize; j++ ) {
            
            // Mutate 
            // TODO: vareity of mutation types (enum), randomly choose?
            //      Maybe vary prob. of type chosen based on it's performance?
            if( choose(mutateProb) ) {

            }

            // Crossover
            if( choose(xover) ) {

            }
            // TODO: make sure we're checking the trees to ensure they're valid!!!
        }

    }

    sort(pop.begin(), pop.end(), compTrees); // Sort population by fitness
    Tree * bestIndividual = pop[0];

    // **** OUTPUT ****

    if(TESTING)
        for( int i = 0; i < popSize; i++ )
            printf("x: %f\tError: %f\n", data[i].x, pop[i]->fitness(data));

	if(TESTING) {
		printf("\nTotal of fitness evaluations performed:\t%d\n", numFitnessCalcs);
        printf("Total mutations: \t%d\n", numMutations);
        printf("Total crossovers: \t%d\n", numXovers);
    }

    // Output for assignment
    printf("MaxGen: %d\tPopSize: %d\tXoverProb: %f\n", maxGen, popSize, xover);
    printf("%f\t", bestIndividual->getFitness());
    bestIndividual->print(); // This prints a newline at the end

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


// Note: mutate probability is global (for the time being)
// Recursive?
void Tree::mutate() {
    // So we can always save the tree for later
    // Could generate a random tree, and attach it to a random part of the tree (very destructive but exploratory)
    // Could modify a random node with a new random op or term
    // Could modify a constant node with a new random constant
    //*pickNode() = 


    numMutations++;
} // end mutate


// Crosses over the two trees given as parameters
// The tree this is called on is the resulting child
void Tree::crossover() {
    

    numXovers++;
} // end crossover


Tree * select( vector<Tree *> population ) {

} // end select

