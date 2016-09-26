#include "evolve.h"

extern double eTable[26][26];		// English contact table
extern double cTable[26][26];		// Cipher contact table
extern vector < keyFitType > population; // The population of possible keys

// Uses index to select character from key for fitness evaluation
// NOTE: does not bounds check, if theres bug it'll probably happen here
inline int encode( int index, string key ) {
	return (int)(convert(key[index]));  // Converts char to int (ASCII 'a' - 97 = 0)
} // end encode

double fitness( string key ) {
    if(FITNESS_FUNC == 0)
        return eFitness(key);
    else
        return bFitness(key);
}

// Fitness function using Euclidean distance
// SMALLER IS BETTER FOR THIS FITNESS
double eFitness( string key ) {
	double fit = 0.0; // Fitness
	for( int i = 0; i < 26; i++ ) {
		for( int j = 0; j < 26; j++ ) {
			fit += pow(( eTable[i][j] - cTable[encode(i, key)][encode(j, key)] ), 2);
		}
	}
	return fit;
} // end eFitness


// Fitness function using Bhatthacaryya distance
// BIGGER IS BETTER FOR THIS FITNESS (oh yeah)
double bFitness( string key ) {
	double fit = 0.0; // Fitness
	for( int i = 0; i < 26; i++ ) {
		for( int j = 0; j < 26; j++ ) {
			fit += sqrt(eTable[i][j] * cTable[encode(i, key)][encode(j, key)]);
		}
	}
	return fit;
} // end bFitness


// Combines genomes of parents using crossover function of choice into child
void crossover( int parentA, int parentB, int child ) {
	// Order One Crossover
	if(CROSSOVER == 0) {

	}

} // end crossover


// Mutate chromosome in-place using permutation-based mutation operator
void mutate( int chromosome ) {
	if(MUTATION == 0) { // Simple swap mutation
		swap(population[chromosome].key[randMod(26)], population[chromosome].key[randMod(26)]);
	}
} // end mutate


// Using a tournament selection to select parents out of the population, culls the weak (bwuahahha)
// This is where we calculate the fitnesses
// NOTE: Assumes a tourney size of three. This may (and probably should) change
int select( int &parentA, int &parentB ) {
    int indicies[TSIZE];
    int range[POPSIZE];
    vector <indFitType> members;
    indFitType m;
    int temp = 0;

    // Randomly select a unique individual (spent more time on this than i should've...)
    for( int i = 0; i < POPSIZE; i++ ) range[i] = i;
    for( int i = 0; i < TSIZE; i++ ) {
        do { temp = randMod(POPSIZE); } while(range[temp] < 0);
        indicies[i] = range[temp];
        range[temp] = -1;
    }

    // Setup the tournament, determining fitness of each contestant
    for( int i = 0; i < TSIZE; i++ ) {
        m.index = indicies[i];
        m.fit = population[indicies[i]].fit;
        members.push_back(m);
    }

    // FIGHT! FIGHT FOR YOUR SURVIVAL!
    sort(members.begin(), members.end(), compSelect);

    // Winners circle
    parentA = members[0].index;
    parentB = members[1].index;

    // Losing individual will be overwritten by child...what a horrible fate
    return members[TSIZE - 1].index;
}

bool compSelect( indFitType a, indFitType b) {
    if(FITNESS_FUNC == 0)
        return (a.fit < b.fit);
    else
        return (a.fit > b.fit);
}
