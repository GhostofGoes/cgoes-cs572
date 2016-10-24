#include "points.h"

extern vector<member> pop;
extern unsigned int numPoints;


// Initializes the global population
void initPopulation() {
	for(int i = 0; i < POPSIZE; i++) {
        member m;
        m.points = genRandVec();
        m.fitness = fitness(m.points);
		pop.push_back(m);
	}
} // end initPopulation

// Generates a random vector of points, using global variable numPoints
vector<point> genRandVec() {
	vector<point> ps;

	for(int i = 0; i < numPoints; i++) {
        point p;
		p.theta = randUnit() * 2.0 * PI;
		p.r = randUnit();
        ps.push_back(p);
	}
    ps[0].theta = 0.0; // Lock first point to angle of 0 to reduce drift

    return ps;
} // end genRandVec

// Prints the global population, headed by title
void printPopulation( string title ) {
    cout << "\n++ Population: " << title << " ++" << endl;
    cout << setw(fieldWidth) << left << "Theta" << "\tRadius" << endl;
    for( member m : pop ) {
        cout << setw(fieldWidth) << left << "\nFitness: " << m.fitness << endl;
        printPoints(m.points);
    }
    cout << "++++++++++++++++++++++++++" << endl;;
} // end printPopulation

// Prints all the points in point vector ps
void printPoints( vector<point> ps ) {
    for( point p : ps) {
        cout << setw(fieldWidth) << left << p.theta << "\t" << p.r << endl;
    }
} // end printPoints
