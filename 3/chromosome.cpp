// Project: 	Assignment 3 - Evolution Strategies
// Author: 		Christopher Goes
// Description: Function definitions for the Chromosome class as defined in chromosome.h

#include <cmath>
#include <iomanip>
#include <algorithm>

#include "chromosome.h"
extern int numFitnessCalcs;
const double SIGMA = (double)(1.0 / 5.0);

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
}

// sigma    Mutation step size (usually 1/5)
// Possible modification: per-dimension sigmas
void Chromosome::mutate( double tSigma, double rSigma ) {
    for( point &p : points ) {
        if(choose(mutateProb)) { // Mutate only 1-2 of the points usually
            double temp = randNorm(tSigma) + p.theta;
            // Remove amount that pushed us past 2PI, so its (0 + whats left over)
            if( temp > 2.0*PI ) p.theta = temp - (2.0*PI); 
            else if( temp < 0.0 ) p.theta = temp + (2.0*PI);
            else p.theta = temp;

            if(p.theta < 0) {
                cout << "\ntheta: \t" << p.theta << endl;
                cout << "temp: \t" << temp << endl;
            }

            temp = randNorm(rSigma) + p.r;
            if(temp > 1.0) p.r = 1.0;
            else if(temp < -1.0) p.r = -1.0;
            else p.r = temp;

        }
    }
} // end mutate


vector<point> Chromosome::mutate( double tSigma, double rSigma, vector<point> ps ) const {
    vector<point> pts = ps;
    const double directionProb = 0.5;
    
    //if(choose(directionProb)) { // Positive direction
    if(true) {
        for( point &p : pts ) {
            if(choose(mutateProb)) { // Mutate only 1-2 of the points usually
                double temp = randNorm(tSigma) + p.theta;
                if( temp > 2.0*PI ) {
                    p.theta = temp - (2.0*PI); // Remove amount that pushed us past 2PI, so its (0 + whats left over)
                }
                else if( temp < 0.0 ) {
                    p.theta = temp + (2.0*PI);
                } else
                    p.theta = temp;
                    
                if(p.theta < 0) {
                    cout << "\ntheta: \t" << p.theta << endl;
                    cout << "temp: \t" << temp << endl;
                }

                temp = randNorm(rSigma) + p.r;
                if(temp > 1.0) p.r = 1.0;
                else if(temp < -1.0) p.r = -1.0;
                else p.r = temp;

            }
        }
    } else { // Negative direction
        for( point &p : pts ) {
            if(choose(mutateProb)) { // Mutate only 1-2 of the points usually
                double temp = randNorm(tSigma);
                if( p.theta - temp < 0.0 ) p.theta = (2.0*PI) - (temp - p.theta);
                else p.theta -= temp;

                temp = randNorm(rSigma);
                if(p.r - temp < -1.0) p.r = 1.0 - (temp + (-1.0 - p.r)); // ex: 1.0 - (0.2 + (-1.0 - -0.9)) = 1.0 - (0.2 + -0.1) = 1.0 - 0.1 = 0.9
                else p.r -= temp;
            }
        }
    }

    return pts;
}

// Fitness calculated by finding minimum Euclidean distance between all points in the chromosome
double Chromosome::calcFitness( vector<point> ps ) const {
    double fit = 2.0;  // Diameter of unit circle

    for( point i : ps ) {
		for( point j : ps ) {
            // From: https://en.wikipedia.org/wiki/Euclidean_distance#Two_dimensions
            // double temp = sqrt( pow(i.r, 2) + pow(j.r, 2) - 2 * i.r * j.r * cos(i.theta - j.theta));
			double temp = sqrt( i.r + j.r - 2 * i.r * j.r * cos(i.theta - j.theta));
            if( temp < fit ) { fit = temp; } // If dist is lower, new minimum
		}
	}

    numFitnessCalcs++;
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
