// Filename: 	localSearchLIb.h
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Description:	Assignment 1 - Local Search
// Github:		https://github.com/GhostofGoes/cgoes-cs572

// NOTE: this library assumes you've called initRand() !!!

#ifndef LOCALSEARCHLIB_H
#define LOCALSEARCHLIB_H

#define TESTING 0
#include <string>
#include <bitset>
#include <iostream>
#include <stdio.h>
#include "rand.h"
#include "bitHelpers.h"

using namespace std;
typedef unsigned long long int Bit64;
typedef unsigned int Bit32;

inline double convertX( Bit64 binaryX );
inline double convertY( Bit64 binaryY );
double map(double value, double low1, double high1, double low2, double high2);
void printBinary( Bit64 value ); // Prints the binary representation of value

#endif
