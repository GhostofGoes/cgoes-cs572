// Project: 	Assignment 3 - Evolution Strategies
// Author: 		Christopher Goes
// Description: Function definitions for the Chromosome class as defined in chromosome.h

#include <cmath>
#include <iomanip>
#include <algorithm>

#include "chromosome.h"

Chromosome::Chromosome( int size ) {
    cSize = size;

    // Generates a random chromosome as a vector of points
    for( int i = 0; i < cSize; i++ ) {
        point p;
		p.theta = randUnit() * 2.0 * PI;
		p.r = randUnit();
        points.push_back(p);
	}
    points[0].theta = 0.0;  // Lock first point to angle of 0 to reduce drift
    updateFitness();        // Calculate the fitness of the new point vector
}


// Fitness calculated by finding minimum Euclidean distance between all points in the chromosome
void Chromosome::updateFitness() {
    fitness = 2.0;  // Diameter of unit circle

	for( point i : points ) {
		for( point j : points ) {
            // From: https://en.wikipedia.org/wiki/Euclidean_distance#Two_dimensions
			double temp = sqrt(i.r + j.r - 2 * i.r * j.r * cos(i.theta - j.theta));
            if( temp < fitness ) { fitness = temp; }
		}
	}

    if( fitness < 0 ) { cerr << "Fitness" << fitness << " is negative!!!" << endl; }
} // end updateFitness


void Chromosome::print() const {
    for( point p : points )
        cout << setw(fieldWidth) << left << p.theta << "\t" << p.r << endl;
} // end print


// Pretty Print - Print sorted by Theta
void Chromosome::pPrint() const {
    vector<point> ps = points;
    sort( ps.begin(), ps.end(), [](point a, point b){ return a.theta < b.theta; } );
    for( point p : ps )
        cout << setw(fieldWidth) << left << p.theta << "\t" << p.r << endl;
} // end pPrint

