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
void updateFitnesses( std::vector<Tree *> population, p * data );

bool compTrees( Tree * a, Tree * b) { return a->getFitness() < b->getFitness(); }
bool isIn( std::vector<int> t, int val );


// This sets everything up, kicks off evolutions, and prints results
int main() {
    initRand();         // Initialize the random number generator

    int numPairs = 0;   // Number of pairs to be input
    p * data = NULL;    // List of pairs of real numbers x, f(x)
    std::vector<Tree *> pop(popSize); // The population
	
    // Input the dataset of function inputs and results
    std::cin >> numPairs;
    data = new p[numPairs];
    for( int i = 0; i < numPairs; i++ )
        std::cin >> data[i].x >> data[i].fx;

    // Initialize Heckendorn's library
    initOps(10); // TODO: why 10?
    addOpOrTerm((char * )"+", 2, addOp);
    addOpOrTerm((char * )"-", 2, subOp);
    addOpOrTerm((char * )"*", 2, mulOp);
    addOpOrTerm((char * )"/", 2, divOp);
    addOpOrTerm((char * )"sin", 1, sinOp);
    addOpOrTerm((char * )"x", 0, xOp);
    addOpOrTerm((char * )NULL, 0, constOp);  // WARNING: null name means it is a constant!!!!

    // Initialize the population with random trees
    for( int i = 0; i < popSize; i++ ) {
        pop[i] = Tree::getRandTree(treeDepth);
        pop[i]->evalFitness(data);
    }

    if(TESTING) {
        pop[0]->print();
        pop[0]->mutate();
        pop[0]->print();
    }

    // **** THE EVOLUTION MAGIC ****

    // TODO: why is it "max" generations?
    // Generational loop
    for( int i = 0; i < maxGen; i++ ) {
        
        for( auto &t : pop ) {
            
            // Mutate 
            // TODO: vareity of mutation types (enum), randomly choose?
            //      Maybe vary prob. of type chosen based on it's performance?
            if( choose(mutateProb) ) {
                t->mutate();
            }

            // Crossover
            if( choose(xover) ) {

            }
            // TODO: make sure we're checking the trees to ensure they're valid!!!
        }

        updateFitnesses(pop, data);
    } // end generational loop


    // Determine the best individual in the population
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


// Note: error == fitness
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


// Generate a random tree, and attach it to a random part of the tree (destructive but exploratory)
void Tree::mutate() {
    // Could always save the tree for later (instead of free)
    //      - Perhaps a pool for "userful" trees
    //      - Pool would have a probability to be drawn from versus a random tree generated
    // Could modify a random node with a new random op or term
    // Could modify a constant node with a new random constant

    Tree * chosen = pickNode();         // Choose a random subtree to mutate
    int chosenDepth = chosen->depth();  // Save it's depth
    Tree * chosenParent = chosen->up(); // Save it's parent
    Side chosenSide = chosen->remove(); // Save the side it's on
    
    free(chosen);   // Free old subtree's memory back to the memory pool

    chosen = getRandTree(chosenDepth);      // Generate a random tree
    chosenParent->join(chosenSide, chosen); // Attach to random part of the tree

    if(TESTING)
        check(); // Verify integrity of the complete mutated tree

    numMutations++;
} // end mutate


// Crosses over the two trees given as parameters
// The tree this is called on is the resulting child
void Tree::crossover() {
    

    numXovers++;
} // end crossover


// Selects a chromosome out of p using simple tournament selection
// Most of this code came from Assignment 3 population.cpp
Tree * select( std::vector<Tree *> pop ) {
    std::vector<int> t;

    for( int i = 0; i < tournySize; i++ ) {
        int temp;
        do {
            temp = randMod(pop.size());
        } while( isIn(t, temp));
        t.push_back(temp);
    }

    double bestFit = pop[t[0]]->getFitness(); // Fitness of the "best" seen thus far
    int bestIndex = 0; // Index of the best individual seen thus far

    for( int i = 0; i < tournySize; i++ ) {
        if(pop[t[i]]->getFitness() > bestFit) {
            bestFit = pop[t[i]]->getFitness();
            bestIndex = i;
        }
    }

    numSelections++;
    return pop[bestIndex]; 
} // end select


// Checks if val is in vector t
bool isIn( std::vector<int> t, int val ) {
    for( int i : t )
        if(i == val) return true;
    return false;
} // end isIn


void updateFitnesses( std::vector<Tree *> pop, p * data ) {
    for( auto &i : pop )
        i->evalFitness(data);
}

