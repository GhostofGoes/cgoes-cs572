// Project: 	Assignment 3 - Evolution Strategies
// Author: 		Christopher Goes
// Description: Function definitions for the Chromosome class as defined in chromosome.h

#include <cmath>
#include <iomanip>
#include <algorithm>

#include "chromosome.h"

extern int numFitnessCalcs; // Keeps track of total number of fitness evaluations performed
const double SIGMA = (double)(1.0 / 5.0);


// Generates a new chromosome with random values, and calculates it's fitness
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
    sort( points.begin(), points.end(), [](point a, point b){ return a.theta < b.theta; } );
    updateFitness();    // Calculate the fitness of the new point vector
} // end Chromosome


// Initializes points with initVal
// TODO: could be fancy and use a function pointer to try different rand libraries (python would be nice sigh)
Chromosome::Chromosome( int size, double initVal ) {
    cSize = size;
    mutateProb = 1.0 / (double)cSize;

    for( int i = 0; i < cSize; i++ ) {
        point p;
		p.theta = initVal;
		p.r = initVal;
        points.push_back(p);
	}

    fitness = 0.0;
} // end Chromosome


// Version of mutate that modifies the chromosome's points and update's its fitness
void Chromosome::mutate( double tSigma, double rSigma ) {
    points = mutate(tSigma, rSigma, points);
    updateFitness();
} // end mutate


// Mutates the given chromosome (vector of points) by incrementing theta and radius for 1-2 of the points
// sigma    Mutation step size (usually 1/5) (tSigma for Theta, rSigma for Radius)
// Returns the mutated vector of points
// TODO: considoring doing a decrement sometimes instead of an increment (Perhaps a seperate mutate function for this, so caller can decide)
// TODO: perhaps tweak only the radius OR theta for a point
// Possible modification: per-dimension sigmas (if we want to go into higher dimensions in the future)
vector<point> Chromosome::mutate( double tSigma, double rSigma, vector<point> ps ) const {
    vector<point> pts = ps;

    for( point &p : pts ) {
        if(choose(mutateProb)) { // Mutate only 1-2 of the points usually
            double temp = randNorm(tSigma) + p.theta;
            // Remove amount that pushed us past 2PI, so its (0 + whats left over)
            if( temp > 2.0*PI ) p.theta = temp - (2.0*PI); 
            else if( temp < 0.0 ) p.theta = temp + (2.0*PI);
            else p.theta = temp;

            temp = randNorm(rSigma) + p.r;
            if(temp > 1.0) p.r = 1.0;
            else if(temp < -1.0) p.r = -1.0;
            else p.r = temp;
        }
    }

    return pts;
} // end mutate


// Fitness is calculated by finding minimum Euclidean distance between all points in ps
double Chromosome::calcFitness( vector<point> ps ) const {
    double fit = 2.0;  // Diameter of unit circle [-1.0 to 1.0]

    for( point i : ps ) {
		for( point j : ps ) {
            // TODO: comp function as a define or something, as i'm doing this in several places
            // This check prevents comparing a point with itself, as it will always evaevaluate to zero
            if( i.theta == j.theta && i.r == j.r ) continue;

            // Euclidian Distance, from: https://en.wikipedia.org/wiki/Euclidean_distance#Two_dimensions
			double temp = sqrt( pow(i.r, 2.0) + pow(j.r, 2.0) - 2.0 * i.r * j.r * cos(i.theta - j.theta));
            if( temp < fit ) { fit = temp; } // If dist is lower, new minimum
		}
	}

    numFitnessCalcs++; // Count how many times we evaluate fitness
    return fit;
} // end calcFitness


// Evolves the chromosome using a local search for the specified number of iterations
// This will *hopfully* help "clean up" the points a bit
void Chromosome::localSearch( int iterations ) {

    for( int i = 0; i < iterations; i++ ) {
        vector<point> pts = mutate(SIGMA, SIGMA, points);
        double fit = calcFitness(pts);
        if( fit > fitness ) {
            points = pts;
            fitness = fit;
        }
    }
} // end localSearch


// Pretty Print - Print sorted by Theta
void Chromosome::print() const {
    vector<point> ps = points;
    sort( ps.begin(), ps.end(), [](point a, point b){ return a.theta < b.theta; } );

    for( point p : ps )
        cout << setw(fieldWidth) << left << p.theta << "\t" << p.r << endl;
} // end print


// Prints points in format specified by assignment, sorted by theta
void Chromosome::printResults() const {
    vector<point> ps = points;
    sort( ps.begin(), ps.end(), [](point a, point b){ return a.theta < b.theta; } );
    
    cout << "** " << cSize << endl;
    for( point p : ps )
        cout << "***\t"  << p.theta << "\t" << p.r << endl;
    cout << "***\tFit:\t" << fitness << endl;
} // end printResults
