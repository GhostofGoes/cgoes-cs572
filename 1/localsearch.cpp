// Filename: 	localsearch.cpp
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Description:	Assignment 1 - Local Search
// Github:		https://github.com/GhostofGoes/cgoes-cs572

#include <iostream>
#include "rand.h"
#include "bitHelpers.h"
#define TESTING 1

using namespace std;
typedef unsigned long long int Bit64;
typedef unsigned int Bit32;
int encoding = -1, mutation = -1;

double fitness( double x, double y );  // Single-peak fitness function that evaluates quality of x and y
Bit64 randomJump( Bit64 chromosome, int size );  // Mutation randomly jumps to somewhere in search space
Bit64 bitFlip( Bit64 chromosome );  // Mutation randomly flips exactly one bit in the 20 bit chromosome
Bit64 sdIncDec( Bit64 chromosome ); // Mutation increments or decrements one of the fields of 10 bits fields for x or for y (4 possible changes/neighbors)
Bit32 extractX( Bit64 genome ); // Gets x chromosome from the genome
Bit32 extractY( Bit64 genome ); // Gets y chromosome from the genome
double convertX( Bit64 binaryX );
double convertY( Bit64 binaryY );
double map(double value, double low1, double high1, double low2, double high2);

int main( int argc, char *argv[] ) {
	if(argc < 3) { // so we don't segfault on something silly like forgetting arguments lol
		cout << "Not enough arguments: need encoding(0|1) and mutation(0|1|2)." << endl;
		return 1;
	}
	encoding = (int)*argv[1];  // 0 = identity, 1 = Grey
	mutation = (int)*argv[2];  // 0 = random jump, 1 = bit flip, 2 = int/dec
	initRand();  // Initialize random number generator
	
	if(TESTING) {
		cout << fitness(5, 1) << endl;
		Bit64 test = pow(2, 20) - 1; // 2^20
		//test = bitGray(test);
		Bit64 x = extractX(test);
		Bit64 y = extractY(test);
		cout << map(double(x), 0.0, 1023.0, 0.0, 10.0) << endl;
		cout << map(double(y), 0.0, 1023.0, -10.0, 10.0) << endl;
		cout << randomJump(test, 20) << endl;
		cout << bitFlip(test) << endl;
	}
	else {
		for( int i = 0; i < 1000; i++ ) { // Used to average behavior of program across many runs
			Bit64 genotype = randULL(); // Represents chromosome, 20 Least-signifigant Bits (LSB) of an UUL
			Bit32 x = 0; // Chromosome composed of the 10 Most-signifigant bits (MSB) of the Genotype
			Bit32 y = 0; // Chromosome compoased of 10 LSB of the Genotype
			Bit64 xprime = 0; // Used to represent decimal value of X for fitness function
			Bit64 yprime = 0; // See above
			double currentFitness = 0.0; // Current fitness to compare against best
			double bestFitness = 0.0; // Best fitness found
			int numImproveMoves = 0; // Number of times fitness was improved
			int numFitEvalsBest = 0; // Number of fitness evaluations it took to get best fitness
			double fit_xprime = 0.0;
			double fit_yprime = 0.0;

			
			for( int fitEvals = 0; fitEvals < 10000; fitEvals++ ) { // Fitness evaluation loop
				// Mutate: 0 = random jump, 1 = bit flip, 2 = int/dec
				if( mutation == 0 ) {
					x = randomJump(genotype, 10);
					y = randomJump(genotype, 10);
				} else if( mutation == 1 ) {
					x = bitFlip(genotype);
					y = bitFlip(genotype);
				} else if( mutation == 2 ) {
					x = sdIncDec(genotype);
					y = sdIncDec(genotype);
				}

				// Convert binary mutations to decimal for fitness evaluation
				xprime = map(double(x), 0.0, 1023.0, 0.0, 10.0); 	// x range = [0, 10]
				yprime = map(double(y), 0.0, 1023.0, -10.0, 10.0); 	// y range = [-10, 10]

				// Evaluate fitness
				currentFitness = fitness(xprime, yprime);

				// If the fitness we found is better, save it's genotype, fitness, and iterations taken
				if( currentFitness > bestFitness ) {
					bestFitness = currentFitness;
					numFitEvalsBest = fitEvals;
					fit_xprime = xprime;
					fit_yprime = yprime;
					numImproveMoves++;
				}
				
			} // end fitness eval loop
			cout << numFitEvalsBest << numImproveMoves << fit_xprime << fit_yprime << bestFitness << endl;
		} // end program loop
	}
	return 0;
} // end main

double fitness( double x, double y ) {
	return 1.0 / ( pow((x - 1.0), 2) + pow((y - 3.0), 2) + 1.0 );
}


Bit64 randomJump( Bit64 chromosome, int size ) {
	return randMask((1ULL << size) - 1); // Mask is number of bits in chromosome 
}

Bit64 bitFlip( Bit64 chromosome ) { // Assumes a 20 bit chromosome
	int randBit = randMod(20) + 1; // We want range to be [1, 20] not [0, 19], hence the +1
	return chromosome ^ (1ULL << randBit); // Flip a random bit in the chromosome
}

Bit64 sdIncDec( Bit64 chromosome ) {
	Bit32 x = chromosome >> 10;
	Bit32 y = chromosome & ((1ULL << 10) - 1);
	Bit64 newChromosome = 0;
	int change = randMod(4); // 0 = x + inc, 1 = x + dec, 2 = y + inc, 3 = y + dec

	if( change == 0 ) { // Increment X

	} else if( change == 1 ) { // Decrement X

	} else if( change == 2 ) { // Increment Y

	} else if( change == 3 ) { // Decrement Y

	} else 
		cerr << "Bad random value in sdIncDec" << endl;
	
	// Recombine modified X and Y
	newChromosome = x << 10;
	newChromosome |= y;
	return newChromosome;
}

Bit32 extractX( Bit64 genome ) {
	Bit32 x = genome >> 10; // Get the 10 Most signifigant bits in genome
	if( encoding == 1 ) // Grey code mapping
		x = bitDeGray(x);
	return x;
}

Bit32 extractY( Bit64 genome ) {
	Bit32 y = genome & ((1ULL << 10) - 1); // Get the 10 Least signifigant bits out of genome
	if( encoding == 1 ) // Grey code mapping
		y = bitDeGray(y);
	return y;
}

// map value from [low1, high2] -> [low2, high2]
// This basically maps from range of, say, [0,10] to [0,1023]
// Function Copyright Robert Heckendorn
double map(double value, double low1, double high1, double low2, double high2) {
    double denom, a, b;
	
    denom = high1 - low1;
    a = (high2 - low2)/denom;
    b = (high1 * low2 - high2 * low1)/denom;
    return a * value + b;
}
