#ifndef ATOM_H
#define ATOM_H
#include "vec3.h"
#include <string>

struct Atom {
    std::string type;
    Vec3 position;
    double charge;
    double epsilon;
    double sigma;
};

#endif