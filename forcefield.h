#ifndef FORCEFIELD_H
#define FORCEFIELD_H
#include "atom.h"

double lennard_jones_potential(const Atom& a, const Atom& b);
double coulomb_potential(const Atom& a, const Atom& b);
double total_pair_energy(const Atom& a, const Atom& b);

#endif