#ifndef POPULATION_H
#define POPULATION_H

#include "points.h"


class Population {
    public:
        // ** ASSUMES initRand() HAS BEEN CALLED! **
        Population( unsigned int nPoints, unsigned int pSize ); // constructor
        Population( unsigned int nPoints ) : Population(nPoints, 100) {} // constructor with default pop size (C++11 delegating constructors)
        ~Population() {} // Empty destructor for now

        double fitness( vector<point> points ); // Minimum Euclidean distance between all points
        
        void printPop( string title );   // Prints the population, headed by title
        void printPoints( vector<point> points );

        unsigned int getNumPoints() { return numPoints; }
        unsigned int getPopSize() { return popSize; }
        vector<member> getPop() { return pop; }
    private:
        unsigned int numPoints; // Number of points for each member in population
        unsigned int popSize;   // Total size of population
        vector<member> pop;     // The population

        void initPopulation();      // Initializes the population with random values, and calculates their fitnesses
        vector<point> genRandVec(); // Generates a random vector of points
};


#endif
