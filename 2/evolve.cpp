#include "evolve.h"

extern double eTable[26][26];		// English contact table
extern double cTable[26][26];		// Cipher contact table
extern vector < keyFitType > population; // The population of possible keys

// Uses index to select character from key for fitness evaluation
// NOTE: does not bounds check, if theres bug it'll probably happen here
inline int encode( int index, char * key ) {
	return (int)(convert(key[index]));  // Converts char to int (ASCII 'a' - 97 = 0)
} // end encode


// Fitness function using Euclidean distance
// SMALLER IS BETTER FOR THIS FITNESS
double eFitness( char * key ) {
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
double bFitness( char * key ) {
	double fit = 0.0; // Fitness
	for( int i = 0; i < 26; i++ ) {
		for( int j = 0; j < 26; j++ ) {
			fit += sqrt(eTable[i][j] * cTable[encode(i, key)][encode(j, key)]);
		}
	}
	return fit;
} // end bFitness

// Returns child that is the crossover of both parents
// Length of the parents and the child are identical
string crossover( string parentA, string parentB ) {

	// Order One Crossover
	if(CROSSOVER == 0) {

	}
} // end crossover


// Mutates the chromosome in-place
void mutate( string &chromosome ) {

    // Mutate using permutation-based mutation operator

} // end mutate


// Selects an individual out of the population
string select() {
    string individual;

    // select based on selection type, e.g Tournament selection
    // remove selected individual from population

    // Return the individual's key, since we don't care about their fitness
    return individual;
}
