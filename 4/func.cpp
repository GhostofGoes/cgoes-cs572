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
using std::vector;

#include "func.h"
#include "tree.h"
#include "opList.h"

// Keeps track of total number of fitness evaluations performed
int numFitnessEvals = 0; 
int numMutations = 0;
int numXovers = 0;
int numSelections = 0;

Tree * select( vector<Tree *> population ); // Selects a tree out of the population
void updateFitnesses( vector<Tree *> population, vector<p> data );

bool compTrees( Tree * a, Tree * b) { return a->getFitness() < b->getFitness(); }
bool isIn( vector<int> t, int val );
void printPop( vector<Tree *> pop );


// This sets everything up, kicks off evolutions, and prints results
int main() {
    initRand();         // Initialize the random number generator

    int numPairs = 0;   // Number of data points to be input
    vector<p> data;     // List of pairs of real numbers x, f(x)
    vector<Tree *> pop(popSize);    // The population
    vector<Tree *> children(popSize); // Population consisting of modified population members
	
    // Input the dataset of function inputs and results
    std::cin >> numPairs;
    for( int i = 0; i < numPairs; i++ ) {
        p point;
        std::cin >> point.x >> point.fx;
        data.push_back(point);
    }
    
    // Initialize Heckendorn's library
    initOps(10); // TODO: why 10? but it works so i don't question it
    addOpOrTerm((char * )"+", 2, addOp);
    addOpOrTerm((char * )"-", 2, subOp);
    addOpOrTerm((char * )"*", 2, mulOp);
    addOpOrTerm((char * )"/", 2, divOp);
    addOpOrTerm((char * )"sin", 1, sinOp);
    addOpOrTerm((char * )"x", 0, xOp);
    addOpOrTerm((char * )NULL, 0, constOp);  // WARNING: null name means it is a constant!!!!

    // Initialize the population with random trees
    for( int i = 0; i < popSize; i++ ) {
        pop[i] = Tree::getRandTree(startingDepth);
        if(TESTING) pop[i]->check();
        pop[i]->evalFitness(data);
    }



    // **** THE EVOLUTION MAGIC ****

    // TODO: check for error <= 0.01, exit early if we reach it
    // Generational loop
    for( int GEN = 0; GEN < maxGen; GEN++ ) {
        
        for( int i = 0; i < popSize; i++ ) {
            children[i] = select(pop)->copy();

            if( choose(xover) )           // Crossover
                children[i]->crossover(select(pop)); // Select individual out of population to crossover with
            
            // TODO: variety of mutation types (enum), randomly choose
            if( choose(mutateProb) )     // Mutation
                children[i]->mutate();
        }

        updateFitnesses(pop, data);
    } // end generational loop

    // Determine the best individual in the population
    std::sort(pop.begin(), pop.end(), compTrees); // Sort population by fitness

    // TODO: bit of local search on the best individual?

    // **** OUTPUT ****

	if(STATS) {
		printf("\nFitness evaluations:\t%d\n", numFitnessEvals);
        printf("Total mutations: \t%d\n", numMutations);
        printf("Total crossovers:\t%d\n", numXovers);
        printf("Total selections:\t%d\n\n", numSelections);
    }

    // Output for assignment
    printf("MaxGen: %d\tPopSize: %d\tXoverProb: %f\n", maxGen, popSize, xover);
    printf("%f\t", pop[0]->getFitness());
    pop[0]->print(); // This prints a newline at the end

	return 0;
} // end main


// Error = sum from i to N of (f(x_i) - f*(x_i))^2
void Tree::evalFitness( const std::vector <p> &data ) {
    fitness_ = 0;

    for( const p &point : data ) {
        setX(point.x);
        fitness_ += pow((point.fx - eval()), 2);
    }

    numFitnessEvals++;
} // end fitness


// Generate a random tree, and attach it to a random part of the tree (destructive but exploratory)
void Tree::mutate() {
    // Could always save the tree for later (instead of free)
    //      - Perhaps a pool for "userful" trees
    //      - Pool would have a probability to be drawn from versus a random tree generated
    // Could modify a random node with a new random op or term
    // Could modify a constant node with a new random constant

    Tree * chosen = pickNode();             // Choose a random subtree to mutate
    int chosenDepth = chosen->depth();      // Save it's depth
    Tree * chosenParent = chosen->up();     // Save it's parent
    Side chosenSide = chosen->remove();     // Save the side it's on, whilst trimming from tree
    free(chosen);                           // Release old subtree to the memory pool

    chosenDepth += randMod(growthFactor) + 1;   // Grow tree by random amount (profile this)
    chosen = getRandTree(chosenDepth);      // Generate a random tree
    chosenParent->join(chosenSide, chosen); // Attach to random part of the tree

    if(TESTING) check();                    // Verify integrity of the complete mutated tree
    numMutations++;
} // end mutate


// Crosses over a random swath of the given tree with the current tree
// Similiar methodology as mutate()
void Tree::crossover( Tree * t ) {
    Tree * swath = t->pickNode()->copy();   // Grab a random swath from the given tree
    Tree * chosen = pickNode();             // Choose a random subtree to replace with the xover'd swath
    Tree * chosenParent = chosen->up();     // Save it's parent
    Side chosenSide = chosen->remove();     // Save the side it's on, whilst trimming from tree
    free(chosen);                           // Release old subtree to the memory pool

    chosenParent->join(chosenSide, swath);  // Insert the swath into the tree

    if(TESTING) check();                    // Verify integrity of the modified tree
    numXovers++;
} // end crossover


// Selects a chromosome out of population using simple tournament selection
// Most of this code came from Assignment 3 population.cpp
Tree * select( vector<Tree *> pop ) {
    std::vector<int> t;

    for( int i = 0; i < tournySize; i++ ) {
        int temp;
        do {
            temp = randMod(pop.size());
        } while( isIn(t, temp));
        t.push_back(temp);
    }

    double bestFit = pop[t[0]]->getFitness(); // Fitness of the "best" seen thus far
    int bestIndex = t[0]; // Index of the best individual seen thus far

    for( int i = 0; i < tournySize; i++ ) {
        if(pop[t[i]]->getFitness() < bestFit) {
            bestFit = pop[t[i]]->getFitness();
            bestIndex = i;
        }
    }

    numSelections++;
    return pop[bestIndex]; 
} // end select


// Checks if val is in vector t
bool isIn( vector<int> t, int val ) {
    for( int i : t )
        if(i == val) return true;
    return false;
} // end isIn


void updateFitnesses( vector<Tree *> pop, vector<p> data ) {
    for( auto &i : pop )
        i->evalFitness(data);
} // end updateFitnesses


void printPop( vector<Tree *> pop ) {
    for( int i = 0; i < popSize; i++ )
        printf("[%d]\t%f\n", i, pop[i]->getFitness());
} // end printPop
