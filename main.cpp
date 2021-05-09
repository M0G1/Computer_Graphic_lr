#include <iostream>
#include <random>
#include <cmath>

#include "lodepng.h"
#include "NumCpp.hpp" //depends from "boost" lib

#include "Image.h"
#include "line_drawing.h"
#include "ObjParser.h"
#include "App.h"


void encodeToFileWithType(std::string filename, std::vector<unsigned char>& image,
	unsigned width, unsigned height, LodePNGColorType type) {
	std::vector<unsigned char> png;
	//encode
	unsigned error = lodepng::encode(png, image, width, height, type);
	std::cout << "Size of image " << image.size() << " \nencoded size " << png.size() << std::endl;
	//save to file successed encoded image
	if (!error) lodepng::save_file(png, filename);
	else std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

void lab1Task1() {
	//// TASK 1.1 /1.2
	//// definition
	unsigned width = 200, height = 200;
	//std::vector<unsigned char> image;
	//unsigned BYTES_PER_COLORS = 1;
	//std::string filenameGray = std::string("testGray.png");

	//// resize in bytes for gray image
	//image.resize(width * height * BYTES_PER_COLORS);
	////fill the image
	//for (unsigned y = 0; y < height; ++y)
	//	for (unsigned x = 0; x < width; ++x) {
	//		image[BYTES_PER_COLORS * width * y + BYTES_PER_COLORS * x] = 255;
	//	}
	//encodeToFileWithType(filenameGray, image, width, height, LCT_GREY);

	//Task 1.3/1.4
	// definition
	std::vector<unsigned char> imageRGB;
	unsigned BYTES_PER_COLORS = 3;
	std::string filenameRGB = std::string("testRGB.png");
	const unsigned char colorRGB[3] = { 255, 0, 0 };

	// resize in bytes for gray image
	imageRGB.resize(width * height * BYTES_PER_COLORS);
	////fill the image
	for (unsigned y = 0; y < height; ++y)
		for (unsigned x = 0; x < width; ++x) {
			for (int i = 0; i < BYTES_PER_COLORS; ++i)
				//imageRGB[BYTES_PER_COLORS * width * y + BYTES_PER_COLORS * x + i] = colorRGB[i];	//Task 1.3
				imageRGB[BYTES_PER_COLORS * width * y + BYTES_PER_COLORS * x + i] = (x + y) % 256;
		}
	encodeToFileWithType(filenameRGB, imageRGB, width, height, LCT_RGB);

}

void lab1Task2Test() {
	unsigned width = 200, height = 200;
	Image png = Image(width, height);
	std::string filename = "classTest.png";

	for (unsigned y = 0; y < png.height(); ++y)
		for (unsigned x = 0; x < png.width(); ++x) {
			Color3 temp = Color3((unsigned char)(rand() % 256), rand() % 256, rand() % 256);
			png.set(x, y, temp);
		}
	png.save(filename);

}

void task3() {
	std::pair<int, int> b_point = std::make_pair(100, 100);
	Color3 white = Color3(unsigned char(255), 255, 255);
	Color3 black = Color3(unsigned char(0), 0, 0);
	std::vector<Image> images = { Image(200, 200, white),Image(200, 200, white),Image(200, 200, white),Image(200, 200, white) };
	// цикл по изображениям
	double alpha; // переменная для угла
	// цикл для отрисовки линий
	for (int i = 0; i <= 12; ++i) {
		alpha = 2 * std::_Pi * i / 13;
		// текующая точка
		std::pair<int, int> cur_p =
			std::make_pair(
				int(100 + 95 * std::cos(alpha)),
				int(100 + 95 * std::sin(alpha))
			);
		// рисуем линию во всех изображениях разными способами на разных изображениях
		line1(b_point.first, b_point.second, cur_p.first, cur_p.second, images[0], black);
		line2(b_point.first, b_point.second, cur_p.first, cur_p.second, images[1], black);
		line3(b_point.first, b_point.second, cur_p.first, cur_p.second, images[2], black);
		line(b_point.first, b_point.second, cur_p.first, cur_p.second, images[3], black);
	}
	for (int i = 0; i < 4; ++i)
		images[i].save("TASK3_line" + std::to_string(i) + ".png");

}

void num_cpp_test() {
	nc::NdArray<int> a0 = { {1, 2}, {3, 4} };
	auto af = nc::linspace<double>(0., nc::constants::pi);
	a0.print();

	std::cout << "af(";
	/*nc::Shape *sh = & af.shape;
	sh->print();*/
	std::cout << "): \n";
	af.print();
	af.reshape(25, 2);
	std::cout << std::endl;
	af.print();

	std::cout << std::endl;
	nc::NdArray<double> dd = nc::dot<double>(af, a0.astype<double>());
	dd.print();
	nc::NdArray<double> onesN = nc::ones<double>(25, 1);
	auto extended = nc::hstack({ dd,onesN });
	std::cout << "rows: " << onesN.shape().rows << std::endl;
	std::cout << "cols: " << onesN.shape().cols << std::endl;
	std::cout << std::endl;
	extended.print();
	std::cout << std::endl;
	std::vector<std::vector<double>> m = { {1,1,0},
	{0,1,0},
	{0,0,1} };

	nc::NdArray<double> mat1 = nc::asarray<double>(m);
	std::cout << "matrix\n";
	mat1.print();

	std::cout << "\nnc::dot<double>(extended, mat1).;" << std::endl;
	nc::dot<double>(mat1, nc::transpose(extended)).print();
	std::cout << "\nnc::dot<double>(extended, nc::transpose(mat1));" << std::endl;
	nc::dot<double>(extended, mat1).print();
	std::cout << "\nnc::dot<double>(extended, nc::transpose(mat1));" << std::endl;
	nc::dot<double>(extended, nc::transpose(mat1)).print();
	std::cout << "\nnc::dot<double>(mat1,nc::transpose(extended))" << std::endl;
	nc::dot<double>(mat1,nc::transpose(extended)).print();
	//nc::dot<double>(mat1,extended).print(); error))

	std::cout << std::endl<< std::endl;
	onesN(nc::Slice(0,3),nc::Slice()).print();
	std::cout << "end";
}

ObjParser get_obj_parser(bool is_test) {
	std::string file_path = "Test_lr1.obj";
	ObjParser obj = ObjParser(file_path, is_test);
	return obj;
}

int main() {
	std::string file_path = "Test_lr1.obj";
	/*lab1Task1();*/
	//lab1Task2Test();
	//task3();
	//num_cpp_test();
	//get_obj_parser(true);
	//App(file_path).task5();
	App(file_path).task11();
	//App(file_path).project_on_plane().shape().print();
	return 0;
}