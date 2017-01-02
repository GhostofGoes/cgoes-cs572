// Project:		Assignment 1 - Local Search
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Github:		https://github.com/GhostofGoes/cgoes-cs572
// License:		MITv2
// If you're in the class, don't copy the code
// You're welcome to use it to get un-stuck, or learn things like I/O, C++ syntax, libary functions, etc

#include <stdio.h>
#include <iostream>
#include <bitset>
#include "rand.h"
#include "bitHelpers.h"
#define TESTING 0

typedef unsigned long long int Bit64;
typedef unsigned int Bit32;
int encoding = -1, mutation = -1;

inline double fitness( double x, double y );  			// Single-peak fitness function that evaluates quality of x and y
inline Bit64 randomJump( Bit64 chromosome, int size );  // Mutation randomly jumps to somewhere in search space
inline Bit64 bitFlip( Bit64 chromosome );  				// Mutation randomly flips exactly one bit in the 20 bit chromosome
Bit64 sdIncDec( Bit64 chromosome ); 					// Mutation increments or decrements one of the fields of 10 bits fields for x or for y (4 possible changes/neighbors)

Bit32 extractX( Bit64 genome ); // Gets x chromosome from the genome
Bit32 extractY( Bit64 genome ); // Gets y chromosome from the genome
inline Bit64 randomGenotype();
double map(double value, double low1, double high1, double low2, double high2);
void printBinary( Bit64 value ); // Prints the binary representation of value


int main( int argc, char *argv[] ) {
	if(argc < 3) { // so we don't segfault on something silly like forgetting arguments
		printf("Not enough arguments: need encoding(0|1) and mutation(0|1|2).");
		return 1;
	}
	encoding = *argv[1] - '0';  // 0 = identity, 1 = Grey ( the -'0' is ASCII conversion)
	mutation = *argv[2] - '0';  // 0 = random jump, 1 = bit flip, 2 = int/dec
	initRand();  				// Initialize random number generator
	int runs = 1000; 			// Number of times to run the program
	if(TESTING) runs = 5;

	for( int i = 0; i < runs; i++ ) { // Used to average behavior of program across many runs
		Bit64 genotype = randomGenotype(); 	// Represents chromosome, 20 Least-signifigant Bits (LSB) of an UUL
		Bit32 x = 0, y = 0; 				// x = 10 Most-signifigant bits (MSB), y = 10 LSB of chromosome
		double xprime = 0, yprime = 0; 		// Used to represent decimal value of x/y for fitness function (x:[0, 10], y:[-10, 10])
		double fit_xprime = 0.0, fit_yprime = 0.0; // x/y prime values used for best fitness
		double currentFitness = 0.0; 		// Current fitness to compare against best
		double bestFitness = 0.0; 			// Best fitness found
		int numImproveMoves = 0; 			// Number of times fitness was improved
		int numFitEvalsBest = 0; 			// Number of fitness evaluations it took to get best fitness
		int evals = 10000; 					// Number of times to evaluate the fitness function
		if(TESTING) evals = 5;
		if(TESTING) printBinary(genotype);

		for( int fitEvals = 0; fitEvals < evals; fitEvals++ ) { // Fitness evaluation loop
			if(TESTING) {
				printf("Pre-mutation  Genotype: \t");
				printBinary(genotype);
				printf("Pre-mutation  X:\t %d\t\tY:\t %d\n", extractX(genotype), extractY(genotype));
			}
			
			// Mutate: 0 = random jump, 1 = bit flip, 2 = single-dimension inc/dec
			if( mutation == 0 ) {
				genotype = randomJump(genotype, 20);
			} else if( mutation == 1 ) {
				genotype = bitFlip(genotype);
			} else if( mutation == 2 ) {
				genotype = sdIncDec(genotype);
			}
			if(TESTING) {
				printf("Post-mutation Genotype: \t");
				printBinary(genotype);
			}

			// Genotype to phenotype mapping
			x = extractX(genotype);
			y = extractY(genotype);
			xprime = map(double(x), 0.0, 1023.0, 0.0, 10.0); 	// x range = [0, 10]
			yprime = map(double(y), 0.0, 1023.0, -10.0, 10.0); 	// y range = [-10, 10]
			if(TESTING) { printf("Post-mutation\tx:\t %d\ty:\t %d\n", x, y); }

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

		// Output results of the run
		printf("%d %d %f %f %f\n", numFitEvalsBest, numImproveMoves, fit_xprime, fit_yprime, bestFitness);
	} // end program loop
	return 0;
} // end main


// Calculates the fitness of decoded X and Y values of the chromosome
inline double fitness( double x, double y ) {
	return 1.0 / ( pow((x - 1.0), 2) + pow((y - 3.0), 2) + 1.0 );
}

// Randomly jumps to anywhere in the search space, which is defined by the size.
inline Bit64 randomJump( Bit64 chromosome, int size ) {
	return randMask((1ULL << size) - 1); // Mask is number of bits in chromosome 
}

// Randomly flips a bit in the chromosome
inline Bit64 bitFlip( Bit64 chromosome ) { // Assumes a 20 bit chromosome
	return chromosome ^ (1ULL << randMod(20)); // Flip a random bit in the chromosome
}

// Single-dimension Increment or Decrement
// Randomly increments or decrements X or Y of chromosome by 1.
// This results in a very small neighborhood. Alternate encodings will only improve range, not size, of this neighborhood.
Bit64 sdIncDec( Bit64 chromosome ) {
	Bit32 x = chromosome >> 10;
	Bit32 y = chromosome & ((1ULL << 10) - 1);
	Bit64 newChromosome = 0;
	int change = randMod(4); // 0 = x + inc, 1 = x + dec, 2 = y + inc, 3 = y + dec

	if( change == 0 ) { // Increment X (MSD of genotype)
		if( x == 1023 ) x = 0; // 1024 == 2^10 (or 2**10 in python its handy)
		else x += 1;
	} else if( change == 1 ) { // Decrement X (MSD of genotype)
		if( x == 0 ) x = 1023;
		else x -= 1;
	} else if( change == 2 ) { // Increment Y (LSD of genotype)
		if( y == 1023 ) y = 0; 
		else y += 1;
	} else if( change == 3 ) { // Decrement Y (LSD of genotype)
		if( y == 0 ) y = 1023;
		else y -= 1;
	}
	
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

// Gives a random 20-bit genotype
inline Bit64 randomGenotype() {
	return randULL() & 1048575; // 2^20 - 1
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

// Prints the binary representation of a ULL for testing purposes
void printBinary( Bit64 value ) {
	std::bitset<20> binaryValue ((unsigned long) value);
	std::cout << binaryValue.to_string() << std::endl;
}
