#ifndef INTEGRATOR_H
#define INTEGRATOR_H
#include "atom.h"
#include <vector>

Vec3 calculate_force(const Atom& a , const Atom& b);
void velocity_verlet_step(std::vector<Atom>&  atoms , double dt);

#endif