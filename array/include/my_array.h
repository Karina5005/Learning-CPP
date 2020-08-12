#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <stdexcept>
#include <limits.h>

namespace lab_13 {
    static void check(std::size_t index, std::size_t N) {
        if (index >= N || index < 0) throw std::out_of_range("Out of range");
    }

    template<typename T, std::size_t N>
    class my_array {
    public:
        T &at(std::size_t index);

        const T &at(std::size_t index) const;

        T &operator[](std::size_t index);

        const T &operator[](std::size_t index) const;

        bool empty() const;

        std::size_t size() const;

        void fill(const T &val);

    private:
        T array_[N];
    };

    template<typename T, std::size_t N>
    T &my_array<T, N>::at(std::size_t index) {
        check(index, N);
        return array_[index];
    }

    template<typename T, std::size_t N>
    const T &my_array<T, N>::at(std::size_t index) const {
        check(index, N);
        return array_[index];
    }

    template<typename T, std::size_t N>
    T &my_array<T, N>::operator[](std::size_t index) {
        return array_[index];
    }

    template<typename T, std::size_t N>
    const T &my_array<T, N>::operator[](std::size_t index) const {
        return array_[index];
    }

    template<typename T, std::size_t N>
    bool my_array<T, N>::empty() const {
        return N == 0;
    }

    template<typename T, std::size_t N>
    std::size_t my_array<T, N>::size() const {
        return N;
    }

    template<typename T, std::size_t N>
    void my_array<T, N>::fill(const T &val) {
        for (std::size_t i = 0; i < N; i++) {
            array_[i] = val;
        }
    }

    template<std::size_t N>
    class my_array<bool, N> {
    private:
        uint8_t array_[N / CHAR_BIT + bool(N % CHAR_BIT)];

        class reference {
        private:
            uint8_t &place_;
            uint8_t index_;
        public:
            reference(uint8_t &place, std::size_t index);

            reference &operator=(bool other);

            reference &operator=(const reference &other);

            operator const bool() const;
        };

    public:
        reference at(std::size_t index);

        bool at(std::size_t index) const;

        reference operator[](std::size_t index);

        bool operator[](std::size_t index) const;

        bool empty() const;

        std::size_t size() const;

        void fill(bool val);
    };

    template<std::size_t N>
    my_array<bool, N>::reference::reference(uint8_t &place, std::size_t index):place_(place), index_(index) {}

    template<std::size_t N>
    typename my_array<bool, N>::reference &my_array<bool, N>::reference::operator=(bool other) {
        place_ = (place_ & (~(1 << index_))) | ((uint8_t(other)) << index_);
        return *this;
    }

    template<std::size_t N>
    typename my_array<bool, N>::reference &
    my_array<bool, N>::reference::operator=(const lab_13::my_array<bool, N>::reference &other) {
        *this = bool(other);
        return *this;
    }

    template<std::size_t N>
    my_array<bool, N>::reference::operator const bool() const {
        return place_ & (1 << index_);
    }

    template<std::size_t N>
    typename my_array<bool, N>::reference my_array<bool, N>::at(std::size_t index) {
        check(index, N);
        return reference(array_[index / CHAR_BIT], index % CHAR_BIT);
    }

    template<std::size_t N>
    bool my_array<bool, N>::at(std::size_t index) const {
        check(index, N);
        return (*this)[index];
    }

    template<std::size_t N>
    typename my_array<bool, N>::reference my_array<bool, N>::operator[](std::size_t index) {
        return reference(array_[index / CHAR_BIT], index % CHAR_BIT);
    }

    template<std::size_t N>
    bool my_array<bool, N>::operator[](std::size_t index) const {
        return (array_[index / CHAR_BIT] & (1 << (index % CHAR_BIT))) == (1 << (index % CHAR_BIT));
    }

    template<std::size_t N>
    bool my_array<bool, N>::empty() const {
        return N == 0;
    }

    template<std::size_t N>
    std::size_t my_array<bool, N>::size() const {
        return N;
    }

    template<std::size_t N>
    void my_array<bool, N>::fill(bool val) {
        for (std::size_t i = 0; i < N / CHAR_BIT + bool(N % CHAR_BIT); i++) {
            array_[i] = val ? -1 : 0;
        }
    }

}  // namespace lab_13

#endif  // MY_ARRAY_H_
