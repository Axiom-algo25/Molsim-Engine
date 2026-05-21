#include "forcefield.h"
#include <cmath>

const double COULOMB_CONSTANT = 332.0637;

double lennard_jones_potential(const Atom& a, const Atom& b) {
    double r = (a.position - b.position).length();
    if (r < 0.01) return 0.0;
    
    double sigma_ij = (a.sigma + b.sigma) * 0.5;
    double epsilon_ij = sqrt(a.epsilon * b.epsilon);
    
    double sr = sigma_ij / r;
    double sr6 = sr * sr * sr * sr * sr * sr;
    double sr12 = sr6 * sr6;
    
    return 4.0 * epsilon_ij * (sr12 - sr6);
}

double coulomb_potential(const Atom& a, const Atom& b) {
    double r = (a.position - b.position).length();
    if (r < 0.01) return 0.0;
    return COULOMB_CONSTANT * (a.charge * b.charge) / r;
}

double total_pair_energy(const Atom& a, const Atom& b) {
    return lennard_jones_potential(a, b) + coulomb_potential(a, b);
}