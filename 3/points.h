#ifndef POINTS_H
#define POINTS_H

#include <iostream>
#include <string>
#include <vector>

#include "rand.h"

using namespace std;

#define PI 3.14159265358979323846  /* "good enough" value of pi */
#define TESTING 0

const unsigned int fieldWidth = 10; // For spacing when printing stuff

typedef struct {
    double theta;   // Range: [0, 2PI]
    double r;       // Range: [0, 1]
} point; // Single point using polar notation on a unit circle. theta = angle, r = radius

enum OP { PLUS, COMMA };

#endif
