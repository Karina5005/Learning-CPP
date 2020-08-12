#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <iostream>

namespace my_vector {

    template<typename T>
    class my_vector {
    public:
        explicit my_vector() noexcept = default;

        explicit my_vector(std::size_t n);

        my_vector(my_vector const &other);

        my_vector(my_vector &&other) noexcept;

        my_vector<T> &operator=(const my_vector<T> &other);

        my_vector<T> &operator=(my_vector &&other) noexcept;

        ~my_vector();

        std::size_t size() const noexcept;

        std::size_t capacity() const noexcept;

        bool empty() const noexcept;

        void resize(std::size_t n);

        void reserve(std::size_t n);

        T &operator[](std::size_t index);

        const T &operator[](std::size_t index) const;

        void push_back(T t);

        void pop_back();

        void clear() noexcept;

    private:
        size_t capacity_ = 0;
        size_t size_ = 0;
        T *array_ = nullptr;
    };

}

template<typename T>
std::ostream &operator<<(std::ostream &out, const my_vector::my_vector<T> &v);

#include "my_vector_impl.h"

#endif  // MY_VECTOR_H_