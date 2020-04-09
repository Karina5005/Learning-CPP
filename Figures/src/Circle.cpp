#include "Circle.hpp"
#include <iostream>
#include <string>
#include <string.h>

Circle::Circle(int id, int x, int y, int radius, const char* label): Figure(id, x, y) {
	this->label = new char[(strlen(label) + 1)];
	strcpy(this->label, label);
	this->radius = radius;
}

Circle::~Circle() {
	delete[] this->label;
}

void Circle::print() const {
	std::cout << "Circle " << id << ": x = " << x << " y = "
		<< y << " radius = " << radius << " label = " << std::string(label) << '\n';
}

bool Circle::is_inside(int x, int y) {
	return (this->x - x) * (this->x - x) + (this->y - y) * (this->y - y) <= radius * radius;
}

void Circle::zoom(int factor) {
	radius *= factor;
}
