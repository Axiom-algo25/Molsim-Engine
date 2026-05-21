# MolSim Engine

> A molecular dynamics simulation engine built from first principles in C++ for modeling protein-ligand binding at varying temperatures.

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![Raylib](https://img.shields.io/badge/Raylib-5.0-red.svg)](https://www.raylib.com/)

---

## 🧬 What This Does

MolSim simulates how a drug molecule binds to a cancer protein at the atomic level—and what happens when the temperature changes. Built entirely from scratch: no external simulation libraries.

**Core Physics:**
- **Lennard-Jones potential** — van der Waals forces (personal space between atoms)
- **Coulomb potential** — electrostatic interactions (hydrogen bonds, salt bridges)
- **Velocity Verlet integration** — Newton's equations of motion
- **Thermostat** — temperature control (Berendsen/NVT ensemble)

**Visualization:**
- Real-time 3D rendering with Raylib
- Orbiting camera, zoom, grid, axes
- Live energy and distance display

---

## 🚀 Quick Start

### Prerequisites
- C++17 compiler (Clang/GCC)
- [Raylib](https://www.raylib.com/) (install via Homebrew: `brew install raylib`)
- CMake

### Build & Run
```bash
git clone https://github.com/Axiom-algo25/Molsim-Engine.git
cd molsim-engine
g++ -std=c++17 main.cpp forcefield.cpp integrator.cpp -o molsim -lraylib -lm
./molsim
