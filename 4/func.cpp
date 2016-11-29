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

// Trackers for number of core operations performed (fitness evals, mutations, etc.)
int numFitnessEvals = 0;
int numMutations = 0;
int numXovers = 0;
int numSelections = 0;

Tree * select( vector<Tree *> population ); // Selects a tree out of the population

bool compTrees( Tree * a, Tree * b) { return a->getFitness() < b->getFitness(); }
bool isIn( vector<int> t, int val );
void printPopFits( vector<Tree *> pop );
void printPopTrees( vector<Tree *> pop );
void printPopAll( vector<Tree *> pop );


// This sets everything up, kicks off evolutions, and prints results
int main() {
    initRand();         // Initialize the random number generator
    int oversizedTrees = 0;
    int biggestOversize = 0;

    int numPairs = 0;   // Number of data points to be input
    vector<p> data;     // List of pairs of real numbers x, f(x)
    vector<Tree *> pop(popSize);        // Current population
    vector<Tree *> children(popSize);   // Newly generated population consisting of modified population members
	
    // Input the dataset of function inputs and results
    std::cin >> numPairs;
    for( int i = 0; i < numPairs; i++ ) {
        p point;
        std::cin >> point.x >> point.fx;
        data.push_back(point);
    }
    
    // Initialize Heckendorn's library (see tree.h, and testTreeLibrary in tree.cpp)
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
        pop[i] = Tree::getRandTree(randMod(startingDepthRange) + minStartingDepth);
        if(TESTING) pop[i]->check();
        pop[i]->evalFitness(data);
    }

    if(DUMP) {
        printf("*** STARTING POPULATION ***\n");
        printPopAll(pop);
        printf("\n\n\n\n *** Evolution Phase *** \n");
    }


    // **** THE EVOLUTION MAGIC ****

    // Generational loop
    int GEN;
    for( GEN = 0; GEN < maxGen; GEN++ ) {
        for( int i = 0; i < popSize; i++ ) {
            //children[i] = select(pop)->copy();
            children[i] = pop[i]->copy();

            if( choose(xover) )          // Crossover
                children[i]->crossover(select(pop)); // Select individual out of current population to crossover with
            
            // TODO: variety of mutation types (enum), randomly choose
            if( choose(mutateProb) )     // Mutation
                children[i]->mutate();
            
            if(children[i]->size() > 1000) {
                oversizedTrees++;
                if(children[i]->size() > biggestOversize) biggestOversize = children[i]->size();
                children[i] = pop[i];
            } else {
                children[i]->evalFitness(data); // Update fitnesses of the modified children
            }
        } // end children loop

        // Select from children and replace non-elites in population
        for( int i = elites; i < popSize; i++ ) {
            pop[i] = select(children);
        }
            

        // Sort population by fitness
        std::sort(pop.begin(), pop.end(), compTrees); 

        if(pop[0]->getError() < desiredError) break;
        if(DUMP) { printPopAll(pop); printf("\n\n"); }
    } // end generational loop

    // TODO: bit of local search on the best individual?


    // **** OUTPUT ****

	if(STATS) {
		printf("\nFitness evaluations:\t%d\n", numFitnessEvals);
        printf("Total mutations: \t%d\n", numMutations);
        printf("Total crossovers:\t%d\n", numXovers);
        printf("Total selections:\t%d\n", numSelections);
        printf("Generations done:\t%d\n", GEN);
        printf("Oversized Trees: \t%d\n", oversizedTrees);
        printf("Biggest oversize:\t%d\n", biggestOversize);
        printf("\n");
    }

    // Output for assignment (Note: best individual is pop[0], since we assume it's sorted)
    printf("MaxGen: %d\tPopSize: %d\tXoverProb: %g\tMutateProb: %g\tElites: %d TournySize: %d\n", 
        maxGen, popSize, xover, mutateProb, elites, tournySize);
    if(STATS) {
        printf("\nDepth: %d\tSize: %d\n", pop[0]->depth(), pop[0]->size());
        printf("Error: %g\tFitness: %g\n\n", pop[0]->getError(), pop[0]->getFitness());
    }
    printf("%g\t", pop[0]->getError());
    pop[0]->print(); // This prints a newline at the end

	return 0;
} // end main



// Error = sum from i to N of (f(x_i) - f*(x_i))^2
void Tree::evalFitness( const std::vector <p> &data ) {
    fitness_ = 0;

    for( const p &point : data ) {
        setX(point.x); // Sets global value used in eval()
        fitness_ += pow((point.fx - eval()), 2); // ( f(x_i) - f*(x_i) )^2
    }

    error_ = fitness_;
    fitness_ += size_ * punishment; // Punish large trees. Assumes size is current, may need to update.

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

    //chosenDepth += randMod(growthFactor);   // Grow tree by random amount
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


// Variation of crossover that only crosses over subtrees at the same depth
// Additionally, it only chooses subtrees in range [depth/2 + 1, depth] to avoid massive damage
void Tree::equalCrossover( Tree * t ) {
    int maxDepth = std::min(depth(), t->depth());
    int minDepth = (int)(maxDepth / 2) - 1;
    int chosenDepth = randMod(minDepth) + minDepth;
    //printf("maxDepth: %d\t minDepth: %d\t chosenDepth: %d\n", maxDepth, minDepth, chosenDepth);

    Tree * swath = t->pickNode(chosenDepth)->copy();
    Tree * chosen = pickNode(chosenDepth);
    Tree * chosenParent = chosen->up();
    Side chosenSide = chosen->remove();
    free(chosen);

    chosenParent->join(chosenSide, swath);

    if(TESTING) check();
    numXovers++;
} // end equalCrossover


// Selects a chromosome out of population using simple tournament selection
// Most of this code came from Assignment 3 population.cpp
Tree * select( vector<Tree *> pop ) {
    std::vector<int> t; // The indicies of the members of the tournament

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


void printPopFits( vector<Tree *> pop ) {
    for( int i = 0; i < popSize; i++ )
        printf("[%d]\t%f\n", i, pop[i]->getFitness());
} // end printPop


void printPopTrees( vector<Tree *> pop ) {
    for( auto &t : pop )
        t->print();
} // end printPopTrees


void printPopAll( vector <Tree *> pop ) {
    for( int i = 0; i < popSize; i++ ) {
        printf("\n");
        printf("[%d]\t%f\n", i, pop[i]->getFitness());
        printf("Depth: \t%d\n", pop[i]->depth());
        printf("Size: \t%d\n", pop[i]->size());
        pop[i]->print();
    }
} // end printPopAll
