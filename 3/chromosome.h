#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "points.h"


class Chromosome {
    public:
        Chromosome() { cSize = 0; fitness = 0;} // Simple constructor
        Chromosome( int size );   // Generates a new chromosome with random values, and calculates it's fitness
        Chromosome( int size, double initVal ); // Initializes points with initVal
        ~Chromosome() {}  // TODO: valgrind and see if we're leaking memory

        void mutate( double tSigma, double rSigma );  // Mutate the chromosome and updates it's fitness
        vector<point> mutate( double tSigma, double rSigma, vector<point> ps ) const;

        double calcFitness( vector<point> ps ) const; // Minimum Euclidean distance between all points
        void updateFitness() { fitness = calcFitness(points); }

        void localSearch( int iterations ); // Performs a local search on the chromosome's points for the specified number of iterations

        void print() const;        // Sorts by theta then prints
        void printResults() const;  // Prints points in format specified by assignment, sorted by theta

        // Leaving this stuff public for performance, especially since almost exclusivly used by Population
        int cSize;              // Size of chromosome (Number of points)
        double mutateProb;      // Probability of mutating a point
        double fitness;         // Fitness of the chromosome
        vector<point> points;   // The chromosome itself, as a array of points in polar coordinates (theta, r)
};


#endif
