#include <iostream>
#include <cstring>
#include <cassert>
#include "my_vector.h"

namespace product {

    class Product {
    public:
        Product(const char *name, int quantity, double price);

        Product(const Product &other);

        ~Product();

        friend std::ostream &operator<<(std::ostream &out, const Product &p);

        Product operator=(Product other);

        bool operator==(const Product &other);

    private:
        char *name_;
        int quantity_;
        double price_;
    };

    Product::Product(const char *name, int quantity, double price) : quantity_(quantity), price_(price) {
        name_ = new char[sizeof(char) * (strlen(name) + 1)];
        memcpy(name_, name, strlen(name) + 1);
    }

    Product::Product(const Product &other) : Product(other.name_, other.quantity_, other.price_) {}

    Product Product::operator=(Product other) {
        std::swap(name_, other.name_);
        quantity_ = other.quantity_, price_ = other.price_;
        return *this;
    }

    Product::~Product() {
        delete[] name_;
    }

    bool Product::operator==(const Product &other) {
        return price_ == other.price_ && quantity_ == other.quantity_ && !memcmp(name_, other.name_, strlen(name_));
    }

    void print(const my_vector::my_vector<Product> &v) {
        std::cout << v << std::endl;
    }

    std::ostream &operator<<(std::ostream &out, const Product &p) {
        for (const char *i = p.name_; *i != 0; i++)
            out << *i;
        return out << ' ' << p.quantity_ << ' ' << p.price_;
    }

}


template<typename T>
void test_my_vector(T elem1, T elem2) {
    my_vector::my_vector<T> c;
    try {
        c[5] = elem1;
        assert(false);
    } catch (std::range_error) {}
    try {
        c.pop_back();
        assert(false);
    } catch (std::logic_error) {}
    my_vector::my_vector<T> v, u;
    assert(v.size() == 0);
    assert (v.capacity() == 0);
    v.reserve(1);
    assert(v.size() == 0);
    assert(v.capacity() == 1);
    v.reserve(0);
    assert(v.size() == 0);
    assert(v.capacity() == 1);
    v.reserve(2);
    assert(v.size() == 0);
    assert(v.capacity() == 2);
    v.push_back(elem2);
    assert(v.size() == 1);
    assert(v.capacity() == 2);
    assert(v[0] == elem2);
    v.reserve(3);
    assert(v.size() == 1);
    assert(v.capacity() == 4);
    assert(v[0] == elem2);
    u.push_back(elem1);
    assert(u[0] == elem1);
    v = u;
    assert(v.size() == 1);
    assert(v.capacity() == 1);
    assert(v[0] == elem1);
    v.pop_back();
    assert(v.size() == 0);
    assert(v.capacity() == 1);
    v.reserve(4);
    assert(v.size() == 0);
    assert(v.capacity() == 4);
    u = v;
    u.clear();
    assert(u.empty());
    assert(u.capacity() == 4);
    v.push_back(elem1);
    v[0] = elem2;
    v.push_back(elem1);
    assert(v.size() == 2);
    assert(v.capacity() == 4);
    my_vector::my_vector<T> v_copy(v);
    assert(v_copy.size() == 2);
    assert(v_copy.capacity() == 4);
    u = v_copy;
    assert(u.size() == 2);
    assert(u.capacity() == 4);
}


template<typename T>
void test_my_vector_default_constructible(T elem1, T elem2) {
    my_vector::my_vector<T> v(5);
    assert(v.size() == 5);
    assert(v.capacity() == 8);
    v.push_back(elem1);
    assert(v.size() == 6);
    assert(v.capacity() == 8);
    v.resize(9);
    assert(v.size() == 9);
    assert(v.capacity() == 16);
    assert(v[0] == T() && v[5] == elem1 && v[7] == T());
    my_vector::my_vector<T> u(v);
    assert(u.size() == 9);
    assert(u.capacity() == 16);
    assert(u[0] == T() && u[5] == elem1 && u[7] == T());
    u.clear();
    assert(u.size() == 0);
    assert(u.capacity() == 16);
    u.push_back(elem1);
    assert(u[0] == elem1);
    assert(u.size() == 1);
    assert(u.capacity() == 16);
    u.resize(3);
    assert(u.size() == 3);
    assert(u.capacity() == 16);
}

int main() {
    test_my_vector<int>(5, 10);
    test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));
    test_my_vector_default_constructible<char>(4, 9);

    return 0;
}