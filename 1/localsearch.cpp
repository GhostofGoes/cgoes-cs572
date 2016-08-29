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

// Mutation Operators
Bit64 randomJump( Bit64 chromosome, int size );
Bit64 bitFlip( Bit64 chromosome );  	// Randomly flips exactly one bit in the 20 bit chromosome
Bit64 sdIncDec( Bit64 chromosome );  	// Increments or decrements one of the fields of 10 bits fields for x or for y


int main( int argc, char *argv[] ) {
	encoding = (int)*argv[1];  // 0 = identity, 1 = Grey
	mutation = (int)*argv[2];  // 0 = random jump, 1 = bit flip, 2 = int/dec
	initRand();  // Initialize random number generator
	
	if(TESTING)
		cout << fitness(5, 1) << endl;
	
	for( int i = 0; i < 1000; i++ ) {  // Program behavior averaging loop
		Bit64 genotype = randULL();  // Represents chromosome, 20 Least-signifigant Bits (LSB) of UUL
		Bit32 x = 0;
		Bit32 y = 0;
		double xprime = 0.0;
		double yprime = 0.0;
		int numFitEvals = 0;
		int numImproveMoves = 0;
		double fit_xprime = 0.0;
		double fit_yprime = 0.0;
		double bestFitness = 0.0;
		
		for( int i = 0; i < 10000; i++ ) { // Fitness evaluation loop
			// mutate
			// evaluate fitness
		}
		cout << numFitEvals << numImproveMoves << fit_xprime << fit_yprime << bestFitness << endl;
	
	}
	return 0;
}

double fitness( double x, double y ) {
	if( x > 10 || x < 0 || y < -10 || y > 10) {
		cout << "ERROR: Value is out of bounds in fitness function!  x: " << x << "  y: " << y << endl;
		return -99;
	}
	else {
		return 1.0 / ( pow((x - 1.0), 2) + pow((y - 3.0), 2) + 1.0 );
	}
}


Bit64 randomJump( Bit64 lastChromosome ) {
	Bit64 randomBitString;
	
	return randomBitString;
}

Bit64 bitFlip( Bit64 chromosome ) {
	
}

Bit64 sdIncDec( Bit64 chromosome ) {
	
}

