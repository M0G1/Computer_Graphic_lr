#include "NumCpp.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

//marcoses
constexpr auto VERTEX = 0;  // index of VERTEX  index array in tri_ind vector;
constexpr auto TEXTURE = 1; // index of TEXTURE index array in tri_ind vector
constexpr auto NORMAL = 2;  // index of NORMAL  index array in tri_ind vector


#pragma once
class ObjParser {
public:
	nc::NdArray<float> vertexes; // {{x,y,z},..., {x,y,z}}
	nc::NdArray<float> normals;  // {{x,y,z},..., {x,y,z}}
	nc::NdArray<float> textures; // {{x,y},..., {x,y}}
	/* arrays of index of vertex/ index of texture / index of normals {{vertex},{texture},{normal}}
	 {fvertex{{0_x,...,i_x,},{0_y,...,i_y,},{0_z,...,i_z,}}, ftexture{{0_x,...,i_x,},{0_y,...,i_y,}},fnormals{{0_x,...,i_x,},{0_y,...,i_y,},{0_z,...,i_z,}}} */
	std::vector<nc::NdArray<int>> tri_ind{ nc::NdArray<int>(), nc::NdArray<int>(),nc::NdArray<int>() };
	std::string file_p; // path to file 

	ObjParser(std::string file_path); // is_test - false
	ObjParser(std::string file_path, bool is_test);

	void parse_file(bool is_test = true);

	//void handle_copy_in_ndarray(std::vector<float>,nc::NdArray<float> in);
};

