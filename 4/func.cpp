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
#include <vector>

#include "func.h"
#include "tree.h"
#include "opList.h"

// Keeps track of total number of fitness evaluations performed
int numFitnessCalcs = 0; 
int numMutations = 0;
int numXovers = 0;
int numSelections = 0;

Tree * select( std::vector<Tree *> population ); // Selects a tree out of the population
bool compTrees( Tree * a, Tree * b) { return a->getFitness() < b->getFitness(); }
bool isIn( std::vector<int> t, int val );


// This sets everything up, kicks off evolutions, and prints results
int main() {
    initRand();         // Initialize the random number generator

    std::vector<Tree *> pop(popSize);
    int numPairs = 0;   // Number of pairs to be input
    p * data = NULL;    // List of pairs of real numbers x, f(x)
	
    std::cin >> numPairs;
    data = new p[numPairs];
    for( int i = 0; i < numPairs; i++ )
        std::cin >> data[i].x >> data[i].fx;

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

    std::sort(pop.begin(), pop.end(), compTrees); // Sort population by fitness
    Tree * bestIndividual = pop[0];

    // **** OUTPUT ****

    if(TESTING)
        for( int i = 0; i < popSize; i++ )
            printf("x: %f\tError: %f\n", data[i].x, pop[i]->getFitness());

	if(TESTING) {
		printf("\nTotal of fitness evaluations performed:\t%d\n", numFitnessCalcs);
        printf("Total mutations: \t%d\n", numMutations);
        printf("Total crossovers: \t%d\n", numXovers);
        printf("Total selections: \t%d\n", numSelections);
    }

    // Output for assignment
    printf("MaxGen: %d\tPopSize: %d\tXoverProb: %f\n", maxGen, popSize, xover);
    printf("%f\t", bestIndividual->getFitness());
    bestIndividual->print(); // This prints a newline at the end

	return 0;
} // end main


double Tree::evalFitness( p *data ) {
    double error = 0;

    // error = sum from i to N of (f(x_i) - f*(x_i))^2
    for( int i = 0; i < size_; i++ ) {
        setX(data[i].x);
        error += pow((data[i].fx - eval()), 2);
    }

    fitness_ = error;
    numFitnessCalcs++;
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


// Selects a chromosome out of p using simple tournament selection
// Most of this code came from Assignment 3 population.cpp
Tree * select( std::vector<Tree *> p ) {
    std::vector<int> t;

    for( int i = 0; i < tournySize; i++ ) {
        int temp;
        do {
            temp = randMod(p.size());
        } while( isIn(t, temp));
        t.push_back(temp);
    }

    double bestFit = p[t[0]]->getFitness(); // Fitness of the "best" seen thus far
    int bestIndex = 0; // Index of the best individual seen thus far

    for( int i = 0; i < tournySize; i++ ) {
        if(p[t[i]]->getFitness() > bestFit) {
            bestFit = p[t[i]]->getFitness();
            bestIndex = i;
        }
    }

    numSelections++;
    return p[bestIndex]; 
} // end select


// Checks if val is in vector t
bool isIn( std::vector<int> t, int val ) {
    for( int i : t )
        if(i == val) return true;
    return false;
} // end isIn

