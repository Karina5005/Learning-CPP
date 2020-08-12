//
// Created by anisi on 22.02.2020.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H
#include <iostream>
#include <exception>

class MatrixException: public std::exception {
private:
    std::string m_error;

public:
    explicit MatrixException(std::string error): m_error(error){}

    const char* what() const noexcept override { return m_error.c_str(); }
};

class matrix{
public:
    matrix(std::size_t col, std::size_t row);

    matrix(): col_(0), row_(0), m_(nullptr) {}

    ~matrix();

    void load();

    void print();

    void add(matrix& other);

    void mul(matrix& other);

    int get_elem(std::size_t row, std::size_t col);

    void elem(std::size_t row, std::size_t col);

private:
    std::size_t col_ = 0, row_ = 0;
    int** m_;
};
#endif //MATRIX_MATRIX_H
