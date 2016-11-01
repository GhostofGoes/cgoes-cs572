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
    updateFitness();    // Calculate the fitness of the new point vector
} // end Chromosome


// sigma    Mutation step size (usually 1/5)
// Possible modification: per-dimension sigmas
void Chromosome::mutate( double tSigma, double rSigma ) {
    for( point p : points ) {
        if(choose(mutateProb)) { // Mutate only 1-2 of the points usually
            double temp = randNorm(tSigma);
            if( temp + p.theta > 2.0*PI ) p.theta = temp - ((2.0*PI) - p.theta); // Remove amount that pushed us past 2PI, so its (0 + whats left over)
            else p.theta += temp;

            temp = randNorm(rSigma);
            if(temp + p.r > 1.0) p.r = -1.0 + (temp - ((1.0) - p.r)); // Remove amount that pushed us past 1.0, so its (-1.0 + whats left over)
            else p.r += temp;
        }
    }
} // end mutate


// Fitness calculated by finding minimum Euclidean distance between all points in the chromosome
double Chromosome::calcFitness( vector<point> ps ) const {
    double fit = 2.0;  // Diameter of unit circle
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


// Prints in format specified by assignment (less readable for debugging)
void Chromosome::printResults() const {
    vector<point> ps = points;
    sort( ps.begin(), ps.end(), [](point a, point b){ return a.theta < b.theta; } );
    cout << "** " << cSize << endl;
    for( point p : ps )
        cout << "***\t"  << p.theta << "\t" << p.r << endl;
    cout << "***\tFit:\t" << fitness << endl;
} // end printResults
