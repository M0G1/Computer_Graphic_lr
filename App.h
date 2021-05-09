#include "ObjParser.h"
#include "Image.h"
#include "coord.h"

#pragma once
class App {
public:
	ObjParser model; // сначала выполняем преобразования а потом берем индексы
	double t;		 // смещение в перспективном отображении
	//булевы флаги
	bool is_use_fill_for_drawing;
	bool is_rand_color;
	//nc::NdArray<float> transform_to_Image;

	App(std::string file_path, double t = 0.9,bool is_use_fill_drawing=true,bool is_rand_color_=false);
	//============================================== Methods =========================================================================

	void draw_triangles(Image & image, const Color3 & line_color, nc::NdArray<float> & transform_to_Image, nc::NdArray<float> & vertexes,
		nc::NdArray<float>& z_buff, nc::NdArray<float> & light_dir);

	nc::NdArray<float> project_on_plane(bool is_set_ones = true); //nc::NdArray<float> observer_dir,nc::NdArray<float> observer_pos)

	void draw_triangle_borderds(Image & image, const Color3 & line_color, std::vector<nc::NdArray<int>>& triangle, std::vector<nc::NdArray<float>>& triangle_f);

	void draw_triangle_by_filling(Image & image, const Color3 & line_color, std::vector<nc::NdArray<int>>& triangle,
		std::vector<nc::NdArray<float>>& triangle_f, std::vector<nc::NdArray<float>>& tri_f_trans, nc::NdArray<float>& z_buff);

	nc::NdArray<float> project_transform(nc::NdArray<float> & transform_to_Image, float add_to_z);
	void task5();

	void task11();
};