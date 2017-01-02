#ifndef POPULATION_H
#define POPULATION_H

#include "func.h"
#include "chromosome.h"
#include <vector>
using std::vector;

class Population {
    public:
        // popSize      Size of the population
        // mutateProb   Probability of a chromosome mutating
        // xoverProb    Probability of a crossover occuring
        // nodeProb     Probability of a individual node in a chromosome tree mutating
        // trnySize     Size of tournament used for tournament selection
        // elites       Number of elites to preserve between generations
        Population( const vector<p> &dataset, int popSize, double mutateProb, double xoverProb, double nodeProb, int trnySize, int numElites); // constructor
        Population( const vector<p> &dataset ) : Population(dataset, 1024, 0.7, 0.5, 0.5, 3, 20) {} // constructor with default pop size and evolutions (C++11 delegating constructors)
        ~Population() {} // TODO: valgrind and see if we're leaking memory

        // TODO: deal with pasing along nodeMutateProb (its a const in tree right now...)

        // Evolves the population. Returns number of generations performed.
        int evolve( int maxGenerations, double desiredError );
        int evolve( int maxGenerations )    { return evolve(maxGenerations, 0.0001); }
        int evolve()                        { return evolve(520); }
        
        Chromosome select ( const vector<Chromosome> &p ) const;
        Chromosome select(); // Selects a chromosome out of population

        // Crossover
        Chromosome crossover( const Chromosome &p1, const Chromosome &p2 ) const; // Combine two parents to create a child
        Chromosome insertDepthCrossover( const Chromosome &p1, const Chromosome &p2 ) const;  // BUGGY
        Chromosome sameDepthCrossover( const Chromosome &p1, const Chromosome &p2 ) const;    // UNFINISHED

        //void printPop( string title ) const;   // Prints the population, headed by title
        
        // Accessors
        vector<Chromosome> getPop() const { return pop; }
        int size()                  const { return popSize_; }
        Chromosome getBest();   // Returns the best chromosome in the population
        Stats getStats() const; // Total aggregated stats across all chromosomes

        // Printing output
        void printPop() const;          // Chromosome basics + Tree depths and sizes
        void printPopFits() const;      // Chromosome fitnesses
        void printPopTrees() const;     // Chromosome basics + trees
        void printPopStats() const;     // Stats for every chromosome in population
        void printTotalStats() const;   // Aggregate stats for the entire population

        // Utilites
        bool check() const; // Vetts the integrity of the population
        void resetPop();    // Re-initializes the entire population

        // Operator overloads
        bool operator <  ( Population &p );
        bool operator <= ( Population &p );
        bool operator >  ( Population &p );
        bool operator >= ( Population &p );
        bool operator == ( Population &p );
        bool operator != ( Population &p );

    private:
        vector<Chromosome> pop; // The population
        vector<p> data;        // Dataset describing the expression
        int popSize_;           // Total size of population (total # of members)
        
        double mutateProb_;     // Probability of Mutation
        double xoverProb_;      // Probability of crossover
        double nodeMutateProb_; // Probabily of mutating a specific node in a tree
        int tSize_;             // Tournament size
        int elites_;            // Number of elites (Individuals that are preserved between generations)(TODO: assert <= popsize)

        bool isSorted_;
        int nextChromosomeID;

        int oversizedTrees;
        int biggestOversize;
        int numSelections;
        int numMutations;
        int numXovers;
        // TODO: have a stats member that we initialize to null, so don't recalc every time?
        
        void initPopulation();  // Initializes the population with random values, and calculates their fitnesses
};


#endif