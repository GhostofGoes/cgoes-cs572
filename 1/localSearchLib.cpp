// Filename: 	localSearchLib.cpp
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Description:	Assignment 1 - Local Search
// Github:		https://github.com/GhostofGoes/cgoes-cs572

#include "localSearchLib.h"

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

void printBinary( Bit64 value ) {
	bitset<20> binaryValue ((unsigned long) value);
	cout << binaryValue.to_string() << endl;
}

inline Bit64 randomGenotype() {
	return randULL() ^ 1048575; // 2^20 - 1
}
