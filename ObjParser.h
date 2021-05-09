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
	std::vector<nc::NdArray<float>> norm_to_vert;

	ObjParser(std::string file_path); // is_test - false
	ObjParser(std::string file_path, bool is_test);

	void parse_file(bool is_test = true);

	/*
		ƒруга€ иде€
		»терироватьс€ по массивам вершин и хранить вектор нормалей, где нормаль сооответсвует точке из vertex  по индексу ()

		кажда€ нормаль это сумма нормалей к точке из obj файла
		¬ obj файле есть упоминание точки(вершина/текстура/нормаль). Ќаходитс€ все упоминани€ нормалей к фиксированной точке и соответствующие нормали складываютс€ и нормируютс€.
		
		{{normal1},{normal2},...,{normalN}},
	*/
	std::vector<nc::NdArray<float>> get_normal_to_vertexes();

	//void handle_copy_in_ndarray(std::vector<float>,nc::NdArray<float> in);
};

