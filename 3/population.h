#ifndef POPULATION_H
#define POPULATION_H

// This has definitions and includes for stuff
#include "points.h"


class Population {
    public:
        // ** ASSUMES initRand() HAS BEEN CALLED! **
        Population( unsigned int nPoints, unsigned int pSize, unsigned int evos ); // constructor
        Population( unsigned int nPoints ) : Population(nPoints, 100, 10000) {} // constructor with default pop size and evolutions (C++11 delegating constructors)
        ~Population() {} // Empty destructor for now

        void evolve(); // Main evolution loop for the population
        void mutate( chromosome c );
        chromosome select() const; // Select an individual out of population to be a parent (I choose YOU, unique collection of points!)
        chromosome crossover( chromosome p1, chromosome p2 ) const; // Combine two parents to create a child. *ahem*

        double fitness( chromosome c ) const; // Minimum Euclidean distance between all points
        
        void printPop( string title ) const;   // Prints the population, headed by title
        void printChromosome( chromosome c ) const;

        unsigned int getNumPoints() const { return numPoints; }
        unsigned int getPopSize() const { return popSize; }
        vector<member> getPop() const { return pop; }

    private:
        unsigned int numPoints;     // Size of chromosome (Number of points) for each member in population
        unsigned int popSize;       // Total size of population (total # of members)
        unsigned int evolutions;    // Number of times the evolution loop is pumped
        vector<member> pop;         // The population

        void initPopulation();              // Initializes the population with random values, and calculates their fitnesses
        chromosome genChromosome() const;   // Generates a random vector of points
};


#endif
