// Project: 	Assignment 3 - Evolution Strategies
// Author: 		Christopher Goes
// Description: Function definitions for the Population class as defined in population.h


//#include <cmath>
#include <iomanip>
//#include <algorithm>

#include "population.h"
#include "points.h"


// Constructor ** ASSUMES initRand() HAS BEEN CALLED! **
Population::Population( int nPoints, int pSize, int numGens, double mProb, double cProb, int tSize ) {
    numPoints = nPoints;
    popSize = pSize;
    generations = numGens;
    mutProb = mProb;
    crosProb = cProb;
    trnySize = tSize;

    initPopulation(); // Initialize the population
} // end Population constructor


// The main function and loop that evolves the population
void Population::evolve( OP es_op ) {
    for( int i = 0; i < generations; i++ ) {
        vector<Chromosome> children;

        // Generate children
        for( int i = 0; i < popSize; i++ ) {
            Chromosome c = select();
            if( choose(mutProb) ) {
                c.mutate(1/5, 1/5);
                c.updateFitness();
            }
            children.push_back(c);
        }

        // Select for new population
        if( es_op == PLUS ) // Plus operator (select from pop (parents) AND children)
            pop = genPlus(children);
        else // Comma operator (select from ONLY children)
            pop = genComma(children);
    }
} // end evolve


// Where the Evolution Strategies (ES) magic happens
// sigma    Mutation step size (usually 1/5)
// mu       Current individuals in the population (the set of parents during selection)
// lambda   Offspring generated in a cycle
// +        Plus operator - selection is done from BOTH the parents and the children
// ,        Comma operator - selection is done from ONLY the children
Chromosome Population::select() const {
    // Thinking simple tournament selection with eliteism for now (because it works, that's why!)
    // However, should put variables here to be able to tweak/disable stuff like eliteism
    // Could also try fitness proportional selection or uniform parent selection
    vector<int> t;

    for( int i = 0; i < trnySize; i++ ) {
        int temp;
        do {
            temp = randMod(popSize);
        } while( isIn(t, temp));
        t.push_back(temp);
    }

    double best = pop[t[0]].fitness;
    int bestInd = 0;
    for( int i = 0; i < trnySize; i++ ) {
        if(pop[t[i]].fitness > best) {
            best = pop[t[i]].fitness;
            bestInd = i;
        }
    }

    return pop[bestInd];
} // end select


Chromosome Population::select( vector<Chromosome> p, vector<Chromosome> c ) const {
    int totalSize = p.size() + c.size();
    int endLower = p.size() - 1;
    vector<int> t;

    for( int i = 0; i < trnySize; i++ ) {
        int temp;
        do {
            temp = randMod(totalSize);
        } while( isIn(t, temp));
        t.push_back(temp);
    }

    double best = p[t[0]].fitness;
    int bestInd = 0;
    for( int i = 0; i < trnySize; i++ ) {
        if(p[t[i]].fitness > best) {
            best = p[t[i]].fitness;
            bestInd = i;
        }
    }

    return p[bestInd];
    
} // end select


bool Population::isIn( vector<int> t, int val ) const {
    for( int i : t )
        if(i == val) 
            return true;
    return false;
} // end isIn


vector<Chromosome> Population::genComma( vector<Chromosome> c ) const {
    vector<Chromosome> newPop;
    for( int i = 0; i < popSize; i++ )
        newPop.push_back(select(c));
    return newPop;
} // end genComma


vector<Chromosome> Population::genPlus( vector<Chromosome> c ) const {
    vector<Chromosome> newPop;
    for( int i = 0; i < popSize; i++ )
        newPop.push_back(select(pop, c));
    return newPop;
} // end genPlus


// Crossover with only one parent is basically a sneaky way to save some of the parents when using the Comma operator
Chromosome Population::crossover( Chromosome p1, Chromosome p2 ) const {
    Chromosome child(numPoints);


    return child;
} // end crossover


Chromosome Population::getBest() const {
    double best = pop[0].fitness;
    int bestInd = 0;
    for(int i = 0; i < popSize; i++) {
        if(pop[i].fitness > best) { 
            best = pop[i].fitness;
            bestInd = i;
        }
    }
    return pop[bestInd];
} // end getBest


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


// Initializes the population with random values, and calculates their fitnesses
void Population::initPopulation() {
    for( int i = 0; i < popSize; i++ ) {
        Chromosome c( numPoints ); // Initialize a new chromosome with random values and a fitness
		pop.push_back(c); // Add chromosome to the population
	}
    if( (int)pop.size() != popSize ) { cerr << "pop.size() != popSize !!!" << endl; }
} // end initPopulation
