#ifndef POPULATION_H
#define POPULATION_H


#include "points.h"  // This has definitions and includes for stuff
#include "chromosome.h"

class Population {
    public:
        // ** ASSUMES initRand() HAS BEEN CALLED! **
        Population( int nPoints, int pSize, int numGens, double mProb, double cProb, int tSize, OP op ); // constructor
        Population( int nPoints ) : Population(nPoints, 100, 10000, 0.5, 0.5, 3, 0) {} // constructor with default pop size and evolutions (C++11 delegating constructors)
        ~Population() {} // Empty destructor for now

        void evolve(); // Main evolution loop for the population
        Chromosome select( vector<Chromosome> p ) const; // Select an individual out of population to be a parent (I choose YOU, unique collection of points!)
        Chromosome select( vector<Chromosome> p, vector<Chromosome> c ) const;
        Chromosome crossover( Chromosome p1, Chromosome p2 ) const; // Combine two parents to create a child. *ahem*
        
        void printPop( string title ) const;   // Prints the population, headed by title
        void print() const;  // Basic dump of the population

        int getNumPoints() const { return numPoints; }
        int getPopSize() const { return popSize; }
        vector<Chromosome> getPop() const { return pop; }

    private:
        int numPoints;     // Size of chromosome (Number of points) for each member in population
        int popSize;       // Total size of population (total # of members)
        
        int generations;   // Number of generations (# of times the evolution loop is pumped)
        double mutProb;    // Probability of Mutation
        double crosProb;   // Probability of crossover
        int trnySize;      // Tournament size

        iOP es_op;          // Comma or Plus ES operator

        vector<Chromosome> pop; // The population
        void initPopulation();  // Initializes the population with random values, and calculates their fitnesses
};


#endif
