#define _CRT_SECURE_NO_WARNINGS
#include "bin_manip.h"
#include<iomanip>
#include <string>
#include <cstring>

std::ostream &write_bool::operator()(std::ostream &out) const {
	unsigned char res;
	if (this->_val) {
		res = 1;
	}
	else {
		res = 0;
	}
	out << res;
	return out;
}

std::istream &read_bool::operator()(std::istream &in) const {
	unsigned char byte;
	in >> byte;
	if (byte == 1) {
		*_val = true;
	}
	else {
		*_val = false;
	}
	return in;
}

std::ostream &write_le_int32::operator()(std::ostream &out) const {
	out.write((char *)&_num, sizeof(int32_t));
	return out;
}

std::istream &read_le_int32::operator()(std::istream &in) const {
	in.read((char *)_num, sizeof(int32_t));
	return in;
}

std::ostream &write_c_str::operator()(std::ostream &out) const {
	out << std::string(_str);
	out.write((char *)&_x, sizeof(char));
	return out;
}

std::istream &read_c_str::operator()(std::istream &in) const {
	std::string s;
	char byte;
	s = "";
	in.read((char *)&byte, sizeof(char));
	while (byte) {
		s += byte;
		in.read((char *)&byte, sizeof(char));
	}
	*_str = new char[s.size() + 1];
	strcpy(*_str, s.c_str());
	return in;
}
