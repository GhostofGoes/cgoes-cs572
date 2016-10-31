// Project: 	Assignment 3 - Evolution Strategies
// Author: 		Christopher Goes
// Description: Function definitions for the Chromosome class as defined in chromosome.h

#include <cmath>
#include <iomanip>
#include <algorithm>

#include "chromosome.h"

Chromosome::Chromosome( int size ) {
    cSize = size;
    mutateProb = 1.0 / (double)cSize;

    // Generates a random chromosome as a vector of points
    for( int i = 0; i < cSize; i++ ) {
        point p;
		p.theta = randUnit() * 2.0 * PI;
		p.r = randUnit();
        points.push_back(p);
	}
    points[0].theta = 0.0;      // Lock first point to angle of 0 to reduce drift
    fitness = calcFitness();    // Calculate the fitness of the new point vector
} // end Chromosome


// sigma    Mutation step size (usually 1/5)
// Possible modification: per-dimension sigmas
void Chromosome::mutate( double tSigma, double rSigma ) {
    for( point p : points ) {
        if(choose(mutateProb)) { // Mutate only 1-2 of the points usually
            point.theta += randNorm(tSigma);
            point.r += randNorm(rSigma);
        }
    }
} // end mutate


// Fitness calculated by finding minimum Euclidean distance between all points in the chromosome
double Chromosome::calcFitness( vector<point> ps ) const {
    fit = 2.0;  // Diameter of unit circle
    for( point i : ps ) {
		for( point j : ps ) {
            // From: https://en.wikipedia.org/wiki/Euclidean_distance#Two_dimensions
			double temp = sqrt(i.r + j.r - 2 * i.r * j.r * cos(i.theta - j.theta));
            if( temp < fit ) { fit = temp; }
		}
	}
    return fit;
} // end calcFitness


void Chromosome::print() const {
    vector<point> ps = points;
    sort( ps.begin(), ps.end(), [](point a, point b){ return a.theta < b.theta; } );
    for( point p : points )
        cout << p.theta << " " << p.r << endl;
} // end print


// Pretty Print - Print sorted by Theta
void Chromosome::pPrint() const {
    vector<point> ps = points;
    sort( ps.begin(), ps.end(), [](point a, point b){ return a.theta < b.theta; } );
    for( point p : ps )
        cout << setw(fieldWidth) << left << p.theta << "\t" << p.r << endl;
} // end pPrint

