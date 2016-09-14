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
#include "rand.h"
#define TESTING 1
using namespace std;

double eTable[26][26];
double cTable[26][26];

void initTable();
string decode(string message, char * key);

int main() {
	string msg;
	char key[26];

	initRand();  // Initialize random number generator
	initTable();
	
	cout << "** goes " << key << endl;
	return 0;
} // end main


void initTable() {
	char a = 0, b = 0;
	double num = 0.0, sum = 0.0;
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
		//cout << "a: " << a - 97 << " |b: " << b - 97 << " |num: " << num << endl;
		eTable[a - 97][b - 97] = num;
	}
	//cout << sum << endl;

	// Normalize the frequencies
	for(int i = 0; i < 26; i++) {
		for(int j = 0; j< 26; j++) {
			//cout << eTable[i][j] << endl;;
			if(eTable[i][j] != 0)
				eTable[i][j] /= sum;
			//cout << eTable[i][j] << endl;;
		}
	}

	inf.close();
}

string decode( string message, char * key ) {
	string decoded;


	return decoded;
}