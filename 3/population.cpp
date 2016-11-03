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


// Where the Evolution Strategies (ES) magic happens
Chromosome Population::evolve( OP es_op ) {

    // Generational loop that evolves the population
    for( int i = 0; i < generations; i++ ) {
        vector<Chromosome> children;

        // Generate children
        for( int i = 0; i < popSize; i++ ) {
            Chromosome c;
            if( choose(crosProb) ) {
                Chromosome p1 = select(pop);
                Chromosome p2 = select(pop);
                c = crossover(p1, p2);
            } else {
                c = select(pop);
            }

            if( choose(mutProb) ) {
                c.mutate(SIGMA, SIGMA);
                c.updateFitness();
            }
            children.push_back(c);
        }

        // Select for new population
        if( es_op == PLUS ) // Plus operator (select from pop (parents) AND children)
            genPlus(children);
        else // Comma operator (select from ONLY children)
            genComma(children);
    }

    return getBest();
} // end evolve


// Simple tournament selection
// TODO: Could try fitness proportional selection or uniform parent selection at some point
Chromosome Population::select( vector<Chromosome> p ) const {
    vector<int> t;

    for( int i = 0; i < trnySize; i++ ) {
        int temp;
        do {
            temp = randMod(p.size());
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

bool Population::isIn( vector<point> t, point val ) const {
    for( point i : t )
        if(i.theta == val.theta && i.r == val.r)
            return true;
    return false;
}

// TODO: pretty sure i'm doing this wrong still. 
// I'm dumb and still not understanding/remembering even after people explain to me.
void Population::genComma( vector<Chromosome> children ) {    
    for( int i = 0; i < popSize; i++ )
        pop[i] = select(children);
} // end genComma


void Population::genPlus( vector<Chromosome> children ) {
    vector<Chromosome> newPop;
    pop.insert( pop.end(), children.begin(), children.end()); // Add children to current population

    for( int i = 0; i < popSize; i++ )
        newPop.push_back(select(pop));

    pop = newPop;
} // end genPlus


// Crossover with only one parent is basically a sneaky way to save some of the parents when using the Comma operator
Chromosome Population::crossover( Chromosome p1, Chromosome p2 ) const {
    Chromosome c(numPoints, 0.0);
    int swathLen = randMod(numPoints - 1); // TODO: tweak this?
    int swathStart = randMod(numPoints - swathLen - 1);
    int swathEnd = swathStart + swathLen;
    vector<point> swath;
    vector<point> leftover;

    // Grab swath from parent 1 and put into child
    for( int j = swathStart; j < swathEnd; j++ ) {
        swath.push_back(p1.points[j]);
        c.points[j] = p1.points[j];
    }

    // Grab genes from parent 2 that aren't in swath from parent 1
    for( int i = 0; i < numPoints; i++ ) {
        if( !isIn(swath, p2.points[i]) ) {
            leftover.push_back(p2.points[i]);
        }
    }

    // Put the genes we grabbed from parent 2 into the child's open spots
    int temp = 0;
    for( int i = 0; i < swathStart; i++ ) {
        c.points[i] = leftover[temp];
        temp++;
    }
    for( int i = swathEnd; i < numPoints; i++ ) {
        c.points[i] = leftover[temp];
        temp++;
    }

    c.updateFitness();
    return c;
} // end crossover


Chromosome Population::getBest() const {
    double best = pop[0].fitness;
    int bestInd = 0;

    for(int i = 1; i < popSize; i++) {
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
    for( Chromosome c : pop )
        c.print();
} // end print

void Population::testPrint() const {
    cout << "\n++++++++++++++++++++++++++" << endl;
    for( Chromosome c : pop ) {
        cout << "Fitness: " << c.fitness << endl;
    }
}

// Initializes the population with random values, and calculates their fitnesses
void Population::initPopulation() {
    for( int i = 0; i < popSize; i++ ) {
        Chromosome c( numPoints ); // Initialize a new chromosome with random values and a fitness
		pop.push_back(c); // Add chromosome to the population
	}
    if( (int)pop.size() != popSize ) { cerr << "pop.size() != popSize !!!" << endl; }
} // end initPopulation
