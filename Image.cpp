#include "Image.h"

//======================= see defintion in head file ============ Constuctors in head file ==================================================================
//============================================== Constuctors =====================================================================
Image::Image(unsigned int width, unsigned int height) :m_width(width), m_height(height), m_data(width * height) {
	m_data = std::vector<Color3>(width * height);
};

Image::Image(unsigned int width, unsigned int height, Color3 color) :m_width(width), m_height(height), m_data(width * height) {
	m_data = std::vector<Color3>(width * height);
	for (int i = 0; i < width * height; ++i) {
		m_data[i] = Color3(color);
	}

}
//============================================== Setter/Getter ====================================================================

void Image::set(int x, int y, const Color3& value) {
	/* // Проверка на выход за пределы
	if((x >= m_width) || ( y >= m_width))
		//doesn't work "Out of bound x(" + std::to_string(x) +") from width(" + std::to_string(width) +") y("+std::to_string(y)+ ") from height("+ std::to_string(height)+')';
		throw "Out of bound";
	catch(const char* msg){
		std::cerr << msg << std::endl;
	}	*/

	this->m_data[x + y * m_width] = Color3(value);
}

const Color3& Image::get(int x, int y) {
	return this->m_data[x + y * m_width];
}

unsigned int Image::width() { return this->m_width; }
unsigned int Image::height() { return this->m_height; }

//============================================== Methods =========================================================================

std::vector<unsigned char> Image::toVectorChar() {
	//create buffer
	std::vector<unsigned char> buff = std::vector<unsigned char>(this->m_height * m_width * 3, 0);
	// fill new vector with helping of Color3 method 
	for (int i = 0; i < this->m_data.size(); ++i) {
		buff[3 * i] = unsigned char(this->m_data[i].r * 255);
		buff[3 * i + 1] = unsigned char(this->m_data[i].g * 255);
		buff[3 * i + 2] = unsigned char(this->m_data[i].b * 255);
		//unsigned char* temp = this->m_data[i].getChar();
		/*for (short j = 0; j < 3; ++j) {
			buff[3 * i + j] = temp[j];
			std::cout << "char " << short(temp[j]) << " Color(rgb) " << m_data[i].r << " " << m_data[i].g << " " << m_data[i].b << "\n";
		}*/
	}

	return buff;
}

void Image::save(const std::string& filename) {
	std::vector<unsigned char> png;
	std::vector<unsigned char> image = this->toVectorChar();

	//encode
	unsigned error = lodepng::encode(png, image, this->m_width, this->m_height, LCT_RGB);
	//save to file successed encoded image
	if (!error) lodepng::save_file(png, filename);
	else std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

void Image::draw_line(int x1, int y1, int x2, int y2, Color3 color){
	
	bool step = false;
	if (abs(x2 - x1) < abs(y2 - y1)) {
		std::swap(x1, y1);
		std::swap(x2, y2);
		step = true;
	}
	if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	int dx = x2 - x1;
	int dy = y2 - y1;
	float d = abs(dy / (float)(dx));
	float error = 0;
	int y = y1;
	int add_val =(y2 > y1 ? 1 : -1);
	for (int x = x1; x <= x2; x++) {
		if (step)
			this->m_data[x + y * m_width] = Color3(color);
		else
			this->m_data[y + x * m_width] = Color3(color);
		error += d;
		if (error > 0.5) {
			y += add_val;
			error -= 1;
		}
	}
}
