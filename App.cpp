#include "App.h"


App::App(std::string file_path, double t_param,bool is_use_fill_drawing=true,bool is_rand_color_=false)
	:model(ObjParser(file_path, true)),t(t_param),is_use_fill_for_drawing(is_use_fill_drawing),is_rand_color(is_rand_color_) {

};
//============================================== Methods =========================================================================



void App::task5() {
	// перевести в координаты изображения 
	// взять целые
	// рисуем линии
	float size_xy[] = { 50,100,500,4000 };
	float shift = 500;
	std::cout << "In func" << std::endl;
	auto vertexes = this->model.vertexes; //this->project_on_plane();
	nc::NdArray<float> ligth_dir = { 0,0,1 };
	// set the flags
	this->is_use_fill_for_drawing = false;
	this->is_rand_color = false;

	for (int i = 3; i < 4; ++i) {
		nc::NdArray<float> mat = {
			{size_xy[i], 0 , shift},
			{0, size_xy[i], shift},
			{0, 0, 1}
		};
		//Изображение
		Color3 black = Color3(unsigned char(0), 0, 0);
		Color3 green = Color3(unsigned char(0), 255, 0);
		Image img = Image(1000, 1000, black);
		std::cout << "image " << i << std::endl;
		nc::NdArray<float> z_buff;// =  nc::NdArray<float>(img.width(), img.height()).fill(FLT_MAX);
		this->draw_triangles(img, green, mat, vertexes, z_buff, ligth_dir);

		img.save("TASK5_" + std::to_string(i) + ".png");
	};
}

void App::task11() {
	// перевести в координаты изображения 
	// взять целые
	// рисуем линии
	float size_xy[] = { 50,100,500,4000 };
	float shift = 500;
	std::cout << "In func" << std::endl;
	auto vertexes = this->model.vertexes; //this->project_on_plane();
	bool is_use_fill_for_drawing = true;
	bool is_rand_color = true;
	nc::NdArray<float> ligth_dir = { 0,0,1 };
	for (int i = 3; i < 4; ++i) {
		nc::NdArray<float> mat = {
			{size_xy[i], 0 , shift},
		{0, size_xy[i], shift},
		{0, 0, 1}
		};
		//Изображение
		Color3 black = Color3(unsigned char(0), 0, 0);
		Color3 rand_color = Color3();

		Image img = Image(1000, 1000, black);

		nc::NdArray<float> z_buff = nc::NdArray<float>(img.width(), img.height()).fill(FLT_MAX);
		std::cout << "image " << i << std::endl;;
		this->draw_triangles(img, rand_color, mat, vertexes, z_buff, ligth_dir);

		img.save("TASK11_" + std::to_string(i) + ".png");
	};
}

void App::draw_triangles(Image & image, const Color3 & line_color, nc::NdArray<float> & transform_to_Image, nc::NdArray<float> & vertexes,
	nc::NdArray<float>& z_buff, nc::NdArray<float> & light_dir) {
	// lazy))
	if (vertexes.shape().cols == 0 && vertexes.shape().cols == 0) {
		vertexes = this->model.vertexes;
	}
	if (transform_to_Image.shape().cols == 0 && transform_to_Image.shape().cols == 0) {
		transform_to_Image = {
			{4000, 0 , 500},
		{0, 4000, 500},
		{0, 0, 1} };
	}
	//NORMALIZE LIGHT DIR
	//std::cout << "light_dir shape: "; light_dir.shape().print(); std::cout <<std::endl;
	float norm_l_dir = nc::norm(light_dir)(0, 0);
	light_dir = nc::divide<float>(light_dir, norm_l_dir);
	//std::cout << "light_dir shape: "; light_dir.shape().print(); std::cout <<std::endl;

	transform_to_Image.print();
	// equal to mat * vertexes
	nc::NdArray<float> transformed = nc::dot(this->project_on_plane(), nc::transpose(transform_to_Image));
	transformed.shape().print();
	Color3 color;
	// цикл по индексам
	for (int j = 0; j < this->model.tri_ind[VERTEX].shape().cols; ++j) {
		//std::cout << "index " << j << std::endl;
		std::vector<nc::NdArray<float>> triangle_f, tri_f_translated;
		std::vector<nc::NdArray<int>> triangle;
		//цикл по вершинам
		for (int k = 0; k < 3; ++k) {
			//Ух, берем массив вершим и извлекаем точку по индексу
			int vert_ind = this->model.tri_ind[VERTEX](k, j);
			//std::cout << "\n" << vert_ind << ' '; // test
			nc::NdArray<float> temp = transformed(vert_ind, transformed.cSlice());
			tri_f_translated.push_back(temp);
			temp = vertexes(vert_ind, vertexes.cSlice());
			//temp.print(); // test
			triangle_f.push_back(temp);
			temp = transformed(vert_ind, transformed.cSlice());
			triangle.push_back(nc::around(temp).astype<int>());
		}

		//std::cout << "\n\n";
		nc::NdArray<float> a = triangle_f[1] - triangle_f[0],
		b = triangle_f[1] - triangle_f[2];
		nc::NdArray<float> normal = nc::cross(a, b);
		float norm_n = nc::norm(normal)(0, 0);
		normal = normal / norm_n;
		float scalar_mul = nc::dot(normal, light_dir)(0, 0);
		// draw visible triangle. All vector is normilazed
		if (this->is_rand_color) {
			color = Color3();
		}
		else {
			color = Color3(0, std::abs(scalar_mul), 0);
			color = line_color;
		}
		if (scalar_mul > 0) {
			if (this->is_use_fill_for_drawing) {
				this->draw_triangle_by_filling(image, color, triangle, triangle_f,tri_f_translated, z_buff);
			}
			else {
				this->draw_triangle_borderds(image, color, triangle, triangle_f);
			}
		}
		triangle.~vector();
		triangle_f.~vector();
	}
	std::cout << "all line drawed\n";
}

void App::draw_triangle_borderds(Image & image, const Color3 & line_color, std::vector<nc::NdArray<int>>& triangle, std::vector<nc::NdArray<float>>& triangle_f) {
	// рисуем линии
	// цикл по начальным точкам
	for (int k = 0; k < 2; ++k) {
		// цикл по концевым точкам
		for (int m = k + 1; m < 3; ++m) {
			int x1 = triangle[k](0, 0);
			int	x2 = triangle[m](0, 0);
			int	y1 = triangle[k](0, 1);
			int	y2 = triangle[m](0, 1);
			image.draw_line(x1, y1, x2, y2, line_color);
		}
	}
}

void App::draw_triangle_by_filling(Image & image, const Color3 & fill_color, std::vector<nc::NdArray<int>>& triangle,
	std::vector<nc::NdArray<float>>& triangle_f,std::vector<nc::NdArray<float>>& tri_f_trans, nc::NdArray<float>& z_buff) {
	/*
	{{x_min,x_max}
	{y_min,y_max}}
	*/

	std::vector<std::vector<int>> xy_min_max = get_borders_triangle(triangle);
	float *lambda = new float[3];
	// check
	if (xy_min_max[0][0] < 0)
		xy_min_max[0][0] = 0;
	if (xy_min_max[1][0] < 0)
		xy_min_max[1][0] = 0;
	if (xy_min_max[0][1] >= image.width())
		xy_min_max[0][1] = image.width() - 1;
	if (xy_min_max[1][1] >= image.height())
		xy_min_max[1][1] = image.height() - 1;
	int ind = 0;
	/*for (int i = 0; i < 3; ++i) {
		std::cout << "point of tri: "; triangle_f[i].print(); std::cout << std::endl;
	}*/
	//cycle x
	for (int x_int = xy_min_max[0][0]; x_int <= xy_min_max[0][1]; ++x_int) {
		//cycle y
		for (int y_int = xy_min_max[1][0]; y_int <= xy_min_max[1][1]; ++y_int) {
			bool is_inside_triangle = get_baricentic_coord(x_int, y_int, tri_f_trans, lambda, false);
			// is_inside_triangle = get_baricentic_coord(x_int, y_int, triangle_f, lambda, false);
			if (is_inside_triangle) {
				// work with z_buff
				float z = lambda[0] * triangle_f[0](0, 2) +
					lambda[1] * triangle_f[1](0, 2) +
					lambda[2] * triangle_f[2](0, 2);
				if (z < z_buff(x_int, y_int)) {
					z_buff(x_int, y_int) = z;
					image.set(x_int, y_int, fill_color);
					++ind;
				}
				/*if (ind < 3){
					std::cout <<"Sum of lambdas: "<< lambda[0]+lambda[1]+lambda[2] << std::endl;
				}*/
			}
		}
	}
	//std::cout << "painted " << ind << " pixels\n";
}


nc::NdArray<float> App::project_on_plane(bool is_set_ones) {
	nc::NdArray<float> *vert = &(this->model.vertexes);
	nc::NdArray<float> answer;
	nc::NdArray<float> temp = (*vert)(vert->rSlice(), nc::Slice(0, 2)); // vertex  : 15258 3
	nc::NdArray<float> staking;
	if(is_set_ones){
		staking = nc::ones<float>(temp.shape().rows, 1); // vector with ones
	}
	else{
		staking = nc::add<float>((*vert)(vert->rSlice(), nc::Slice(2, 3)), float(this->t));
	}
	answer = nc::hstack({ temp, staking });
	return answer;
}

nc::NdArray<float> App::project_transform( nc::NdArray<float> & transform_to_Image, float add_to_z){
	
}
