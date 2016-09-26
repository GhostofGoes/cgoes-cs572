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
#define TESTING 0

double eTable[26][26];		// English contact table
double cTable[26][26];		// Cipher contact table
vector < keyFitType > population; // The population of possible keys

void initETable();
void initCTable( string ciphertext );
void initPopulation();
string initKey();

string bestIndividual();
bool comp( keyFitType a, keyFitType b );

string decipher( string ciphertext, string key ); // Deciphers the encrypted ciphertext using the given key

int main() {
	string ciphertext, temp, plaintext, key;
	int par1 = 0, par2 = 0, child = 0;

	initRand();  	// Initialize random number generator
	initETable();	// Initialize the English contact table
	while( cin >> temp ) { ciphertext += temp; } // Input the ciphertext 
	if(TESTING) { cout << "ciphertext: " << ciphertext << endl; }
	initCTable(ciphertext);
	initPopulation();
	if(TESTING) { printPopulation("Post-init"); }
	

	// Steady State - WHERE THE MAGIC HAPPENS
	for( int i = 0; i < EVOLUTIONS; i++ ) {
		// Selects three individuals, returns two best by reference, throws away the poor soul that couldn't stand the heat
		child = select(par1, par2);
		crossover( par1, par2, child );
		mutate(child);  // TODO: could make this random, so it doesn't ALWAYS mutate
		population[child].fit = fitness(population[child].key); // "Add" child to population by modifying fitness
	}
	if(TESTING) { printPopulation("Post-evolution"); }
	

	key = bestIndividual();
	if(TESTING) { cout << "\n** Deciphered text **\n" << decipher(ciphertext, key) << endl; }
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

	// Normalize the frequencies
	for(int i = 0; i < 26; i++) {
		for(int j = 0; j< 26; j++) {
			if(eTable[i][j] != 0)
				eTable[i][j] /= sum;
		}
	}
	inf.close();
 } // end initETables


// Initializes the Ciphertext contact table by counting occurances of pairs of letters in the ciphertext
void initCTable( string ciphertext ) {
	for(int i = 0; i < 26; i++) {
		for(int j = 0; j < 26; j++) {
			cTable[i][j] = 0;
		}
	}

	// Count the number of times each pair of characters occurs in the ciphertext input
	for( unsigned int i = 0; i < ciphertext.length() - 1; i++ ) {
		cTable[convert(ciphertext[i])][convert(ciphertext[i + 1])] += 1;
	}

	// Normalize the frequencies
	for(int i = 0; i < 26; i++) {
		for(int j = 0; j< 26; j++) {
			if(cTable[i][j] != 0)
				cTable[i][j] /= (double)(ciphertext.length() - 1); 
		}
	}
} // end initCTable

// Initializes the population to random keys and zero fitness
void initPopulation() {
	keyFitType member;
	for( int i = 0; i < POPSIZE; i++ ) {
		member.key = initKey();
		member.fit = fitness(member.key);
		population.push_back(member);
	}
}

// Initializes key to random scrambling of the english alphabet
string initKey() {
	string key("abcdefghijklmnopqrstuvwxyz");
	for( int i = 0; i < 26; i++ ) {
		swap(key[i], key[randMod(26)]);
	}
	return key;
}

// Comparison function for sorting
bool comp( keyFitType a, keyFitType b ) {
	if(FITNESS_FUNC == 0)
		return (a.fit < b.fit);
	else
		return (a.fit > b.fit);
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

void printTable( double table[][26], string title = "Table" ) {
	cout << "\n** " << title << " **" << endl;
	for( int i = 0; i < 26; i++ ) {
		for( int j = 0; j < 26; j++ ) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
}

void printPopulation( string title ) {
	cout << "\n** Population " << title << " **" << endl;
	for( unsigned int i = 0; i < population.size(); i++ ) {
		cout << "Key:\t" << population[i].key << "\tFitness:\t" << population[i].fit << endl;
	}
}

string decipher( string ciphertext, string key ) {
	string deciphered;
	for( unsigned int i = 0; i < ciphertext.length(); i++ ) {
		deciphered.push_back( key[ convert( ciphertext[i] )]);
	}
	return deciphered;
}
