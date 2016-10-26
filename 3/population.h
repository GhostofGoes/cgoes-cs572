#ifndef POPULATION_H
#define POPULATION_H

#include "points.h"


class Population {
    public:
        // ** ASSUMES initRand() HAS BEEN CALLED! **
        Population( unsigned int nPoints, unsigned int pSize ); // constructor
        Population( unsigned int nPoints ) : Population(nPoints, 100) {} // constructor with default pop size (C++11 delegating constructors)
        ~Population() {} // Empty destructor for now

        void evolve();
        void mutate( chromosome c );

        double fitness( chromosome c ) const; // Minimum Euclidean distance between all points
        
        void printPop( string title ) const;   // Prints the population, headed by title
        void printChromosome( chromosome c ) const;

        unsigned int getNumPoints() const { return numPoints; }
        unsigned int getPopSize() const { return popSize; }
        vector<member> getPop() const { return pop; }

    private:
        unsigned int numPoints; // Size of chromosome (Number of points) for each member in population
        unsigned int popSize;   // Total size of population (total # of members)
        vector<member> pop;     // The population

        void initPopulation();              // Initializes the population with random values, and calculates their fitnesses
        chromosome genChromosome() const;   // Generates a random vector of points
};


#endif
