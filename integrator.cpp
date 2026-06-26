#include "integrator.h"
#include "forcefield.h"
#include <iostream>
#include <cmath>

const double  COLOUMB_CONSTANT = 332.0637;
const double BOX_SIZE = 20.0;

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

    std::cout
        << "r = " << r
        << " force = " << total_force_mag
        << std::endl;
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

        if(atoms[i].position.x > BOX_SIZE){
            atoms[i].position.x = BOX_SIZE;
            atoms[i].velocity.x *= -1;
        }

        if(atoms[i].position.x < -BOX_SIZE){
            atoms[i].position.x = -BOX_SIZE;
            atoms[i].velocity.x *= -1;
        }

        if(atoms[i].position.y > BOX_SIZE){
            atoms[i].position.y = BOX_SIZE;
            atoms[i].velocity.y *= -1;
        }

        if(atoms[i].position.y < -BOX_SIZE){
            atoms[i].position.y = -BOX_SIZE;
            atoms[i].velocity.y *= -1;
        }

        if(atoms[i].position.z > BOX_SIZE){
            atoms[i].position.z = BOX_SIZE;
            atoms[i].velocity.z *= -1;
        }

        if(atoms[i].position.z < -BOX_SIZE){
            atoms[i].position.z = -BOX_SIZE;
            atoms[i].velocity.z *= -1;
        }
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

/*  
    for (int i = 0; i < n; i++) {
        atoms[i].velocity.x *= 0.99;
        atoms[i].velocity.y *= 0.99;
        atoms[i].velocity.z *= 0.99;
    }
*/
}


double compute_temperature(const std::vector<Atom>& atoms) {
    double ke = 0.0;
    for(const auto& a : atoms){
        double v2 = a.velocity.x * a.velocity.x +
                    a.velocity.y * a.velocity.y + 
                    a.velocity.z * a.velocity.z;
        ke += 0.5 * a.mass * v2;
    }
    int dof = 3 * atoms.size() - 3;
    if(dof < 1) dof = 1;
    return (2.0 * ke) / (0.831446 * dof);
}

void apply_thermostat(std::vector<Atom>& atoms , double target_temp){
    double current = compute_temperature(atoms);
    if(current < 0.001) return ;
    double scale = sqrt(target_temp / current);
    for( auto& a : atoms){
        a.velocity.x *= scale;
        a.velocity.y *= scale;
        a.velocity.z *= scale;
    }
    /*
    std::cout
            << "Current T = " << current
            << " Target = " << target_temp
            << " Scale = " << scale
            << "temperature" << compute_temperature(atoms)
            << std::endl;
    std::cout
            << atoms[0].velocity.x << " "
            << atoms[0].velocity.y << " "
            << atoms[0].velocity.z
        << std::endl; 
    */           
}
    