#include "ObjParser.h"
#include "Image.h"
#include "coord.h"
#include <cmath>

#pragma once
class App {
public:
	ObjParser model; // сначала выполняем преобразования а потом берем индексы
	float t;		 // смещение в перспективном отображении // max val in obj is 0.028931. t = 1 - 0.39251  = 0,960749
	//булевы флаги
	bool is_use_fill_for_drawing; // antipod of wireframe drawing
	bool is_rand_color; // rand color for triangle
	bool is_light_dot; // set the color which is depended from scalar mul
	bool is_set_ones; // projection
	bool is_adv_light;
	//nc::NdArray<float> transform_to_Image;

	App(std::string file_path, double t = 0.96, bool is_use_fill_drawing = true, bool is_rand_color_ = false, bool is_use_ones = false, bool is_advan_light = true);
	//============================================== Methods =========================================================================

	void draw_triangles(Image & image, const Color3 & line_color, nc::NdArray<float> & transform_to_Image, nc::NdArray<float> & vertexes,
		nc::NdArray<float>& z_buff, nc::NdArray<float> & light_dir);

	nc::NdArray<float> project_on_plane(); //nc::NdArray<float> observer_dir,nc::NdArray<float> observer_pos)

	void draw_triangle_borderds(Image & image, const Color3 & line_color, std::vector<nc::NdArray<int>>& triangle, std::vector<nc::NdArray<float>>& triangle_f);

	void draw_triangle_by_filling(Image & image, const Color3 & line_color, std::vector<nc::NdArray<int>>& triangle,
		std::vector<nc::NdArray<float>>& triangle_f, std::vector<nc::NdArray<float>>& tri_f_trans, nc::NdArray<float>& z_buff, nc::NdArray<float>& light);

	nc::NdArray<float> project_transform(nc::NdArray<float> & transform_to_Image, float add_to_z);
	void task5();

	void task11();

	nc::NdArray<float> get_rot_mat(float a,float b,float g);
};