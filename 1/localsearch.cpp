// Filename: 	localsearch.cpp
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Description:	Assignment 1 - Local Search
// Github:		https://github.com/GhostofGoes/cgoes-cs572

#include "localSearchLib.h"
int encoding, mutation;

inline double fitness( double x, double y );  // Single-peak fitness function that evaluates quality of x and y
inline Bit64 randomJump( Bit64 chromosome, int size );  // Mutation randomly jumps to somewhere in search space
inline Bit64 bitFlip( Bit64 chromosome );  // Mutation randomly flips exactly one bit in the 20 bit chromosome
Bit64 sdIncDec( Bit64 chromosome ); // Mutation increments or decrements one of the fields of 10 bits fields for x or for y (4 possible changes/neighbors)

Bit32 extractX( Bit64 genome ); // Gets x chromosome from the genome
Bit32 extractY( Bit64 genome ); // Gets y chromosome from the genome
inline Bit64 randomGenotype();


int main( int argc, char *argv[] ) {
	if(argc < 3) { // so we don't segfault on something silly like forgetting arguments lol
		cout << "Not enough arguments: need encoding(0|1) and mutation(0|1|2)." << endl;
		return 1;
	}
	encoding = (int)*argv[1];  // 0 = identity, 1 = Grey
	mutation = (int)*argv[2];  // 0 = random jump, 1 = bit flip, 2 = int/dec
	initRand();  // Initialize random number generator
	
	if(false) {
		Bit64 test = 1048575; // 2^20 - 1, which is first 20 bits set to 1
		//test = bitGray(test);
		Bit64 x = extractX(test);
		Bit64 y = extractY(test);
		cout << map(double(x), 0.0, 1023.0, 0.0, 10.0) << endl;
		cout << map(double(y), 0.0, 1023.0, -10.0, 10.0) << endl;
		printBinary(test);
		printBinary(x);
		printBinary(y);
		Bit64 randJump = randomJump(test, 20);
		Bit64 bflip = bitFlip(test);
		Bit64 sd = sdIncDec(test);
		printf("randJump(%llu): %llu\n", test, randJump);
		printBinary(randJump);
		printf("bitFlip(%llu): %llu\n", test, bflip);
		printBinary(bflip);
		printf("sdIncDec(%llu): %llu\n", test, sd);
		printBinary(sd);
	}
	else {
		int runs = 1000;
		if(TESTING) runs = 1;
		for( int i = 0; i < runs; i++ ) { // Used to average behavior of program across many runs
			Bit64 genotype = randomGenotype(); // Represents chromosome, 20 Least-signifigant Bits (LSB) of an UUL
			Bit32 x = 0, y = 0; // x = 10 Most-signifigant bits (MSB), y = 10 LSB of chromosome
			double xprime = 0, yprime = 0; // Used to represent decimal value of x/y for fitness function
			double fit_xprime = 0.0, fit_yprime = 0.0;
			double currentFitness = 0.0; // Current fitness to compare against best
			double bestFitness = 0.0; // Best fitness found
			int numImproveMoves = 0; // Number of times fitness was improved
			int numFitEvalsBest = 0; // Number of fitness evaluations it took to get best fitness
			
			if(TESTING) printBinary(genotype);
			int evals = 10000;
			if(TESTING) evals = 5;
			for( int fitEvals = 0; fitEvals < evals; fitEvals++ ) { // Fitness evaluation loop
				// Mutate: 0 = random jump, 1 = bit flip, 2 = int/dec
				if( mutation == 0 ) {
					genotype = randomJump(genotype, 20);
				} else if( mutation == 1 ) {
					genotype = bitFlip(genotype);
				} else if( mutation == 2 ) {
					genotype = sdIncDec(genotype);
				}

				// Genotype to phenotype mapping
				x = extractX(genotype);
				y = extractY(genotype);
				xprime = map(double(x), 0.0, 1023.0, 0.0, 10.0); 	// x range = [0, 10]
				yprime = map(double(y), 0.0, 1023.0, -10.0, 10.0); 	// y range = [-10, 10]
				printf("Pre-eval:\txprime: %f\typrime: %f\n", xprime, yprime);

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
	}
	return 0;
} // end main

inline double fitness( double x, double y ) {
	return 1.0 / ( pow((x - 1.0), 2) + pow((y - 3.0), 2) + 1.0 );
}

inline Bit64 randomJump( Bit64 chromosome, int size ) {
	return randMask((1ULL << size) - 1); // Mask is number of bits in chromosome 
}

inline Bit64 bitFlip( Bit64 chromosome ) { // Assumes a 20 bit chromosome
	return chromosome ^ (1ULL << (randMod(20) + 1)); // Flip a random bit in the chromosome
}

Bit64 sdIncDec( Bit64 chromosome ) {
	// TODO: issue with grey encoding here!
	Bit32 x = chromosome >> 10;
	Bit32 y = chromosome & ((1ULL << 10) - 1);
	Bit64 newChromosome = 0;
	int change = randMod(4); // 0 = x + inc, 1 = x + dec, 2 = y + inc, 3 = y + dec
	// printf("OLD\t chromo: %llu \t x: %d \t y: %d \n", chromosome, x, y);
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
	// printf("NEW\t chromo: %llu \t x: %d \t  y: %d \n", newChromosome, x, y);
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

inline Bit64 randomGenotype() {
	return randULL() & 1048575; // 2^20 - 1
}
