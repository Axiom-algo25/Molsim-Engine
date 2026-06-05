#include "atom.h"
#include <vector>
void create_atom(
    std::vector<Atom>& atoms,
    std::string type,
    Vec3 pos,
    double mass,
    double epsilon,
    double sigma,
    double charge
)

{
    Atom a;

    a.type = type;
    a.position = pos;
    a.velocity = Vec3(0,0,0);
    a.acceleration = Vec3(0,0,0);

    a.mass = mass;
    a.charge = charge;
    a.epsilon = epsilon;
    a.sigma = sigma;

    atoms.push_back(a);
}