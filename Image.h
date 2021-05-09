#include <vector>
#include <string>
#include <iostream>

#include "lodepng.h"

#include "Color3.h"


#pragma once
class Image
{
private:
	unsigned int m_width;
	unsigned int m_height;
	std::vector<Color3> m_data;

public:
	//============================================== Constuctors =====================================================================
	//Create an image object with given width(x) and height(y);
	Image(unsigned int width, unsigned int height);
	//Create an image object with given width(x) and height(y) fill every in given color(Beter to use);
	Image(unsigned int width, unsigned int height, Color3 color);
	//============================================== Setter/Getter ===================================================================

	void set(int x, int y, const Color3& value);

	const Color3& get(int x, int y);

	unsigned int width();
	unsigned int height();

	//============================================== Methods =========================================================================
	
	std::vector<unsigned char> toVectorChar();

	void save(const std::string& filename);

	void draw_line(int x1, int y1, int x2, int y2, Color3 color);
};


