#include "evolve.h"

extern double eTable[26][26];		// English contact table
extern double cTable[26][26];		// Cipher contact table
extern vector < keyFitType > population; // The population of possible keys

// Uses index to select character from key for fitness evaluation
// NOTE: does not bounds check, if theres bug it'll probably happen here
inline int encode( int index, string key ) {
	return (int)(convert(key[index]));  // Converts char to int (ASCII 'a' - 97 = 0)
} // end encode


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


// Selects parents out of the population, culls the weak (bwuahahha)
// This is where we calculate the fitnesses
// NOTE: this is written with assumption of losing individual
int select( int &parentA, int &parentB ) {
    int loser = 0;
    // select based on selection type, e.g Tournament selection
    
    // Losing individual is overwritten by child...what a horrible fate
    return loser;
}

