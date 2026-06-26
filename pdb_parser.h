#ifndef PDB_PARSER_H
#define PDB_PARSER_H

#include <vector>
#include <string>
#include "atom.h"

std::vector<Atom> load_pdb(const std::string& filename);

#endif