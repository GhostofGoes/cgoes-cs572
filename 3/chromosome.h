#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "points.h"

class Chromosome {
    public:
        Chromosome() {}
        Chromosome( int size );   // Generates a new chromosome with random values, and calculates it's fitness
        ~Chromosome() {}  // destructor

        void mutate( double tSigma, double rSigma );  // Mutate the chromosome (and recalculate fitness?)
        double calcFitness( vector<point> ps ) const; // Minimum Euclidean distance between all points
        void updateFitness() { fitness = calcFitness(points); }

        void print() const;     // Prints the chromosome to stdout
        void pPrint() const;    // Sorts by theta then prints

        // Leaving this stuff public for performance, especially since almost exclusivly used by Population
        int cSize;              // Size of chromosome (Number of points)
        double mutateProb;
        double fitness;         // Fitness of the chromosome
        vector<point> points;   // The chromosome itself, as a array of points in polar coordinates (theta, r)
};


#endif
