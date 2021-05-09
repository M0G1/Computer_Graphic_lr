#include "line_drawing.h"


void line1(int x0, int y0, int x1, int y1, Image &image, Color3 color) {
	for (float t = 0.0; t < 1.0; t += 0.01) {
		int x = x0 * (1. - t) + x1 * t;
		int y = y0 * (1. - t) + y1 * t;
		image.set(x, y, color);
	}
}

void line2(int x0, int y0, int x1, int y1, Image &image, Color3 color) {
	for (int x = x0; x <= x1; x++) {
		float t = (x - x0) / (float)(x1 - x0);
		int y = y0 * (1. - t) + y1 * t;
		image.set(x, y, color);
	}
}

void line3(int x0, int y0, int x1, int y1, Image &image, Color3 color) {
	bool steep = false;
	/* Если смещение по оси X меньше смещения по оси Y, меняем местами координаты.*/
	if (std::abs(x0 - x1) < std::abs(y0 - y1)) {

		std::swap(x0, y0); std::swap(x1, y1); steep = true;
	}
	/* Если начало прямой находится правее конца, меняем начало и конец местами.*/
	if (x0 > x1) { // make it left-to-right
		std::swap(x0, x1); std::swap(y0, y1);
	}
	for (int x = x0; x <= x1; x++) {
		float t = (x - x0) / (float)(x1 - x0);
		int y = y0 * (1. - t) + y1 * t;
		if (steep) {
			image.set(y, x, color);
		}
		else {
			image.set(x, y, color);
		}
	}
}
void line(int x1, int y1, int x2, int y2, Image &image, Color3 color) {
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
			image.set(y, x, color);
		else
			image.set(x, y, color);
		error += d;
		if (error > 0.5) {
			y += add_val;
			error -= 1;
		}
	}
}
