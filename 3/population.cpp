// Project: 	Assignment 3 - Evolution Strategies
// Author: 		Christopher Goes
// Description: Function definitions for the Population class as defined in population.h


//#include <cmath>
#include <iomanip>
//#include <algorithm>

#include "population.h"
#include "points.h"


// Constructor ** ASSUMES initRand() HAS BEEN CALLED! **
Population::Population( int nPoints, int pSize, int numGens, double mProb, double cProb, int tSize, OP op ) {
    numPoints = nPoints;
    popSize = pSize;
    generations = numGens;
    mutProb = mProb;
    crosProb = cProb;
    trnySize = tSize;
    es_op = op;

    initPopulation(); // Initialize the population
} // end Population constructor


// The main function and loop that evolves the population
void Population::evolve() {
    for( int i = 0; i < generations; i++ ) {
        vector<Chromosome> children;
        children.reserve(popSize);

        // Generate children
        for( int i = 0; i < popSize; i++ ) {
            Chromosome c = select(pop);
            if( choose(mutProb) ) {
                c.mutate(1/5, 1/5);
                c.updateFitness();
            }
            children[i] = c;
        }


        /* Select for new population */

        // Plus operator (select from pop (parents) AND children)
        if( es_op == PLUS ) { 
            vector<Chromosome> newPop;
            newPop.reserve(popSize);
            for( int i = 0; i < popSize; i++ ) {
                newPop[i] = select(pop, children);
            }
            pop = newPop;
        } 

        else { // Comma operator (select from ONLY children)
            pop = children;
        }
    }
} // end evolve


// Where the Evolution Strategies (ES) magic happens
// sigma    Mutation step size (usually 1/5)
// mu       Current individuals in the population (the set of parents during selection)
// lambda   Offspring generated in a cycle
// +        Plus operator - selection is done from BOTH the parents and the children
// ,        Comma operator - selection is done from ONLY the children
Chromosome Population::select( vector<Chromosome> p ) const {
    // Thinking simple tournament selection with eliteism for now (because it works, that's why!)
    // However, should put variables here to be able to tweak/disable stuff like eliteism
    // Could also try fitness proportional selection or uniform parent selection

    return c;
} // end select


Chromosome Population::select( vector<Chromosome> p, vector<Chromosome> c ) const {

} // end select


// Crossover with only one parent is basically a sneaky way to save some of the parents when using the Comma operator
Chromosome Population::crossover( Chromosome p1, Chromosome p2 ) const {
    Chromosome child(numPoints);


    return child;
} // end crossover


// Initializes the population with random values, and calculates their fitnesses
void Population::initPopulation() {
    for( int i = 0; i < popSize; i++ ) {
        Chromosome c( numPoints );
		pop.push_back(c);
	}
    if( (int)pop.size() != popSize ) { cerr << "pop.size() != popSize !!!" << endl; }
} // end initPopulation


// Prints the population, headed by title
void Population::printPop( string title ) const {
    cout << "\n++ Population: " << title << " ++" << endl;
    cout << setw(fieldWidth) << left << "Theta" << "\tRadius" << endl;
    for( Chromosome c : pop ) {
        cout << setw(fieldWidth) << left << "\nFitness: " << c.fitness << endl;
        c.pPrint();
    }
    cout << "++++++++++++++++++++++++++" << endl;
} // end printPop

// Basic print for visualization and possibly output
void Population::print() const {
    for( Chromosome c : pop ) {
        c.print();
    }
} // end print
