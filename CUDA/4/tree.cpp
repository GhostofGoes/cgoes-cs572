// Initial code courtesy of Robert Heckendorn
// It has been modified to suit my purposes for this course

#include "tree.h"

#define BADDOUBLE 666.66

// the list of possible operators
int numOpsTotal;   // total number of ops
int numOps0;       // number of nullary ops
int numOps1;       // number of unary ops
int numOps2;       // number of binary ops

// the list of possible operators of different numbers of arguments
Op **opList0;   // Nullary ops
Op **opList1;   // Unary ops
Op **opList2;   // Binary ops


// give a simple 4 character hex address of something to make it easier to 
// spot what address is what without full address being given.
unsigned long long int addrToNum(const void *addr) {
    return ((unsigned long long int)addr) & 0xffff;
}

Op::Op(char * name, int arity, double (*f)(double x, double y)) {
    name_ = name;
    arity_ = arity;
    f_ = f;
}

Op::Op(char * name, int arity, double (*u)(double x)) {
    name_ = name;
    arity_ = arity;
    u_ = u;
}

void initOps(int maxNumOps) {
    numOps0 = numOps1 = numOps2 = 0;
    numOpsTotal = numOps0 + numOps1 + numOps2;
    opList0 = new Op * [maxNumOps];
    opList1 = new Op * [maxNumOps];
    opList2 = new Op * [maxNumOps];
}

void addOpOrTerm(char * name, int arity, double (*f)(double x, double y)) {
    switch (arity) {
        case 0:
            opList0[numOps0++] = new Op(name, arity, f);
            break;
        case 1:
            opList1[numOps1++] = new Op(name, arity, f);
            break;
        case 2:
            opList2[numOps2++] = new Op(name, arity, f);
            break;
        default: 
            printf("ERROR(addOpOrTerm): Invalid arity\n");
    }
    numOpsTotal++;
}

// Gets a single node with a random operator of the specified arity chosen
Op * randOp( int arity ) {
    switch(arity) {
        case 0:
            return opList0[randMod(numOps0)];
        case 1:
            return opList1[randMod(numOps1)];
        case 2:
            return opList2[randMod(numOps2)];
    }
    return NULL;
}


// // // // // // // // // // // // // // // // // // // // // // // //
// Tree Memory Allocation
//
// A free list is maintained of nodes.  This was allocation can be tracked
// and it is often faster than running the new and delete all the time.
// Someone should check that it is faster in this case.  It also provides
// some small amount of error checking.
//
// (Chris's note) This is basically a Memory Pool, so time isn't wasted on re-allocating chunks using malloc or new

int Tree::freeListInitSize_ = 0;
int Tree::freeListSize_ = 0;
int Tree::freeListUsed_ = 0;
Tree *Tree::freeList_ = NULL;

void Tree::init() {
    left_ = NULL;
    right_ = NULL;
    up_ = NULL;
    used_ = false;
    value_ = 0.0;
    size_ = 1;
}


// this gets a single node 
Tree *Tree::get(Op *op, double initValue=0.0) {  // some ops assume an initial value!

    if (freeListInitSize_ == 0) {
        freeListInitSize_ = 2;
        freeList_ = new Tree(NULL);
        freeList_->used_ = false;
        freeListSize_ = 1;
        freeListUsed_ = 0;
    }

    // are their preallocated nodes available?
    if (freeList_ == NULL) {
        for (int i = 0; i < freeListInitSize_; i++) {
            Tree *tmp;

            tmp = freeList_;
            freeList_ = new Tree(NULL);
            freeList_->used_ = false;
            freeListSize_++;
            freeList_->left_ = tmp;
        }
        freeListInitSize_ = int(1.618 * freeListInitSize_); // Why 1.618?
    }

    if(freeList_ == NULL) { printf("ERROR(get): unable to allocate more nodes.\n"); return NULL; }

    // get node from free list
    Tree *result = freeList_;
    freeList_ = result->left_;

    // set up initial values for fetched tree node
    result->init();
    result->op_ = op;
    result->value_ = initValue;
    result->used_ = true;

    freeListSize_--;
    freeListUsed_++;

    return result;
}


// frees up a tree.  NOTE: it will set the tree pointer you give it to NULL!
void Tree::free(Tree *&freeMe) {
    if (freeMe) {
        if (!freeMe->used_) {
            printf("ERROR(free): trying to free tree: 0x%04llx that is already free.\n", addrToNum(freeMe));
            return;
        }
        freeMe->used_ = false;
        freeMe->value_ = 0.0;

        Tree * right = freeMe->right_;
        freeMe->right_ = NULL;

        Tree * left = freeMe->left_;
        freeMe->left_ = NULL;

        freeMe->left_ = freeList_;
        freeList_ = freeMe;
        freeMe = NULL;

        freeListUsed_--;
        freeListSize_++;

        free(left);
        free(right);
    }
}


// // // // // // // // // // // // // // // // // // // // // // // // 
// Tree Class
//
// Note: if a method has default parameters those parameters are
// not intended to be set by the user.  For example getRandTree should
// only be called with one parameter.  The others are for recursion.
//


// Gets a single node with a random operator chosen
Tree *Tree::getRandOp() {
    int index = randMod(numOps1 + numOps2);
    if (index < numOps1)
	    return get(opList1[index]);
    else
	    return get(opList2[index - numOps1]);
}


// Gets a single node with a random term
Tree *Tree::getRandTerm() {
    return get(opList0[randMod(numOps0)], randUnit() * 3.0);
}


// Gets a single node with random op or term
Tree *Tree::getRandOpOrTerm() {
    int index = randMod(numOpsTotal);
    if (index < numOps0)
	    return get(opList0[index], randUnit() * 3.0);
    else {
        index -= numOps0;
        if (index < numOps1)
            return get(opList1[index]);
        else
            return get(opList2[index - numOps1]);
    }
}


// Constructs a random tree that is no deeper than maxDepth
// It attaches to a parent tree at pointer: up.
Tree *Tree::getRandTree(int maxDepth, Tree *up, int depth) {
    Tree *t;

    if (depth==maxDepth) t = getRandTerm();     
    else if (depth==1) t = getRandOp();         // guarantee a tree at least 2 deep
    else t = getRandOpOrTerm();

    if (t->op_->arity_>=1) {
        t->left_ = getRandTree(maxDepth, t, depth + 1);
        t->size_ += t->left_->size_;
    }
    if (t->op_->arity_>=2) {
        t->right_ = getRandTree(maxDepth, t, depth + 1);
        t->size_ += t->right_->size_;
    }
    t->up_ = up;

    return t;
}


// Constructs a random tree that is no deeper than maxDepth
// It attaches to a parent tree at pointer: up.
Tree *Tree::getRandFullTree(int maxDepth, Tree *up, int depth) {
    Tree *t;

    if (depth==maxDepth) t = getRandTerm();     
    else t = getRandOp();

    if (t->op_->arity_>=1) {
        t->left_ = getRandFullTree(maxDepth, t, depth+1);
        t->size_ += t->left_->size_;
    }
    if (t->op_->arity_>=2) {
        t->right_ = getRandFullTree(maxDepth, t, depth+1);
        t->size_ += t->right_->size_;
    }
    t->up_ = up;

    return t;
}


// // // // // // // // // // // // // // // // // // // // // // // // 
// Tree Methods
//

// The tree constructor
Tree::Tree(Op *op) {
    left_ = NULL;
    right_ = NULL;
    up_ = NULL;
    op_ = op;
    if (op_) {
        if (op_->name_) value_ = BADDOUBLE;
        else value_ = op_->f_(0.0, 0.0); // must be terminal value
    }
    size_ = 1;
}


void Tree::printIndent(int indent) const {
    for (int i=0; i<indent; i++) printf("   ");
    printf("[%d, 0x%04llx]", size_, addrToNum(this));

    if (op_->name_) printf("%s\n", op_->name_);
    else printf("%lg\n", value_);  // terminal value

    if (left_) left_->printIndent(indent+1);
    if (right_) right_->printIndent(indent+1);
}


void Tree::printAux() const {
    if (op_->arity_==0) {
        if (op_->name_) printf("%s", op_->name_);     // if name_==nullptr then constant!
        else printf("%lg", value_);  // terminal value
    }
    else if (op_->arity_==1) {
        if (op_->name_) printf("%s", op_->name_);
        printf("(");
        if (left_) left_->printAux();
        printf(")");
    }
    else {
        printf("(");

        if (left_) left_->printAux();

        if (op_) printf(" %s ", op_->name_);
        else printf("NO OP POINTER\n");

        if (right_) right_->printAux();

        printf(")");
    }
}


void Tree::printAuxPre() const
{
    if (op_->arity_==0) {
        if (op_->name_) printf("%s", op_->name_);     // if name_==nullptr then constant!
        else printf("%lg", value_);  // terminal value
    }
    else {
        printf("(");
        if (op_->name_) printf("%s", op_->name_);
        if (left_) {
            printf(" ");
            left_->printAuxPre();
        }
        if (right_) {
            printf(" ");
            right_->printAuxPre();
        }
        printf(")");
    }
}


Tree *Tree::copy(Tree *up) {
    Tree *t = get(op_);

    t->up_ = up;
    t->value_ = value_;
    t->left_ = (left_ ? left_->copy(t) : NULL);
    t->right_ = (right_ ? right_->copy(t) : NULL);
    t->size_ = size_;

    return t;
}


int Tree::depth() const {
    int result = 1;
    if (left_!=NULL) result = left_->depth() + 1;
    if (right_!=NULL) {
        int tmp;
        if ((tmp = right_->depth()) + 1 > result) result = tmp + 1;
    }

    return result;
}


// Use setX defined in opList.h to set the value of X before calling this!
double Tree::eval() {
    // Checks if constant, if not then calls op with left and right if they are evaluatable, otherwise just 0
    if (op_->name_) value_ = (op_->f_)((left_ ? left_->eval() : 0), (right_ ? right_->eval() : 0));
    return value_;
}


// Use setX defined in opList.h to set the value of X before calling this!
// Evaluates entire tree, regardless of where this is called
// Basically, evaluates itself, then continues evaluating tree above it until reaches root
double Tree::evalUp() {
    Tree *node = this;
    while (1) {
        if (op_->name_) value_ = (op_->f_)((left_ ? left_->eval() : 0), (right_ ? right_->eval() : 0));
        if (node->up_ == NULL) return node->value_;
        node = node->up_;
    }
}


void Tree::print() const {
    printAux();
    printf("\n");
}


void Tree::printPre() const {
    printAuxPre();
    printf("\n");
}


// actually don't have to linearize and that would save time.
// do that some day.
int Tree::leftLinearize(Tree *appendix) {
    Tree *follow = this;
    Tree *bottomLeft = this;
    int size = 1;

    while (1) {
        // find bottom of the left tree
        while (bottomLeft->left_) {
            bottomLeft = bottomLeft->left_;
            size++;
	    }

        // find next right branch
        while (follow->left_ && (! follow->right_)) follow = follow->left_;

        // move to bottom left
        if (follow->right_) {
            bottomLeft->left_ = follow->right_;
            follow->right_ = NULL;
        }

        // if at the end of the tree add appendix tree if needed
        if (follow->left_==NULL) {
            follow->left_ = appendix;
            break;
        }
    } // why was there a semicolon here?

    return size;
}



bool Tree::join(Side s, Tree *node) {
    if (node) {
        if (((s==LEFT) && left_) || ((s==RIGHT) && right_)) {
            printf("ERROR(join): can't join on %s since there is a subtree there.\n", ((s==LEFT) ? "left" : "right"));
            return false;
        }
        else {
            // attach it
            if (s==LEFT) left_ = node;
            else right_ = node;

            // adjust the sizes
            node->up_ = this;
            int delta = node->size_; // Needed since node is being reassigned in while loop evaluation
            while (( node = node->up_ )) node->size_ += delta;
        }
    }

    return true;
}


bool Tree::check(bool hasParent) const {
    bool ok;
    
    if (this == NULL) {
	    printf("ERROR(check): node: 0x%04llx a NULL pointer and asked to check it as if it pointed to a tree!\n", addrToNum(this));
        ok = false;
    }
    else {
        ok = true;
        unsigned int loc = addrToNum(this);

        // Is size positive?
        if (size_<0) {
            printf("ERROR(check): node: 0x%04x has size: %d\n", loc, size_);
            ok = false;
        }

        // Is linkage consistant?
        if (up_) {
            if (!hasParent) {
                printf("ERROR(check): node: 0x%04x is not supposed to have a parent but does\n", loc);
                ok = false;
            }
            if ((up_->left_!=this) && (up_->right_!=this)) {
                printf("ERROR(check): parent does not have this node: 0x%04x as a child\n", loc);
                ok = false;
            }
        }
        else {
            if (hasParent) {
                printf("ERROR(check): node: 0x%04x is supposed to have a parent but doesn't\n", loc);
                ok = false;
            }
        }

        // Is sum of sizes consistant?
        int l = 0;
        int r = 0;
        if (left_) l = left_->size_;
        if (right_) r = right_->size_;
        if (l+r+1!=size_) {
            printf("ERROR(check): node: 0x%04x size on left: %d and size on right: %d does not give size of parent: %d\n", loc, l, r, size_);
            ok = false;
        }

        if (op_==NULL) {
            printf("ERROR(check): node: 0x%04x has an NULL operator pointer.\n", loc);
        }
        else {
            if (op_->arity_ == 0) {
                if (left_!=0) printf("ERROR(check): node: 0x%04x is a terminal but left side operand exists.\n", loc);
                if (right_!=0) printf("ERROR(check): node: 0x%04x is a terminal but right side operand exists.\n", loc);
            }
            else if (op_->arity_ == 1) {
                if (left_==0) printf("ERROR(check): node: 0x%04x operator is unary but there is no left side operand.\n", loc);
                if (right_!=0) printf("ERROR(check): node: 0x%04x operator is unary but right side operand exists.\n", loc);
            }
            else if (op_->arity_ == 2) {
                if (left_==0) printf("ERROR(check): node: 0x%04x operator is binary but there is no left side operand.\n", loc);
                if (right_==0) printf("ERROR(check): node: 0x%04x operator is binary but there is no right side operand.\n", loc);
            }
        }

        // Now check left and right
        if (left_) left_->check(true);
        if (right_) right_->check(true);
    }

    return ok;
}


Side Tree::remove() {
    Tree *node = this;

    int delta = size_;
    while (( node = node->up_ )) node->size_ -= delta;

    node = up_;
    up_ = NULL;

    if (node) {
        if (node->left_ == this) {
            node->left_ = NULL;
            return LEFT;
        }
        else if (node->right_ == this) {
            node->right_ = NULL;
            return RIGHT;
        }
        else printf("ERROR(remove): neither the left nor the right link of the parent of the removed node point to the node removed.\n");
    }

    return SIDEERROR;
}


// randomly and uniformly pick any node in the tree but the root
Tree * Tree::pickNode() {
    Tree *node = this;

    int loc = randMod(size_ - 1) + 1; // pick a node number
    if (loc>=size_) loc++;  // prevent choosing the root

    // find the node
    while (1) {
        if (node->size_ == loc) return node;

        int split;
        if (node->left_) split = node->left_->size_;
        else split = 0;

        if (loc<=split)
            node = node->left_;
        else {
            node = node->right_;
            loc -= split;
        }
    }
}

// TODO: this is probably broken
// TODO: print trees that it picks
Tree * Tree::pickNode( int loc ) {
    Tree *node = this;
    
    if (loc>=size_) loc++;  // prevent choosing the root

    // find the node
    while (1) {
        if (node->size_ == loc) return node;

        int split;
        if (node->left_) split = node->left_->size_;
        else split = 0;

        if (loc<=split)
            node = node->left_;
        else {
            node = node->right_;
            loc -= split;
        }
    }
}


void Tree::nodeMutate( Tree * node ) {
    const double nodeMutateProb = 0.5; // TODO: REMOVE THIS

    if(node == NULL) node = this;

    if(node->left_ != NULL) nodeMutate(node->left_);
    if(node->right_ != NULL) nodeMutate(node->right_);

    if(choose(nodeMutateProb)) {
        switch(node->op_->arity_) {
            case 0:
                node->op_ = opList0[randMod(numOps0)];
                node->value_ = randUnit()*3.0;
                break;
            case 1:
                node->op_ = opList1[randMod(numOps1)];
                break;
            case 2:
                node->op_ = opList2[randMod(numOps2)];
                break;
        } 
    }

}


// Suite of tests to make sure things are work as they should
void testTreeLibrary() {
    initRand();
    initOps(10);

    addOpOrTerm((char * )"+", 2, addOp);
    addOpOrTerm((char * )"-", 2, subOp);
    addOpOrTerm((char * )"*", 2, mulOp);
    addOpOrTerm((char * )"/", 2, divOp);
    addOpOrTerm((char * )"sin", 1, sinOp);
    addOpOrTerm((char * )"x", 0, xOp);
    addOpOrTerm((char * )NULL, 0, constOp);  // WARNING: null name means it is a constant!!!!

    // BEGIN TESTS


    // ALLOCATE A SINGLE NODE AND FREE IT
    Tree *s, *t, *u;

    printf("SIMPLE TREE\n");
    // one node
    t = Tree::getRandOp();
    Tree::printFreeSpace();
    t->printIndent();
    Tree::free(t);

    // build a simple tree by hand
    Tree::printFreeSpace();
    t = Tree::getRandOp();
    t->join(LEFT, Tree::getRandTerm());
    t->join(RIGHT, Tree::getRandTerm());
    Tree::printFreeSpace();
    t->printIndent();
    if(t->check()) printf("the tree is ok\n");
    else printf("the tree is NOT ok\n");
    Tree::free(t);  // t is now NULL
    Tree::printFreeSpace();

    // RANDOM TREE
    printf("\nRANDOM TREE\n");
    t = Tree::getRandTree(5);
    t->print();
    t->printPre();
    t->printIndent();
    Tree::printFreeSpace();
    setX(10);
    printf("eval: %lg\n", t->eval());
	
    // COPY
    printf("\nCOPY\n");
    s = t->copy();
    Tree::free(t);
    if (!t) printf("NULL\n");  // t should be set to NULL
    else t->print();
    printf("create random full tree\n");
    t = Tree::getRandFullTree(5);

    printf("copied tree\n");
    s->print();
    printf("eval: %lg\n", s->eval());

    printf("new tree\n");
    t->print();
    t->printPre();
    printf("eval: %lg\n", t->eval());

    // some tree data
    Tree::printFreeSpace();
    printf("new size: %d  old size %d\n", t->size(), s->size());
    printf("new depth: %d  old depth %d\n", t->depth(), s->depth());

    // release the tree space
    Tree::free(t);
    Tree::free(s);

    // PICKING NODES
    printf("\nPICK A NODE\n");
    t = Tree::getRandFullTree(4);
    t->printIndent();
    printf("root node: 0x%04llx   size: %d\n", addrToNum(t), t->size());
    for (int i=0; i<10; i++) {
	s = t->pickNode();
	printf("random node: 0x%04llx\n", addrToNum(s));
    }

    // release the tree space
    Tree::free(t);
    Tree::free(s);  // should generate an "already freed" error

    // REMOVE A RANDOM SUBTREE
    printf("\nREMOVE\n");
    Tree *parent;
    Side side;

    printf("target tree:\n");
    t = Tree::getRandTree(5);            // this is the tree we will mess with
    t->check();                    // tree ok?
    t->printIndent();              // what does it look like?
    s = t->pickNode();             // pick a subtree
    printf("remove this:\n");
    s->printIndent();              // what does the subtree look like?
    parent = s->up();              // get its parent
    side = s->remove();            // remove it from the tree (this probably
                                   // does not necessarily leave a legal 
                                   // expression to evaluate)
    printf("removal gives this tree:\n");
    t->printIndent();              // print the mutilated tree
    t->check();                    // this check SHOULD FIND PROBLEMS

    printf("\nremove tree s and then check it.\n");
    u = s;                         // remember location of tree you are about to delete
    Tree::free(s);                 // free up the part you cut out
    if(s->check()) printf("the tree is ok\n");  // check should fail since s==NULL
    else printf("the tree is NOT ok\n");
    printf("\ncheck the freed nodes of s as if they were a tree.  Should fail with lots of errors.\n");
    u->check();

    // attach a small tree to where you removed tree
    printf("\nATTACH\n");
    s = Tree::getRandTree(3);            // create a random subtree
    s->printIndent();             
    parent->join(side, s);         // attach it where the cut out part was

    printf("now you have:\n");
    t->printIndent();              // this should be able to be evaluated
    t->check();

    Tree::printFreeSpace();
} // end testTreeLibrary
