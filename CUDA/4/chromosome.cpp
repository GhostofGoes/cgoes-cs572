
#include "chromosome.h"
#include <iostream>
#include <cstdio>


Chromosome::Chromosome( int id, int startingDepthRange, int minStartingDepth, int growthFactor ) {
    growthFactor_ = growthFactor;
    fitness_ = -666.0;
    error_ = -666.0;
    ID_ = id;

    numFitnessEvals = 0;
    numNodeMutations = 0;
    numLeafMutations = 0;
    preLocalSearchError = 0.0;
    localSearchImprovements = 0;

    // Initialize the Chromosome with a random tree
    root_ = Tree::getRandTree(randMod(startingDepthRange) + minStartingDepth);
    if(CHECKING) root_->check(); // Verify the tree we got is valid
}

Chromosome::~Chromosome() {
    Tree::free(root_);
}


// Error = sum from i to N of (f(x_i) - f*(x_i))^2
// TODO: keep a copy of data in the chromosome?
void Chromosome::evalFitness( const vector <p> &data ) {
    fitness_ = 0.0;

    for( const p &point : data ) {
        // TODO: make this non-global
        setX(point.x); // Sets global value used in eval()
        fitness_ += pow((point.fx - root_->eval()), 2); // ( f(x_i) - f*(x_i) )^2
    }

    error_ = fitness_;
    fitness_ += pow(2.0 * root_->size(), 2) / 4000; // Punish large trees. Assumes size is current, may need to update.

    numFitnessEvals++;
} // end evalFitness


// Generate a random tree, and attach it to a random part of the tree (destructive but exploratory)
// TODO: variety of mutation types (enum), randomly choose
void Chromosome::mutate() {
    // Could always save the tree for later (instead of free)
    //      - Perhaps a pool for "userful" trees
    //      - Pool would have a probability to be drawn from versus a random tree generated
    // Could modify a random node with a new random op or term
    // Could modify a constant node with a new random constant

    Tree * chosen = root_->pickNode();             // Choose a random subtree to mutate
    int chosenDepth = chosen->depth();      // Save it's depth
    Tree * chosenParent = chosen->up();     // Save it's parent
    Side chosenSide = chosen->remove();     // Save the side it's on, whilst trimming from tree
    free(chosen);                           // Release old subtree to the memory pool

    chosenDepth += randMod(growthFactor_);   // Grow tree by random amount
    chosen = Tree::getRandTree(chosenDepth);      // Generate a random tree
    chosenParent->join(chosenSide, chosen); // Attach to random part of the tree

    if(CHECKING) root_->check();             // Verify integrity of the complete mutated tree
} // end mutate


// TODO: leaf-based mutation
void Chromosome::nodeMutate() {
    root_->nodeMutate();
    numNodeMutations++;
} // end nodeMutate


// Basic local search. Another way would be to try different operators until stuff is better.
// TODO: convert to Chromosome
void Chromosome::localSearch( int iterations, const vector<p> &data ) {
    double bestError = error_;
    preLocalSearchError = error_;
    Tree * bestTree = root_;
    Chromosome newTree = copy();
    // TODO: copy constructor that takes a Tree argument

    for( int i = 0; i < iterations; i++ ) {
        newTree.nodeMutate();
        newTree.mutate();
        newTree.evalFitness(data);
        if( newTree.error() < bestError ) {
            if(localSearchImprovements > 0)
                Tree::free(bestTree);               // Free the previous best
            bestTree = newTree.tree()->copy();             // Replace with copy of the new best
            bestError = newTree.error();       // Save the error
            localSearchImprovements++;
        }
    }
    //Tree::free(newTree);
    root_ = bestTree;
} // end localSearch


void Chromosome::print() const {
    printf("Chromosome ID: %d\tFitness: %g\tError: %g\n", ID_, fitness_, error_);
}

void Chromosome::printWithTree() const {
    print();
    printf("Tree Depth: %d\tTree Size: %d\tGrowth Factor: %d\n", root_->depth(), root_->size(), growthFactor_);
    root_->print();
}

void Chromosome::printTree() const {
    root_->print();
}

void Chromosome::printStats() const {
    print();
    printf("numFitnessEvals: %d\tnumNodeMutations: %d\tnumLeafMutations: %d\n", numFitnessEvals, numNodeMutations, numLeafMutations);
    if(LOCALSEARCH) printf("preLocalSearchError: %g\tlocalSearchImprovements: %d\n", preLocalSearchError, localSearchImprovements);
}


bool Chromosome::check () const {
    bool ret = true;

    if( !root_->check() ) ret = false;

    if( fitness_ == 0.0 ) {
        std::cerr << "Fitness of Chromosome is uninitialized!" << std::endl;
        ret = false;
    }

    if( error_ == 0.0 ) {
        std::cerr << "Error of Chromosome is uninitialized!" << std::endl;
        ret = false;
    }

    return ret;
}

Stats Chromosome::getStats() const {
    Stats s;
    s.numFitnessEvals = numFitnessEvals;
    s.numNodeMutations = numNodeMutations;
    s.numLeafMutations = numLeafMutations;
    return s;
}

Chromosome Chromosome::copy() const {
    Chromosome c;
    c.fitness_ = fitness_;
    c.error_ = error_;
    c.root_ = root_->copy();
    c.growthFactor_ = growthFactor_;
    c.ID_ = ID_;
    c.numFitnessEvals = numFitnessEvals;
    c.numNodeMutations = numNodeMutations;
    c.numLeafMutations = numLeafMutations;
    c.preLocalSearchError = preLocalSearchError;
    c.localSearchImprovements = localSearchImprovements;
    return c;
}

bool Chromosome::operator < ( const Chromosome &p ) const {
    return fitness_ < p.fitness();
}
bool Chromosome::operator <= ( const Chromosome &p ) const {
    return fitness_ <= p.fitness();
}
bool Chromosome::operator > ( const Chromosome &p ) const {
    return fitness_ > p.fitness();
}
bool Chromosome::operator >= ( const Chromosome &p ) const {
    return fitness_ >= p.fitness();
}
bool Chromosome::operator == ( const Chromosome &p ) const {
    return fitness_ == p.fitness();
}
bool Chromosome::operator != ( const Chromosome &p ) const {
    return fitness_ != p.fitness();
}

/*
Chromosome & Chromosome::operator = ( const Chromosome &rhs ) const {
    if( this != &rhs ) // If not assigning to self
        this = rhs;
    return *this;
}*/

bool compChromosomeFitness( const Chromosome &a, const Chromosome &b ) {
    return a.fitness() < b.fitness(); 
}
bool compChromosomeError( const Chromosome &a, const Chromosome &b ) {
    return a.error() < b.error(); 
}