#ifndef VECTOR_MY_VECTOR_IMPL_H
#define VECTOR_MY_VECTOR_IMPL_H

#include "my_vector.h"
#include <algorithm>
#include <memory>
#include <iostream>

template<typename T>
my_vector::my_vector<T>::my_vector(std::size_t n) {
    resize(n);
}

template<typename T>
my_vector::my_vector<T>::my_vector(my_vector const &other) {
    reserve(other.capacity_);
    size_ = other.size_;
    for (std::size_t i = 0; i < other.size_; i++) {
        new(array_ + i) T(other.array_[i]);
    }
}

template<typename T>
my_vector::my_vector<T> &my_vector::my_vector<T>::operator=(my_vector &&other) noexcept {
    if (this != &other) {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(array_, other.array_);
    }
    return *this;
}

template<typename T>
my_vector::my_vector<T> &my_vector::my_vector<T>::operator=(const my_vector <T> &other) {
    my_vector <T> other_copy(other);
    *this = std::move(other_copy);
    return *this;
}

template<typename T>
my_vector::my_vector<T>::my_vector(my_vector &&other) noexcept : my_vector() {
    my_vector < T > tmp(other);
    *this = std::move(tmp);
}

template<typename T>
my_vector::my_vector<T>::~my_vector() {
    for (size_t i = 0; i < size_; i++)
        array_[i].~T();
    if (capacity_ != 0)
        delete[] reinterpret_cast<char *>(array_);
}

template<typename T>
std::size_t my_vector::my_vector<T>::size() const noexcept {
    return size_;
}

template<typename T>
std::size_t my_vector::my_vector<T>::capacity() const noexcept {
    return capacity_;
}

template<typename T>
bool my_vector::my_vector<T>::empty() const noexcept {
    return size_ == 0;
}

template<typename T>
void my_vector::my_vector<T>::resize(std::size_t n) {
    reserve(n);
    if (n >= size_)
        for (std::size_t i = size_; i < n; i++)
            new(array_ + i) T();
    else
        for (size_t i = n; i < size_; i++)
            array_[i].~T();
    size_ = n;
}

template<typename T>
void my_vector::my_vector<T>::reserve(std::size_t n) {
    if (capacity_ >= n)
        return;
    size_t cap = 1;
    for (cap = 1; cap < n; cap *= 2) {}
    if (cap != n) n = cap;

    T *temp = reinterpret_cast<T *>(new char[sizeof(T) * n]);
    for (size_t i = 0; i < size_; i++) {
        new(temp + i) T(std::move(array_[i]));
    }
    for (size_t i = 0; i < size_; i++)
        array_[i].~T();
    if (capacity_ != 0)
        delete[] reinterpret_cast<char *>(array_);
    array_ = std::move(temp);
    capacity_ = n;
}

template<typename T>
T &my_vector::my_vector<T>::operator[](std::size_t index) {
    if (index >= size_) {
        throw std::range_error("Out of range");
    }
    return array_[index];
}

template<typename T>
const T &my_vector::my_vector<T>::operator[](std::size_t index) const {
    if (index >= size_) {
        throw std::range_error("Out of range");
    }
    return array_[index];
}

template<typename T>
void my_vector::my_vector<T>::push_back(T t) {
    if (size_ == capacity_) {
        reserve(size_ + 1);
    }
    new(array_ + size_) T(std::move(t));
    size_++;
}

template<typename T>
void my_vector::my_vector<T>::pop_back() {
    if (empty()) {
        throw std::logic_error("Vector is empty");
    }
    size_--;
    array_[size_].~T();
}

template<typename T>
void my_vector::my_vector<T>::clear() noexcept {
    for (size_t i = 0; i < size_; i++)
        array_[i].~T();
    size_ = 0;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const my_vector::my_vector<T> &v) {
    if (v.size())
        out << v[0];
    for (std::size_t i = 1; i < v.size(); i++) {
        out << ' ' << v[i];
    }
}

#endif //VECTOR_MY_VECTOR_IMPL_H
