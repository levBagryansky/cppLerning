#include "Stack.h"
#include <cmath>

BoolStack<bool>::BoolStack(): size_(0), capacity_((32 + 7)/8), data_(new unsigned char[capacity_]){}

BoolStack<bool>::BoolStack(size_t len): size_(0), capacity_((len + 7)/8), data_(new unsigned char[capacity_]){}

BoolStack<bool>::BoolStack(const BoolStack& other): size_(other.size_), capacity_(other.capacity_), data_(new unsigned char[(other.capacity_ + 7)/8]){
    std::copy(other.data_, other.data_ + (size_ + 7) / 8, data_);
}

BoolStack<bool>::BoolStack(BoolStack &&other): data_(other.data_), size_(other.size_), capacity_(other.capacity_){
    other.data_ = nullptr;
}

BoolStack<bool>::~BoolStack(){
    delete[] data_;
}

size_t BoolStack<bool>::getSize() const {
    return size_;
}

bool BoolStack<bool>::isEmpty() const{
    return !size_;
}

void BoolStack<bool>::push(bool value) {
    if (size_ == capacity_){
        auto * newData = new unsigned char[2 * ((capacity_ + 7) / 8)];
        std::copy(data_, data_ + (size_ + 7) / 8, newData);
        delete[] data_;
        data_ = newData;
        capacity_ = 2 * ((capacity_ + 7) / 8) * 8;
    }

    int i = size_ % 8;
    data_[size_ / 8] = ((data_[size_ / 8] & (~(1 << i))) + (value << i));
    size_++;
}

void BoolStack<bool>::pop(){
    if(size_ == 0){
        exit(1);
    }
    size_--;
}

bool BoolStack<bool>::top() const {
    if (size_ == 0){
        exit(2);
    }

    unsigned char containElem = data_[(size_-1)  / 8];
    containElem  = containElem >> ((size_-1) % 8);
    containElem &= 1;
    return containElem;
}

void BoolStack<bool>::swap(BoolStack<bool> &other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
}

BoolStack<bool>& BoolStack<bool>::operator=(const BoolStack<bool> &other) {
    if (this == &other){
        return *this;
    }

    capacity_ = other.capacity_;
    size_ = other.size_;

    delete[] data_;
    data_ = new unsigned char [(capacity_ + 7) / 8];
    std::copy(other.data_, other.data_ + (size_ + 7) / 8 , data_);
    return *this;
}

BoolStack<bool>& BoolStack<bool>::operator=(BoolStack<bool>&& other) {
    if (this == &other){
        return *this;
    }

    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = other.data_;
    other.data_ = nullptr;
    return *this;
}

bool BoolStack<bool>::operator==(const BoolStack<bool> &other) const{
    if (size_ != other.size_){
        return false;
    }

    for (int i = 0; i < size_ / 8; ++i) {
        if (data_[i] != other.data_[i]){
            return false;
        }
    }

    for (int i = 0; i < size_ % 8; ++i) {
        unsigned char elem1 = data_[(size_-1)  / 8];
        elem1  = elem1 >> (i);
        elem1 &= 1;

        unsigned char elem2 = other.data_[(size_-1)  / 8];
        elem2  = elem2 >> (i);
        elem2 &= 1;

        if (elem1 != elem2){
            return false;
        }
    }
    return true;
}

bool BoolStack<bool>::operator!=(const BoolStack<bool> &other) const{
    return !(operator==(other));
}