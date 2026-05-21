cmake_minimum_required(VERSION 3.16)
project(MolSim)
set(CMAKE_CXX_STANDARD 17)
add_executable(molsim src/main.cpp src/forcefield.cpp)
target_link_libraries(molsim raylib)Nillkin 3-in-1 Laptop Sleeve