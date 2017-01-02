#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "func.h"
#include "tree.h"
#include <vector>

// The Chromosome, a tree of operators and operands representing a mathematical expression
class Chromosome {
    public:
        // startingDepthRange   Range of initial depths of the trees in population
        // minStartingDepth     Lowest value for the starting range
        // growthFactor         Factor by which crossed over trees grow
        // NOTE: fitness is NOT evaluated at construction time!
        Chromosome( int id, int startingDepthRange, int minStartingDepth, int growthFactor );
        Chromosome( int id ) : Chromosome(id, 15, 3, 2) {}; // Default constructor
        // TODO: copy constructor that takes a Tree argument
        Chromosome() {};
        ~Chromosome(); // Destructor

        // TODO: issues with copy constructor when passing chromosomes around?

        // Evolutionary
        void evalFitness( const vector<p> &data ); // Calculates fitness for the Chromosome and update's it's fitness value
        void mutate();  // Mutate the chromosome and updates it's fitness
        void nodeMutate(); // TODO: move this out of Tree
        void localSearch( int iterations, const vector<p> &data ); // Performs a local search on the chromosome's points for the specified number of iterations

        // Printing/Output
        void print() const;             // ID, Fitness, error
        void printWithTree() const;     // ID, Fitness, error, and the tree
        void printTree() const;         // Just the tree
        void printStats() const;        // Chromosome stats, such as numFitnessEvals

        // Accessors
        double fitness()    const { return fitness_; }
        double error()      const { return error_; }
        int ID()            const { return ID_; }
        Tree * tree()       const { return root_; }
        int depth()         const { return root_->depth(); }
        int size()          const { return root_->size(); }

        // Utility
        bool check() const;   // Vetts the integrity of the chromosome
        Stats getStats() const;
        Chromosome copy() const;

        // Operator overloads (comparison done using FITNESS)
        bool operator <  ( const Chromosome &p ) const;
        bool operator <= ( const Chromosome &p ) const;
        bool operator >  ( const Chromosome &p ) const;
        bool operator >= ( const Chromosome &p ) const;
        bool operator == ( const Chromosome &p ) const;
        bool operator != ( const Chromosome &p ) const;

        // Assignment operator
        //Chromosome & operator = ( const Chromosome & rhs) const;

    private:        
        double fitness_;    // Fitness of the chromosome (Smaller is better, used for things such as punishment)
        double error_;      // Error of the chromosome (Smaller is better, what we ultimatly want to minimize)

        Tree * root_;       // Root node of the tree storing the chromosome's expression
        int growthFactor_;  // Factor by which crossed over trees grow
        int ID_;            // Used to track unique chromosomes between generations

        // Counters of number of core operations performed
        // TODO: do stats as a list of named pairs (string label, value), then just format print the pairs
        int numFitnessEvals;
        int numNodeMutations;
        int numLeafMutations;
        double preLocalSearchError;
        int localSearchImprovements;
};

bool compChromosomeFitness( const Chromosome &a, const Chromosome &b );
bool compChromosomeError( const Chromosome &a, const Chromosome &b );

#endif