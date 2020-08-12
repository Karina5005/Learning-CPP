#ifndef LAB_11_BIN_MANIP_H
#define LAB_11_BIN_MANIP_H

#include <iostream>
#include <string.h>


class write_le_int32 {
public:
	explicit write_le_int32(int32_t a) { _num = a; }
	std::ostream &operator()(std::ostream &out) const;

private:
	int32_t _num;
};

class read_le_int32 {
public:
	explicit read_le_int32(int32_t &a) { _num = &a; }
	std::istream &operator()(std::istream &in) const;

private:
	int32_t *_num;
};

class write_bool {
public:
	explicit write_bool(bool a) { _val = a; }
	std::ostream &operator()(std::ostream &out) const;

private:
	bool _val;
};

class read_bool {
public:
	explicit read_bool(bool &a) { _val = &a; }
	std::istream &operator()(std::istream &in) const;

private:
	bool *_val;
};

class write_c_str {
public:
	explicit write_c_str(char *a) { _str = a; }
	std::ostream &operator()(std::ostream &out) const;

private:
	char *_str;
	char _x = 0;
};

class read_c_str {
public:
	explicit read_c_str(char **a, int size) { _str = a; _size = size; }
	std::istream &operator()(std::istream &in) const;

private:
	char **_str;
	int32_t _size;
};

#endif

