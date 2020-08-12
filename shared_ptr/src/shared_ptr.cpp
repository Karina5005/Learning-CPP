#include "matrix.hpp"
#include "shared_ptr.hpp"


shared_ptr::shared_ptr(Matrix* obj) {
	if (obj != nullptr) {
		storage_ = new Storage(obj);
	} else {
		storage_ = nullptr;
	}
}

shared_ptr::shared_ptr(const shared_ptr &other) {
	storage_ = other.storage_;
	storage_->incr();
	
}

shared_ptr& shared_ptr::operator=(const shared_ptr &other) {
	storage_->decr();
	if(storage_->getCounter() == 0) {
		delete storage_;
	}
	storage_ = other.storage_;
	storage_->incr();
	return *this;
}

shared_ptr::~shared_ptr() {
	storage_->decr();
	if (storage_->getCounter() == 0){
		delete storage_;
	}
}

Matrix* shared_ptr::ptr() const {
	if(this == nullptr) {
		return nullptr;
	}
	return storage_->getObject();
}

bool shared_ptr::isNull() const {
	return storage_== nullptr;
}

void shared_ptr::reset(Matrix* obj) {
	*this = shared_ptr(obj);
}

Matrix* shared_ptr::operator->() const {
	return storage_->getObject();
}

Matrix& shared_ptr::operator*() const {
	return *(storage_->getObject());
}

shared_ptr::Storage::Storage(Matrix* mtx) {
	data_ = mtx;
	ref_count_ = 1;
}

shared_ptr::Storage::~Storage() {
	delete data_;
}

void shared_ptr::Storage::incr() {
	if (this != nullptr) {
		ref_count_++;
	}
}

void shared_ptr::Storage::decr() {
	if (this != nullptr) {
		ref_count_--;
	}
}

int shared_ptr::Storage::getCounter() const {
	if (this == nullptr) {
		return 0;
	}
	return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
	if (this == nullptr) {
		return nullptr;
	}
	return data_;
}
