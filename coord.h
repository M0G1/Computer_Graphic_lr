
#pragma once
#include <vector>
#include <iostream>
#include "NumCpp.hpp"

bool get_baricentic_coord(int x, int y, std::vector<nc::NdArray<float>> & tr_f, float* lambda, bool is_check_equlation = false);

std::vector<std::vector<int>> get_borders_triangle(std::vector<nc::NdArray<int>> & tr_i);


