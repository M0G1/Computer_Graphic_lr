#include "Color3.h"

//============================================== Constuctors ====================================================================
Color3::Color3() {
	this->r = float(std::rand() % 256) / 256;
	this->g = float(std::rand() % 256) / 256;
	this->b = float(std::rand() % 256) / 256;
}

Color3::Color3(unsigned char red, unsigned char green, unsigned char blue) {
	this->r = (float)red / 256;
	this->g = (float)green / 256;
	this->b = (float)blue / 256;
}

Color3::Color3(unsigned int red, unsigned int green, unsigned int blue) {
	this->r = (float)red / 256;
	this->g = (float)green / 256;
	this->b = (float)blue / 256;
}
//Color3::Color3() :r(0), g(0), b(0) {};
Color3::Color3(float red, float green, float blue) :r(red), g(green), b(blue) {};

//============================================== Setter/Getter ====================================================================

unsigned char* Color3::getChar() {
	unsigned char temp[3] = { (unsigned char)((r * 256)),(unsigned char)((g * 256)),(unsigned char)((b * 256)) };
	return temp;
}

float * Color3::getFloat() {
	float temp[3] = { r, g, b };
	return temp;
}
