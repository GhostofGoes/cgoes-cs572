// Project: 	Assignment 3 - Evolution Strategies
// Author: 		Christopher Goes
// Description: Function definitions for the Population class as defined in population.h


#include <cmath>
#include <iomanip>
#include <algorithm>

#include "population.h"
#include "points.h"


// Constructor ** ASSUMES initRand() HAS BEEN CALLED! **
Population::Population( unsigned int nPoints, unsigned int pSize ) {
    numPoints = nPoints;
    popSize = pSize;
    initPopulation(); // Initialize the population
} // end Population constructor

void Population::evolve() {

}

// Fitness calculated by finding minimum Euclidean distance between all points in the chromosome
double Population::fitness( chromosome c ) const {
    double fitness = 1.0;  

	for( point i : c ) {
		for( point j : c ) {
            // From: https://en.wikipedia.org/wiki/Euclidean_distance#Two_dimensions
			double temp = sqrt(i.r + j.r - 2 * i.r * j.r * cos(i.theta - j.theta));
            if( temp < fitness ) { fitness = temp; }
		}
	}

    if( fitness < 0 ) { cerr << "Fitness" << fitness << " is negative!!!" << endl; }
	return fitness;
} // end fitness


// Initializes the population with random values, and calculates their fitnesses
void Population::initPopulation() {
    for( unsigned int i = 0; i < popSize; i++ ) {
        member m;
        m.c = genChromosome();
        // TODO: use std::multimap to keep members sorted by Theta. 
        // Maybe use a class instead of struct for members?
        m.fitness = fitness(m.c);
		pop.push_back(m);
	}
    if( pop.size() != popSize ) { cerr << "pop.size() != popSize !!!" << endl; }
} // end initPopulation


// Generates a random chromosome as a vector of points
chromosome Population::genChromosome() const {
	chromosome c;

	for( unsigned int i = 0; i < numPoints; i++ ) {
        point p;
		p.theta = randUnit() * 2.0 * PI;
		p.r = randUnit();
        c.push_back(p);
	}
    c[0].theta = 0.0; // Lock first point to angle of 0 to reduce drift

    return c;
} // end genChromosome


// Prints the population, headed by title
void Population::printPop( string title ) const {
    cout << "\n++ Population: " << title << " ++" << endl;
    cout << setw(fieldWidth) << left << "Theta" << "\tRadius" << endl;
    for( member m : pop ) {
        cout << setw(fieldWidth) << left << "\nFitness: " << m.fitness << endl;
        printChromosome(m.c);
    }
    cout << "++++++++++++++++++++++++++" << endl;
} // end printPop


void Population::printChromosome( chromosome c ) const {
    for( point p : c ) {
        cout << setw(fieldWidth) << left << p.theta << "\t" << p.r << endl;
    }
} // end printChromosome