cmake_minimum_required(VERSION 3.16)

project(MolSim)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    molsim
    main.cpp
    atom.cpp
    forcefield.cpp
    integrator.cpp
)

target_link_libraries(
    molsim
    raylib
    -lm
    -framework CoreVideo
    -framework IOKit
    -framework Cocoa
    -framework GLUT
    -framework OpenGL
)