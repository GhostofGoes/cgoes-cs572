// Project: 	Assignment 3 - Evolution Strategies
// Author: 		Christopher Goes
// Description: Function definitions for the Population class as defined in population.h


#include <cmath>
#include <iomanip>
#include <algorithm>

#include "population.h"
#include "points.h"

const unsigned int fieldWidth = 10; // For spacing when printing stuff


// Constructor ** ASSUMES initRand() HAS BEEN CALLED! **
Population::Population( unsigned int nPoints, unsigned int pSize, unsigned int evos ) {
    numPoints = nPoints;
    popSize = pSize;
    evolutions = evos;
    initPopulation(); // Initialize the population
} // end Population constructor


void Population::evolve() {
    
    for( unsigned int i = 0; i < evolutions; i++ ) {

    }

} // end evolve


void Population::mutate( chromosome c ) {
    // TODO: pass by reference?
} // end mutate


chromosome Population::select() const {
    // Thinking simple tournament selection with eliteism for now (because it works, that's why!)
    // However, should put variables here to be able to tweak/disable stuff like eliteism 
    // Could also try fitness proportional selection or uniform parent selection
    chromosome c;

    return c;
} // end select


// Where some of the Evolution Strategies magic happens
// sigma    Mutation step size (usually 1/5)
// mu       Individuals in population
// lambda   Offspring generated in a cycle
// +        Plus operator
// ,        Comma operator
chromosome Population::crossover( chromosome p1, chromosome p2 ) const {
    chromosome child;


    return child;
} // end crossover


// Fitness calculated by finding minimum Euclidean distance between all points in the chromosome
double Population::fitness( chromosome c ) const {
    double fitness = 2.0;  // Diameter of unit circle

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
