#ifndef POPULATION_H
#define POPULATION_H

#include "points.h"  // This has definitions and includes for stuff
#include "chromosome.h"

const double SIGMA = (double)(1.0 / 5.0);

class Population {
    public:
        // ** ASSUMES initRand() HAS BEEN CALLED! **
        Population( int nPoints, int pSize, int numGens, double mProb, double cProb, int tSize); // constructor
        Population( int nPoints ) : Population(nPoints, 100, 10000, 0.5, 0.5, 3) {} // constructor with default pop size and evolutions (C++11 delegating constructors)
        ~Population() {} // TODO: valgrind and see if we're leaking memory

        Chromosome evolve( OP es_op ); // Main evolution loop for the population
        Chromosome select( vector<Chromosome> p ) const; // Select a chromosome out of population (I choose YOU, unique collection of points!)
        Chromosome crossover( Chromosome p1, Chromosome p2 ) const; // Combine two parents to create a child. *ahem*

        void genComma( vector<Chromosome> children );
        void genPlus( vector<Chromosome> children );
        
        void printPop( string title ) const;   // Prints the population, headed by title
        void print() const;                    // Basic dump of the population
        void printResults() const { getBest().printResults(); } // Output for assignment from the population
        void testPrint() const; // Simple dump of the fitnesses in the current population

        Chromosome getBest() const;     // Gets the best chromosome in the population
        int getNumPoints() const { return numPoints; }
        int getPopSize() const { return popSize; }
        vector<Chromosome> getPop() const { return pop; }

        void resetPop() { initPopulation(); } // Re-initializes the entire population

    private:
        int numPoints;     // Size of chromosome (Number of points) for each member in population
        int popSize;       // Total size of population (total # of members)
        
        int generations;   // Number of generations (# of times the evolution loop is pumped)
        double mutProb;    // Probability of Mutation
        double crosProb;   // Probability of crossover
        int trnySize;      // Tournament size

        // Checks if val is in vector t
        bool isIn( vector<int> t, int val) const;
        bool isIn( vector<point> t, point val ) const;

        vector<Chromosome> pop; // The population
        void initPopulation();  // Initializes the population with random values, and calculates their fitnesses
};


#endif
