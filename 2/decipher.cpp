// Filename: 	decipher.cpp
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Description:	Assignment 2 - Genetic Algorithms - Breaking a simple Substitution Cipher
// Github:		https://github.com/GhostofGoes/cgoes-cs572
// License:		AGPLv3 until end of Fall 2016 semester. Then will convert to MITv2.

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "rand.h"
#define TESTING 1
using namespace std;

double eTable[26][26];		// English contact table
double cTable[26][26];		// Cipher contact table

inline int encode( int index, char * key ); // index + key -> index
double eFitness( char * key );	// Euclidean distance
double bFitness( char * key );	// Bhatthacaryya distance

void initETable();
void initCTable( string ciphertext );
inline int convert( char c );
void printTable( double table[][26], string name );

int main() {
	string ciphertext, temp, plaintext;
	char key[26];

	initRand();  	// Initialize random number generator
	initETable();	// Initialize the English contact table
	while( cin >> temp ) { ciphertext += temp; } // Input the ciphertext 
	if(TESTING) { cout << "ciphertext: " << ciphertext << endl; }
	initCTable(ciphertext);
	// (c++ is so freaking annoying when it comes to string processing...)

	if(TESTING) {
		printTable(eTable, "eTable post-init");
		printTable(cTable, "cTable post-init");
	}

	cout << "** goes " << key << endl;
	return 0;
} // end main


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


// Initializes the English contact table from a file
void initETable() {
	char a = 0, b = 0;
	double num = 0, sum = 0;
	ifstream inf("freq.txt");

	// Initialize the table
	for(int i = 0; i < 26; i++) {
		for(int j = 0; j < 26; j++) {
			eTable[i][j] = 0;
		}
	}

	// Input the english language frequencies
	while(inf) {
		inf >> a >> b >> num;
		sum += num;
		eTable[convert(a)][convert(b)] = num;
	}
	//printTable(eTable, "eTable: post-load");

	// Normalize the frequencies
	for(int i = 0; i < 26; i++) {
		for(int j = 0; j< 26; j++) {
			if(eTable[i][j] != 0)
				eTable[i][j] /= sum;
		}
	}
	//printTable(eTable, "eTable: post-normalize");
	inf.close();
 } // end initETables

// Initializes the Ciphertext contact table by counting occurances of pairs of letters in the ciphertext
void initCTable( string ciphertext ) {
	// Initialize the table
	for(int i = 0; i < 26; i++) {
		for(int j = 0; j < 26; j++) {
			cTable[i][j] = 0;
		}
	}

	// Count the number of times each pair of characters occurs in the ciphertext input
	// length - 1 = total number of pairs in the ciphertext
	for( int i = 0; i < ciphertext.length() - 1; i++ ) {
		cTable[convert(ciphertext[i])][convert(ciphertext[i + 1])] += 1;
	}
	//printTable(cTable, "cTable: post-load");
	// Normalize the frequencies
	for(int i = 0; i < 26; i++) {
		for(int j = 0; j< 26; j++) {
			if(cTable[i][j] != 0)
				cTable[i][j] /= (double)(ciphertext.length() - 1); 
		}
	}
	//printTable(cTable, "cTable: post-normalize");
} // end initCTable


// Converts a character to an int to be used to index a table
inline int convert( char c ) {
	return (int)(c - 97);
}

// Print 26 x 26 table
void printTable( double table[][26], string title = "Table" ) {
	cout << "\n" << "** " << title << " **" << endl;
	for( int i = 0; i < 26; i++ ) {
		for( int j = 0; j < 26; j++ ) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
}
