#include "points.h"

extern vector<member> pop;
extern unsigned int numPoints;


// Returns the fitness found using the currently selected fitness function
double fitness() {
    return 0.0;
} // end fitness

// Initializes the population
void initPopulation() {
    member m;
	for(int i = 0; i < POPSIZE; i++) {
        m.fitness = -1;
        m.points = genRandVec();
		pop.push_back(m);
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
    cout << "\n++ Population: " << title << " ++" << endl;
    cout << setw(fieldWidth) << left << "Theta" << "\tRadius" << endl;
    for(int i = 0; i < POPSIZE; i++) {
        cout << setw(fieldWidth) << left << "\nFitness: " << pop[i].fitness << endl;
        printPoints(pop[i].points);
    }
    cout << "++++++++++++++++++++++++++" << endl;;
}

void printPoints( vector<point> ps ) {
    for(int i = 0; i < ps.size(); i++) {
        cout << setw(fieldWidth) << left << ps[i].theta << "\t" << ps[i].r << endl;
    }
}
