#include <random>

#pragma once
class Color3 {
public:
	float r, g, b;

	//============================================== Constuctors ====================================================================

	Color3();
	Color3(float red, float green, float blue);
	Color3(unsigned char red, unsigned char green, unsigned char blue);
	Color3(unsigned int red, unsigned int green, unsigned int blue);
	Color3(const Color3 &color):r(color.r),g(color.g),b(color.b){};

	//============================================== Setter/Getter ====================================================================
	
	unsigned char* getChar();
	float* getFloat();

};