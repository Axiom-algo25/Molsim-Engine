#include "pdb_parser.h"
#include <fstream>
#include <iostream>

std::vector<Atom> load_pdb(const std::string& filename){
    
    std::vector<Atom> atoms;
    std::ifstream file(filename);

    if(!file.is_open()){
        std::cout << "Failed to open PDB file\n";
        return atoms;
    }

    std::cout << "PDB File opened successfully\n";

    std::string line;

    while(std::getline(file , line )){

        if (line.substr(0,4) != "ATOM" && line.substr(0,6) != "HETATM"){
            continue;
        }

        Atom a;

        double x = std::stod(line.substr(30,8));
        double y = std::stod(line.substr(38,8));
        double z = std::stod(line.substr(46,8));

        std::string atom_name = line.substr(12,4);
        std::string clean_name;
        for(char c : atom_name){
            if (c != ' ') clean_name += c ;
        }

        a.type = clean_name;
        a.position = Vec3(x , y , z );
        a.velocity = Vec3(0 , 0 , 0 );
        a.acceleration = Vec3(0 , 0, 0);

        char element = clean_name[0];
        
            if (element == 'C'){
                a.mass = 12.0;
                a.epsilon = 0.1904;
                a.sigma = 3.40;
                a.charge = 0.0;
            }else if ( element == 'N'){
                a.mass = 14.0;
                a.epsilon = 0.1700;
                a.sigma = 3.25;
                a.charge = 0.0;
            }else if ( element == 'O'){
                a.mass = 16.0;
                a.epsilon = 0.2092;
                a.sigma = 2.96;
                a.charge = 0.0;
            }else if ( element == 'S'){
                a.mass = 32.0;
                a.epsilon = 0.2500;
                a.sigma = 3.56;
                a.charge = 0.0;
            }else if ( element == 'H'){
                a.mass = 1.0;
                a.epsilon = 0.0157;
                a.sigma = 1.07;
                a.charge = 0.0;
            }else {
                a.mass = 12.0;
                a.epsilon = 0.1;
                a.sigma = 3.0;
                a.charge = 0.0;
            }
           
            atoms.push_back(a);
        }

    std::cout << "Loaded " << atoms.size() << " atoms from PDB\n";
    return atoms;
}
std::vector<Bond> detect_bonds(const std::vector<Atom>& atoms){
    std::vector<Bond> bonds;
    double cutoff = 1.6;

    for(int i = 0 ; i < atoms.size() ; i++){
        for(int j = i + 1 ; j < atoms.size() ; j++){
            double dist = (atoms[i].position - atoms[j].position).length();
            if(dist < cutoff){
                bonds.push_back({i , j});
            }
        }
    }
        std::cout << "Detected " << bonds.size() << " bonds\n";
        return bonds;
}
