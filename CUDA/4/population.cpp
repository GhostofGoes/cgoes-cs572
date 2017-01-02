
#include "population.h"
#include <iostream>
#include <cstdio>
#include <algorithm>


Population::Population( const vector<p> &dataset, int popSize, double mutateProb, double xoverProb, double nodeProb,  int trnySize, int numElites ) {
    initRand(); // Initialize the random number generator
    data = dataset;
    popSize_ = popSize;
    mutateProb_ = mutateProb;
    xoverProb_ = xoverProb;
    nodeMutateProb_ = nodeProb;
    tSize_ = trnySize;
    elites_ = numElites;
    isSorted_ = false;
    nextChromosomeID = 0;
    oversizedTrees = 0;
    biggestOversize = 0;
    numSelections = 0;
    numMutations = 0;
    numXovers = 0;
    initPopulation();
}

void Population::initPopulation() {
    nextChromosomeID = 0;
    pop.reserve(popSize_);
    for( int i = 0; i < popSize_; i++ ) {
        Chromosome c(nextChromosomeID++);     // Initialize a new chromosome with random values and a fitness
        c.evalFitness(data);
        pop[i] = (c);   // Add the chromosome to the population
	}
}


int Population::evolve(int maxGenerations, double desiredError ) {
    const int maxTreeSize = 3500;
    int gensPerformed = 0;

    for( ; gensPerformed < maxGenerations; gensPerformed++ ) {
        vector<Chromosome> children(popSize_);

        for( int i = 0; i < popSize_; i++ ) {
            // TODO: use different types of xovers
            if( choose(xoverProb_) ) {         // Crossover
                //children[i]->crossover(select(pop)); 
                children[i] = crossover(pop[i], select());
                numSelections++;
                numXovers++;
            } else {
                children[i] = pop[i].copy();
            }

            if( choose(mutateProb_) ) {    // Mutation
                children[i].mutate();
                numMutations++;
            }
            else if( choose(mutateProb_) ) {
                children[i].nodeMutate();
                numMutations++;
            }
            
            // Check if tree is too big. If not, evaluate fitness.
            if( children[i].size() > maxTreeSize ) {
                oversizedTrees++;
                if( children[i].size() > biggestOversize ) biggestOversize = children[i].size();
                //if( children[i]->getUsed() ) 
                //    Tree::free(children[i]);
                children[i] = pop[i]; // Tree is too big, so overwrite with the old value
            } else {
                children[i].evalFitness(data); // Update fitnesses of the modified children
            }
        } // end children loop

        // Select from children and replace non-elites in population
        for( int i = elites_; i < popSize_; i++ ) {
            pop[i] = select(children);
            numSelections++;
        }
        
        // Memory management
        /*
        for( int i = 0; i < popSize; i++ ){
            if( children[i] == NULL || !children[i]->getUsed() ) continue;
            bool used = false;
            
            for( int j = 0; j < popSize; j++ )
                if( children[i] == pop[j] ) { used = true; break; }
            if( !used ) 
                Tree::free(children[i]);
        }*/

        // Sort population by fitness
        std::sort(pop.begin(), pop.end(), compChromosomeFitness); 

        // End early if error is "good enough"
        if( pop[0].error() < desiredError ) break;
    } // end generational loop

    return gensPerformed;
}


// Selects a chromosome out of population using simple tournament selection
Chromosome Population::select( const vector<Chromosome> &p ) const {
    std::vector<int> t((size_t) tSize_, (int) -1); // The indicies of the members of the tournament

    for( int i = 0; i < tSize_; i++ ) {
        int temp;
        do { temp = randMod(p.size()); } 
        while( isIn(t, temp) );
        t[i] = temp;
    }

    double bestFit = p[t[0]].fitness(); // Fitness of the "best" seen thus far
    int bestIndex = t[0]; // Index of the best individual seen thus far

    for( int i = 0; i < tSize_; i++ ) {
        if(p[t[i]].fitness() < bestFit) {
            bestFit = p[t[i]].fitness();
            bestIndex = i;
        }
    }

    return p[bestIndex]; 
} // end select

Chromosome Population::select() {
    return select(pop);
}

// Crosses over a random swath of the given tree with the current tree
// Similiar methodology as mutate()
// TODO: convert to Chromosome
Chromosome Population::crossover( const Chromosome &p1, const Chromosome &p2 ) const {
    Chromosome c = p1.copy();

    Tree * swath = p2.tree()->pickNode()->copy();   // Grab a random swath from the given tree
    Tree * chosen = c.tree()->pickNode();             // Choose a random subtree to replace with the xover'd swath
    Tree * chosenParent = chosen->up();     // Save it's parent
    Side chosenSide = chosen->remove();     // Save the side it's on, whilst trimming from tree
    free(chosen);                           // Release old subtree to the memory pool

    chosenParent->join(chosenSide, swath);  // Insert the swath into the tree

    if(CHECKING) c.check();                    // Verify integrity of the modified tree
    return c;
} // end crossover


// Variation of crossover that only crosses over subtrees AT the same depth (aka the depth the subtrees are located in matches)
// Additionally, it only chooses subtrees in range [depth/2 + 1, depth] to avoid massive damage
// TODO: convert to Chromosome
Chromosome Population::insertDepthCrossover( const Chromosome &p1, const Chromosome &p2 ) const {
    Chromosome c = p1.copy();

    int maxDepth = std::min(c.depth(), p2.depth());
    int minDepth = (int)(maxDepth / 2) - 1;
    int chosenDepth = randMod(minDepth) + minDepth;
    //printf("maxDepth: %d\t minDepth: %d\t chosenDepth: %d\n", maxDepth, minDepth, chosenDepth);

    Tree * swath = p2.tree()->pickNode(chosenDepth)->copy();
    Tree * chosen = c.tree()->pickNode(chosenDepth);
    Tree * chosenParent = chosen->up();
    Side chosenSide = chosen->remove();
    free(chosen);

    chosenParent->join(chosenSide, swath);

    if(CHECKING) c.check();
    return c;
} // end insertDepthCrossover


// TODO: UNFINISHED!
// Variation of crossover that only crosses over subtrees OF the same depth (e.g, the depths of the subtrees match)
// TODO: convert to Chromosome
Chromosome Population::sameDepthCrossover( const Chromosome &p1, const Chromosome &p2 ) const {
    Chromosome c = p1.copy();
    Tree * t = p2.tree();

    Tree * chosen = c.tree()->pickNode();             // Choose a random subtree to replace with the xover'd swath
    Tree * swath = t->pickNode();   // Grab a random swath from the given tree

    while( chosen->depth() != swath->depth() ) {
        swath = t->pickNode();
    }
    
    Tree * chosenParent = chosen->up();     // Save it's parent
    Side chosenSide = chosen->remove();     // Save the side it's on, whilst trimming from tree
    free(chosen);                           // Release old subtree to the memory pool

    chosenParent->join(chosenSide, swath);  // Insert the swath into the tree

    if(CHECKING) c.check();                    // Verify integrity of the modified tree
    return c;
} // end sameDepthCrossover


// Get best individual in population based on error (Not fitness!)
Chromosome Population::getBest() {
    if( !isSorted_ ) {
        std::sort(pop.begin(), pop.end(), compChromosomeError);
        isSorted_ = true;
    }
    return pop[0];
}

Stats Population::getStats() const {
    Stats s = {};
    for( Chromosome c : pop ) {
        Stats temp = c.getStats();
        s.numFitnessEvals += temp.numFitnessEvals;
        s.numNodeMutations += temp.numNodeMutations;
        s.numLeafMutations += temp.numNodeMutations;
    }
    return s;
}


void Population::printPop() const {
    for( int i = 0; i < popSize_; i++ ) {
        printf("\n[%d] ", i);
        pop[i].print();
        printf("Depth: %d\tSize: %d\n", pop[i].depth(), pop[i].size());
    }
} // end printPop

void Population::printPopFits() const {
    for( int i = 0; i < popSize_; i++ )
        printf("[%d]\t%f\n", i, pop[i].fitness());
} // end printPop

void Population::printPopTrees() const {
    for( Chromosome c : pop )
        c.printWithTree();
} // end printPopTrees

void Population::printPopStats() const {
    for( Chromosome c : pop ) {
        c.printStats();
    }
}

void Population::printTotalStats() const {
    Stats s = getStats();
    printf("\nnumFitnessEvals: %d\tnumXovers: %d\tnumSelections: %d\n", s.numFitnessEvals, numXovers, numSelections);
    printf("numMutations: %d\tnumNodeMutations: %d\tnumLeafMutations: %d\n", numMutations, s.numNodeMutations, s.numLeafMutations);
    printf("Oversized Trees: %d\tBiggest oversize:%d\n", oversizedTrees, biggestOversize);
}


bool Population::check() const {
    bool ret = true;

    for( Chromosome c : pop )
        if( !c.check() ) ret = false;

    if( popSize_ != pop.size() ) {
        std::cerr << "Mismatched population sizes. popSize: " << popSize_ << "\tpop.size(): " << pop.size() << std::endl;
        ret = false;
    }

    if( data.size() == 0 ) {
        std::cerr << "No data found!" << std::endl;
        ret = false;
    }

    return ret;
}

void Population::resetPop() {
    isSorted_ = false;
    initPopulation();
}


bool Population::operator < ( Population &p ) {
    return getBest() < p.getBest();
}
bool Population::operator <= ( Population &p ) {
    return getBest() < p.getBest();
}
bool Population::operator > ( Population &p ) {
    return getBest() > p.getBest();
}
bool Population::operator >= ( Population &p ) {
    return getBest() < p.getBest();
}
bool Population::operator == ( Population &p ) {
    return getBest() == p.getBest();
}
bool Population::operator != ( Population &p ) {
    return getBest() != p.getBest();
}