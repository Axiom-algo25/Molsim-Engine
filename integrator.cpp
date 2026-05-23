#include "integrator.h"
#include "forcefield.h"
#include <cmath>

const double  COLOUMB_CONSTANT = 332.0637;

Vec3 calculate_force(const Atom& a , const Atom& b ){
    Vec3 direction = (a.position - b.position);
    double r = direction.length();
    if (r < 0.01) return Vec3(0 , 0 , 0 ) ; 
    
    double sigma_ij = (a.sigma + b.sigma ) * 0.5;
    double epsilon_ij = sqrt( a.epsilon * b.epsilon);
    double sr = sigma_ij/r;
    double sr6 = sr * sr * sr * sr * sr * sr ;
    double sr12 = sr6  * sr6;
    double lj_force_mag = 24.0 * epsilon_ij * (2.0 * sr12 - sr6) / r;
    double coloumb_force_mag = COLOUMB_CONSTANT * (a.charge * b.charge) / (r * r);
    double total_force_mag = lj_force_mag + coloumb_force_mag;

    Vec3 force ;
    force.x = direction.x / r * total_force_mag;
    force.y = direction.y / r * total_force_mag;
    force.z = direction.z / r * total_force_mag;
    return force;
} 

void velocity_verlet_step(std::vector<Atom>& atoms , double dt){
    int n = atoms.size();

    for (int i = 0; i < n; i++) {
        atoms[i].velocity.x += 0.5 * atoms[i].acceleration.x * dt;
        atoms[i].velocity.y += 0.5 * atoms[i].acceleration.y * dt;
        atoms[i].velocity.z += 0.5 * atoms[i].acceleration.z * dt;
    }

    
    for (int i = 0; i < n; i++) {
        atoms[i].position.x += atoms[i].velocity.x * dt;
        atoms[i].position.y += atoms[i].velocity.y * dt;
        atoms[i].position.z += atoms[i].velocity.z * dt;
    }

    
    for (int i = 0; i < n; i++) {
        atoms[i].acceleration = Vec3(0.0, 0.0, 0.0);
    }

    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Vec3 force = calculate_force(atoms[i], atoms[j]);
            
            atoms[i].acceleration.x += force.x / atoms[i].mass;
            atoms[i].acceleration.y += force.y / atoms[i].mass;
            atoms[i].acceleration.z += force.z / atoms[i].mass;

            atoms[j].acceleration.x -= force.x / atoms[j].mass;
            atoms[j].acceleration.y -= force.y / atoms[j].mass;
            atoms[j].acceleration.z -= force.z / atoms[j].mass;
        }
    }


    for (int i = 0; i < n; i++) {
        atoms[i].velocity.x += 0.5 * atoms[i].acceleration.x * dt;
        atoms[i].velocity.y += 0.5 * atoms[i].acceleration.y * dt;
        atoms[i].velocity.z += 0.5 * atoms[i].acceleration.z * dt;
    }

    
    for (int i = 0; i < n; i++) {
        atoms[i].velocity.x *= 0.99;
        atoms[i].velocity.y *= 0.99;
        atoms[i].velocity.z *= 0.99;
    }
}