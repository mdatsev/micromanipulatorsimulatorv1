#pragma once
#include <random>
#define seed 24424236
static std::mt19937 gen(seed);
#define generation_size 1000
#define delta_time 0.001
//creature parameters
#define max_dimension 200
#define min_nodes 2
#define max_nodes 5 
#define min_size 5
#define max_size 25
#define min_friction 0
#define max_friction 1
#define min_restitution  1
#define max_restitution 1
#define min_mass 10
#define max_mass 100
#define min_muscles 1
#define max_muscles 5
#define min_stiffnes 200
#define max_stiffness 600
#define min_targetL 100
#define max_targetL 300