#ifndef ATOM_H
#define ATOM_H
#include "vec3.h"
#include <string>
#include <iostream>
#include <vector>





struct Atom {
    std::string type;
    Vec3 position;
    Vec3 acceleration;
    Vec3 velocity;
    double mass;
    double charge;
    double epsilon;
    double sigma;
};



void create_atom(
    std::vector<Atom>& atoms,
    std::string type,
    Vec3 pos,
    double mass,
    double epsilon,
    double sigma,
    double charge
);

struct Bond{
    int atom1;
    int atom2;
};

#endif

