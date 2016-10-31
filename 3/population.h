#ifndef POPULATION_H
#define POPULATION_H


#include "points.h"  // This has definitions and includes for stuff
#include "chromosome.h"

class Population {
    public:
        // ** ASSUMES initRand() HAS BEEN CALLED! **
        Population( int nPoints, int pSize, int evos ); // constructor
        Population( int nPoints ) : Population(nPoints, 100, 10000) {} // constructor with default pop size and evolutions (C++11 delegating constructors)
        ~Population() {} // Empty destructor for now

        void evolve(); // Main evolution loop for the population
        void mutate( Chromosome c );
        Chromosome select() const; // Select an individual out of population to be a parent (I choose YOU, unique collection of points!)
        Chromosome crossover( Chromosome p1, Chromosome p2 ) const; // Combine two parents to create a child. *ahem*
        
        void printPop( string title ) const;   // Prints the population, headed by title

        int getNumPoints() const { return numPoints; }
        int getPopSize() const { return popSize; }
        vector<Chromosome> getPop() const { return pop; }

    private:
        int numPoints;     // Size of chromosome (Number of points) for each member in population
        int popSize;       // Total size of population (total # of members)
        int evolutions;    // Number of times the evolution loop is pumped

        vector<Chromosome> pop; // The population
        void initPopulation();  // Initializes the population with random values, and calculates their fitnesses
};


#endif
