#ifndef POINTS_H
#define POINTS_H

#include <iostream>
#include <string>
#include <vector>

#include "rand.h"

using namespace std;

#define PI 3.14159265358979323846  /* "good enough" value of pi */
#define TESTING 0


typedef struct {
    double theta;   // Range: [0, 2PI]
    double r;       // Range: [0, 1]
} point; // Single point using polar notation on a unit circle. theta = angle, r = radius

typedef vector<point> chromosome;

typedef struct {
    double fitness;         // Fitness of the member
    chromosome c;   // Points for the member in polar coordinates
} member; // Member of population

#endif
