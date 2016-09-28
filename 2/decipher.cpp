// Filename: 	decipher.cpp
// Author: 		Christopher Goes
// Course: 		CS 572 Evolutionary Computation
// Semester: 	Fall 2016
// Description:	Assignment 2 - Genetic Algorithms - Breaking a simple Substitution Cipher
// Github:		https://github.com/GhostofGoes/cgoes-cs572
// License:		AGPLv3 until end of Fall 2016 semester. Then will convert to MITv2.
// if you're in the class, don't copy the code

#include <fstream>
#include "evolve.h"
#define TESTING 0
#define PRINT_FITNESS 1

double eTable[26][26];		// English contact table
double cTable[26][26];		// Cipher contact table
vector < keyFitType > population; // The population of keys and their fitnesses
string english("abcdefghijklmnopqrstuvwxyz"); // A hack of epic proportions

void initETable();
void initCTable( string ciphertext );
void initPopulation();
string initKey();

string bestIndividual();
bool comp( keyFitType a, keyFitType b );

string decipher( string ciphertext, string key ); // Deciphers the encrypted ciphertext using the given key
char decode( string key, char c );


int main() {
	string ciphertext, temp, plaintext, key;
	int par1 = 0, par2 = 0, child = 0;

	initRand();  	// Initialize random number generator
	initETable();	// Initialize the English frequency table from "freq.txt"
	while( cin >> temp ) { ciphertext += temp; } // Input the ciphertext 
	if(TESTING) { cout << "\n ** Ciphertext **\n" << ciphertext << endl; }
	initCTable(ciphertext); // Initialize the Ciphertext frequency table from the ciphertext
	initPopulation(); // Initialize the population with random keys
	
	// Steady State - WHERE THE MAGIC HAPPENS
	for( int i = 0; i < EVOLUTIONS; i++ ) {
		// Selects three individuals, returns two best by reference, throws away the poor soul that couldn't stand the heat
		child = select(par1, par2);

		// Crossover genetic information based on probability
		if( choose(CROSSOVER_PROB) ) 
			pmx( par1, par2, child );
		// TODO: else { straight copy genetic information from both parents into child }

		// Mutate the child based on probability
		if( choose(MUTATION_PROB) ) 
			mutate(child);

		// "Add" child to population by modifying fitness
		population[child].fit = fitness(population[child].key); 
	}

	key = bestIndividual();
	cout << "** goes " << key << endl;
	if(TESTING) { cout << "\n** Deciphered text **" << endl; }
	cout << decipher(ciphertext, key) << endl;
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

// Comparison function for sorting that changes based on fitness function used
bool comp( keyFitType a, keyFitType b ) {
	if(FITNESS_FUNC == 0)
		return (a.fit < b.fit);
	else
		return (a.fit > b.fit);
}

// Sorts population to determine best individual, then returns that individual's key
string bestIndividual() {
	sort(population.begin(), population.end(), comp);
	if(PRINT_FITNESS) { cout << "Best fitness:\t" << population[0].fit << endl; }
	return population[0].key;
}

// Cleanly prints the given table prepended by the title
void printTable( double table[][26], string title ) {
	cout << "\n** " << title << " **" << endl;
	for( int i = 0; i < 26; i++ ) {
		for( int j = 0; j < 26; j++ ) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
}

// Cleanly prints the global population keys + fitnesses, prepended by the title
void printPopulation( string title ) {
	cout << "\n** Population " << title << " **" << endl;
	for( unsigned int i = 0; i < population.size(); i++ ) {
		cout << "Key:\t" << population[i].key << "\tFitness:\t" << population[i].fit << endl;
	}
}

// Deciphers the encrypted ciphertext into a plaintext string using the key
string decipher( string ciphertext, string key ) {
	string deciphered;
	for( unsigned int i = 0; i < ciphertext.length(); i++ )
		deciphered.push_back(decode(key, ciphertext[i]));
	return deciphered;
}

// Decrypts a given character using the given key. Uses the global english string.
char decode( string key, char c ) {
	// Find index of where c is in the key
	int index = 0;
	for( ; index < 26; index++ ) {
		if(key[index] == c)
			break;
	}
	// Return character from english key at same index
	return english[index];
}
