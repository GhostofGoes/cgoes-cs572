// Filename: 	decipher.cpp
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Description:	Assignment 2 - Genetic Algorithms - Breaking a simple Substitution Cipher
// Github:		https://github.com/GhostofGoes/cgoes-cs572
// License:		AGPLv3 until end of Fall 2016 semester. Then will convert to MITv2.
// if you're in the class, don't copy the code ( ͡° ͜ʖ ͡°)

#include <fstream>
#include "evolve.h"

double eTable[26][26];		// English contact table
double cTable[26][26];		// Cipher contact table

void initETable();
void initCTable( string ciphertext );
void initPopulation();
string initKey();
void printPopulation();
bool comp( keyFitType a, keyFitType b );

vector < keyFitType > population; // The population of possible keys

int main() {
	string ciphertext, temp, plaintext;
	int par1 = 0, par2 = 0;
	string key, child;

	initRand();  	// Initialize random number generator
	initETable();	// Initialize the English contact table
	while( cin >> temp ) { ciphertext += temp; } // Input the ciphertext 
	if(TESTING) { cout << "ciphertext: " << ciphertext << endl; }
	initCTable(ciphertext);
	initPopulation();
	if(TESTING) { printPopulation(); }
	
	for( int i = 0; i < RUNS; i++ ) {
		// Selects three individuals, returns 2 best by reference (ugh), throws away the poor soul that couldn't stand the heat
		select(par1, par2); 
		child = crossover( par1, par2 );
		mutate(child);
		addToPopulation(child);
	}
	
	key = bestIndividual();
	cout << "** goes " << key << endl;
	return 0;
} // end main


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
	for( unsigned int i = 0; i < ciphertext.length() - 1; i++ ) {
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


void initPopulation() {
	keyFitType member;
	for( int i = 0; i < POPSIZE; i++ ) {
		member.key = initKey();
		member.fit = 0;
		population.push_back(member);
	}
}

string initKey() {
	string key("abcdefghijklmnopqrstuvwxyz");
	for( int i = 0; i < 26; i++ ) {
		swap(key[i], key[randMod(26)]);
	}
	cout << key << endl;
	return key;
}

bool comp( keyFitType a, keyFitType b ) {
	return (a.fit < b.fit);
}

string bestIndividual() {
	sort(population.begin(), population.end(), comp);
	if(TESTING) { cout << "Best fitness:\t" << population[0].fit << endl; }
	return population[0].key;
}

// Converts an ASCII letter to an int to be used to index a table
int convert( char c ) {
	return (int)(c - 97);
}


// Reverts an int back to the ASCII letter it originally was
char revert( int i ) {
	return (char)(i + 97);
}

// Print 26 x 26 table
void printTable( double table[][26], string title = "Table" ) {
	cout << "\n** " << title << " **" << endl;
	for( int i = 0; i < 26; i++ ) {
		for( int j = 0; j < 26; j++ ) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
}


void printPopulation() {
	cout << "\n** Current Population **" << endl;
	for( unsigned int i = 0; i < population.size(); i++ ) {
		cout << "Key:\t" << population[i].key << "\tFitness:\t" << population[i].fit << endl;
	}
}
