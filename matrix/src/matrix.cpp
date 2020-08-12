//
// Created by anisi on 22.02.2020.
//

#include "matrix.h"
#include <iostream>
#include <fstream>
#include <exception>
#include <string>

static void clear_data(int**& m, std::size_t& row_) {
	if (m == nullptr || row_ == 0) return;
    for (int k = 0; k < row_; k++) {
        delete[] m[k];
    }
    delete[] m;
}

static void create_data(int**& m, std::size_t& row, std::size_t& col) {
    m = new int*[row];
    for (int i = 0; i < row; i++) {
        m[i] = new int[col];
    }
}

matrix::matrix(std::size_t row, std::size_t col): col_(col), row_(row) {
    create_data(m_, row_, col_);
}

matrix::~matrix() {
    clear_data(m_, row_);
    row_ = 0;
    col_ = 0;
}

void matrix::print() {
    for (int i = 0; i < row_; i++) {
        for (int j = 0; j < col_; j++) {
            elem(i, j);
            std:: cout << " ";
        }
        std::cout << "\n";
    }
}

void matrix::add(matrix &other) {
    if (row_ != other.row_ || col_ != other.col_) {
        throw MatrixException("ADD: dimensions do not match.");
    }

    for (int i = 0; i < row_; i++) {
        for (int j = 0; j < col_; j++) {
            m_[i][j] += other.get_elem(i, j);
        }
    }
}

void matrix::mul(matrix &other) {
    if (col_ != other.row_) {
        throw MatrixException("MUL: #arg1.columns != #arg2.rows");
    }

    int **tmp;
    create_data(tmp, row_, other.col_);

    for (int i = 0; i < row_; i++) {
        for (int j = 0; j < other.col_; j++) {
            tmp[i][j] = 0;
            for (int k = 0; k < col_; k++)
                tmp[i][j] += m_[i][k] * other.m_[k][j];
        }
    }

    clear_data(m_, row_);

    col_ = other.col_;
    create_data(m_, row_, col_);

    for (int i = 0; i < row_; i++) {
        for (int j = 0; j < col_; j++) {
            m_[i][j] = tmp[i][j];
        }
    }

    clear_data(tmp, row_);
}

int matrix::get_elem(std::size_t row, std::size_t col) {
    return m_[row][col];
}

void matrix::elem(std::size_t row, std::size_t col) {
    if (row > row_ || col > col_ || row < 0 || col < 0) {
        throw MatrixException("ACCESS: bad index.");
    }
    std::cout << get_elem(row, col);
}

void matrix::load() {
    std::string name;
    std::cin >> name;
    std::ifstream file(name);
    std::size_t rows, cols;
    int value;

    if (!file.is_open()) {
        throw MatrixException("LOAD: unable to open file.");
    }
    if (!(file >> rows >> cols)) {
        throw MatrixException("LOAD: invalid file format.");
    }
	
    clear_data(m_, row_);
    row_ = rows;
    col_ = cols;
    create_data(m_, row_, col_);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(file >> value)) {
                clear_data(m_, row_);
                row_ = 0;
                col_ = 0;
                throw MatrixException("LOAD: invalid file format.");
            } else {
                m_[i][j] = value;
            }
        }
    }

    file.close();
}

