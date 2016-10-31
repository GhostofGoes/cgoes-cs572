#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "points.h"

class Chromosome {
    public:
        Chromosome();
        Chromosome( int size );   // Generates a new chromosome with random values, and calculates it's fitness
        ~Chromosome() {}  // destructor

        void updateFitness();   // Minimum Euclidean distance between all points
        void print() const;     // Prints the chromosome to stdout
        void pPrint() const;    // Sorts by theta then prints

        // Leaving this stuff public for performance, especially since almost exclusivly used by Population
        int cSize;              // Size of chromosome (Number of points)
        double fitness;         // Fitness of the chromosome
        vector<point> points;   // The chromosome itself, as a array of points in polar coordinates (theta, r)
};


#endif
