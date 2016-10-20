#include "points.h"

extern vector< vector<point> > pop;
extern unsigned int numPoints;


// Returns the fitness found using the currently selected fitness function
double fitness() {
    return 0.0;
} // end fitness

// Initializes the population
void initPopulation() {
	for(int i = 0; i < POPSIZE; i++) {
		pop.push_back(genRandVec());
	}
} // end initPopulation

vector<point> genRandVec() {
	vector<point> ps;
	point p;

	for(int i = 0; i < numPoints; i++) {
		p.theta = randUnit() * 2.0 * PI;
		p.r = randUnit();
        ps.push_back(p);
	}

    return ps;
}

void printPopulation( string title ) {
    cout << "\n++ Population " << title << " ++" << endl;
    for(int i = 0; i < POPSIZE; i++) {
        printPoints(pop[i]);
    }
}

void printPoints( vector<point> ps ) {
    for(int i = 0; i < ps.size(); i++) {
        cout << ps[i].theta << "\t" << ps[i].r << endl;
    }
}
