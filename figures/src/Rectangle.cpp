#include "Rectangle.hpp"
#include <iostream>
#include <string>

Rectangle::Rectangle(int id, int x, int y, int width, int height): Figure(id, x, y) {
	this->width = width;
	this->height = height;
}

void Rectangle::print() const {
	std::cout << "Rectangle " << id << ": x = " << x << " y = " << y 
		<< " width = " << width << " height = " << height << '\n';
}

bool Rectangle::is_inside(int x, int y) {
	return this->x - x <= width / 2 && this->y - y <= height / 2;
}

void Rectangle::zoom(int factor) {
	height *= factor;
	width *= factor;
}
