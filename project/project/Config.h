#pragma once
#include <random>
#define seed 2
static std::mt19937 gen(seed);
#define gravity_constant 1000
#define air_friction 0.4
#define generation_size 1000
#define delta_time 0.001
#define one_generation_time 15
//generator parameters
#define max_dimension 200
#define min_nodes 3
#define max_nodes 6 
#define min_size 5
#define max_size 25
#define min_friction 0
#define max_friction 1
#define min_restitution  0
#define max_restitution 0
#define min_mass 1
#define max_mass 1
#define min_muscles 1
#define max_muscles 10
#define min_stiffness 200
#define max_stiffness 600
#define min_targetL 100
#define max_targetL 300
#define min_cycles 2
#define max_cycles 5
#define min_length_multiplier 0.1
#define max_length_multiplier 1
#define min_phase_time 0.5
#define max_phase_time 2.5
//mutation parameters
#define mutation_chance 0.01
#define large_mutation_chance 0.005
#define max_deviation 2

