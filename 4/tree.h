// Initial code courtesy of Robert Heckendorn
// It has been modified to suit my purposes for this course

#ifndef TREEH
#define TREEH

#include <cstdlib>
#include <cstdio>

#include "rand.h"
#include "opList.h"
#include "func.h"


enum Side {LEFT, RIGHT, SIDEERROR};

void initOps(int maxNumOps);
void addOpOrTerm(char * name, int arity, double (*f)(double x, double y));
void setX(double x); // set the x variable, used when evaluating tree



void testTreeLibrary(); // Suite of tests to make sure things are work as they should


// // // // // // // // // // // // // // // // // // // // // // // // 
// Op class
//
// Operators are Op objects that contain a function that can be evaluated
//
// This class can be either an operator or a terminal
//
class Op
{
public:
    Op(char * name, int arity, double (*f)(double x, double y));
    Op(char * name, int arity, double (*u)(double x));

    double (*f_)(double x, double y);   // Binary function if arity >= 2
    double (*u_)(double x);             // TODO: Unary function if arity == 1
    int arity_;                         // "arity"" of operator
    char * name_;                        // Printable name of operator (NULL if constant)
};

Op * randOp( int arity );

// // // // // // // // // // // // // // // // // // // // // // // // 
// Tree Class
//
// Note: if a method has default parameters those parameters are
// not intended to be set by the user.  For example getRandTree should
// only be called with one parameter.  The others are for recursion.
//
class Tree
{
// data
private:
    Tree *left_;   // the left child
    Tree *right_;  // the right child
    Tree *up_;     // the parent
    Op *op_;       // the operator for this node (could be a terminal)
    double value_; // the cached value for this node (value if terminal)
    int size_;     // size of the tree beneath this node including this node
    bool used_;    // is the node allocated (provides debugging support)
    double fitness_; // Fitness of the tree. Also referred to as "error" in some places in code
    double error_;
    // NOTE: smaller is better for fitness! (since it's the error)

// Memory management
private:
    static int freeListInitSize_;
    static int freeListSize_;
    static int freeListUsed_;
    static Tree *freeList_;

// methods
private:
    void printAux() const;              // print helper routine
    void printAuxPre() const;           // print helper routine
    int leftLinearize(Tree *appendix);  // used in free()


public:
    void init();
    static Tree *get(Op *op, double initValue); // get a node (initValue is optional)
    static Tree *getRandOp();              // get random operator node
    static Tree *getRandTerm();            // get random terminal node
    static Tree *getRandOpOrTerm();        // get random operator or terminal node
    static Tree *getRandTree(int maxDepth, Tree *up=NULL, int depth=1);  // get random tree
    static Tree *getRandFullTree(int maxDepth, Tree *up=NULL, int depth=1); // get random full tree
    static void free(Tree *&freeMe);       // free up a whole tree with freeMe as root


public:
    Tree(Op *op);       // create a tree

    bool check(bool hasParent=false) const;  // vet the tree
    int depth() const;      // Calculates current depth of the tree (TODO: cache this somehow)
    Tree * pickNode();      // Uniformly picks a random node that isn't the root
    Tree * pickNode( int d ); // Uniformly picks a random node at depth d (d must be greater than 0!)

    // setX(x) must be called before evaluating! (See opList.h)
    double eval();      // evaluate the tree (NOTE: modifies value_!)
    double evalUp();    // evaluate by going from this node up

    // Tree edits
    Tree * copy(Tree *up=NULL);  // the only command that copies any nodes
    bool join(Side s, Tree *subtree);  // add a subtree to a tree
    Side remove();              // Remove subtree from parent, returns side removed from in parent. 
    // NOTE: THIS WILL NOT FREE THE SUBTREE

    // Printing
    void printIndent(int depth=0) const;  // print internal form of tree
    void print() const;             // print in nice neat infix expression
    void printPre() const;          // print in nice neat prefix expression
    static void printFreeSpace() { printf("Free Space: unused: %d  used: %d\n", freeListSize_, freeListUsed_); }

    // Accessors
    bool isTerm() const { return left_ == NULL; }   // true if terminator
    bool isOp() const { return left_ != NULL; }     // true if operator
    Tree * up() const { return up_; }               // parent accessor
    int size() const { return size_; }              // size accessor
    double value() const { return value_; }         // value accessor
    double getFitness() const { return fitness_; }  // fitness accessor
    double getError() const { return error_; }      // error accessor


    // Evolutionary components 
    // These are defined in func.cpp (I'm lazy)
    void evalFitness( const std::vector<p> &data ); // Evaluates and updates fitness for the tree

    void mutate();
    void nodeMutate( Tree * node=NULL );
    void leafMutate( Tree * node=NULL );

    void crossover( Tree * t );
    void insertDepthCrossover( Tree * t );
    void sameDepthCrossover( Tree * t );


};


#endif
