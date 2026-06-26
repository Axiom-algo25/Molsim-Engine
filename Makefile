all:
	g++ -std=c++17 main.cpp atom.cpp forcefield.cpp integrator.cpp pdb_parser.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -lm -o molsim