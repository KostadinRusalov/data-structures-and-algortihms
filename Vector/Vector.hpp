#pragma once

#include <cstddef>
#include <utility>
#include <stdexcept>
#include "VectorIterator.hpp"

template<class T>
class Vector {
public:
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T &reference;
    typedef const T &const_reference;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef VectorIterator<value_type> iterator;
    typedef VectorIterator<const value_type> const_iterator;

private:
    pointer data_;
    size_type size_;
    size_type capacity_;

    static const short INITIAL_CAPACITY = 2;
public:
    // MARK: big 6 -d
    Vector();

    Vector(std::initializer_list<value_type> data);

    explicit Vector(size_type capacity);

    Vector(const Vector<T> &other);

    Vector(Vector<T> &&other) noexcept;

    Vector<T> &operator=(const Vector<T> &other);

    Vector<T> &operator=(Vector<T> &&other) noexcept;

    ~Vector();

    void assign(size_type count, const T &value);

    template<class InputIt>
    void assign(InputIt first, InputIt last);

    void assign(std::initializer_list<value_type> data);

    // MARK: element access -d
    const_reference at(size_type idx) const;

    reference at(size_type idx);

    const_reference operator[](size_type idx) const;

    reference operator[](size_type idx);

    const_reference front() const;

    reference front();

    const_reference back() const;

    reference back();

    const_pointer data() const noexcept;

    pointer data() noexcept;

    // MARK: iterators -d
    const_iterator begin() const noexcept;

    iterator begin() noexcept;

    const_iterator cbegin() const noexcept;

    const_iterator end() const noexcept;

    iterator end() noexcept;

    const_iterator cend() const noexcept;

    // MARK: capacity -d
    bool empty() const noexcept;

    size_type size() const noexcept;


    size_type capacity() const noexcept;

    // MARK: modifiers -d
    void clear() noexcept;

    iterator insert(const_iterator pos, const T &value);

    iterator insert(const_iterator pos, T &&value);

    iterator insert(const_iterator pos, size_t count, const T &value);

    iterator insert(const_iterator pos, std::initializer_list<T> ilist);

    iterator erase(const_iterator pos);

    iterator erase(const_iterator first, const_iterator last);

    void pushBack(const T &value);

    void pushBack(T &&value);

    void popBack();

    void resize(size_t capacity);

private:
    // MARK: big 6 helpers -d
    void free();

    void copyFrom(const Vector<T> &other);

    void moveFrom(Vector<T> &&other);
};

// MARK: big 6 -i
template<class T>
Vector<T>::Vector() : Vector<T>(0) {}

template<class T>
Vector<T>::Vector(std::initializer_list<T> data) {
    size_ = data.size();
    capacity_ = data.size() * 2;
    data_ = new T[capacity_];

    size_t idx = 0;
    for (auto el = data.begin(); el != data.end(); ++el) {
        data_[idx++] = *el;
    }
}

template<class T>
Vector<T>::Vector(size_t capacity) : size_{0}, capacity_{capacity} {
    data_ = new T[capacity_];
}

template<class T>
Vector<T>::Vector(const Vector<T> &other) {
    copyFrom(other);
}

template<class T>
Vector<T>::Vector(Vector<T> &&other) noexcept {
    moveFrom(std::move(other));
}

template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;

}

template<class T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template<class T>
Vector<T>::~Vector() {
    free();
}

template<class T>
void Vector<T>::assign(Vector::size_type count, const T &value) {
    free();
    size_ = capacity_ = count;
    data_ = new T[capacity_];

    for (size_type i = 0; i < count; ++i) {
        data_[i] = value;
    }
}

template<class T>
template<class InputIt>
void Vector<T>::assign(InputIt first, InputIt last) {
    free();
    size_ = capacity_ = last - first;
    data_ = new T[capacity_];

    size_type i = 0;
    for (auto it = first; it != last; ++it) {
        data_[i++] = *it;
    }
}

template<class T>
void Vector<T>::assign(std::initializer_list<value_type> data) {
    assign(data.begin(), data.end());
}

// MARK: element access -i
template<class T>
typename Vector<T>::const_reference Vector<T>::at(size_t idx) const {
    if (idx > size_) {
        throw std::out_of_range("index is out of range!");
    }
    return data_[idx];
}

template<class T>
typename Vector<T>::reference Vector<T>::at(size_t idx) {
    if (idx > size_) {
        throw std::out_of_range("index is out of range!");
    }
    return data_[idx];
}

template<class T>
typename Vector<T>::const_reference Vector<T>::operator[](size_t idx) const {
    return data_[idx];
}

template<class T>
typename Vector<T>::reference Vector<T>::operator[](size_t idx) {
    return data_[idx];
}

template<class T>
typename Vector<T>::const_reference Vector<T>::front() const {
    if (empty()) {
        throw std::length_error("vector is empty!");
    }
    return data_[0];
}

template<class T>
typename Vector<T>::reference Vector<T>::front() {
    if (empty()) {
        throw std::length_error("vector is empty!");
    }
    return data_[0];
}

template<class T>
typename Vector<T>::const_reference Vector<T>::back() const {
    if (empty()) {
        throw std::length_error("vector is empty!");
    }
    return data_[size_ - 1];
}

template<class T>
typename Vector<T>::reference Vector<T>::back() {
    if (empty()) {
        throw std::length_error("vector is empty!");
    }
    return data_[size_ - 1];
}

template<class T>
typename Vector<T>::const_pointer Vector<T>::data() const noexcept {
    return data_;
}

template<class T>
typename Vector<T>::pointer Vector<T>::data() noexcept {
    return data_;
}

// MARK: iterators -i
template<class T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept {
    return const_iterator(data_);
}

template<class T>
typename Vector<T>::iterator Vector<T>::begin() noexcept {
    return iterator(data_);
}

template<class T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept {
    return const_iterator(data_);
}

template<class T>
typename Vector<T>::const_iterator Vector<T>::end() const noexcept {
    return const_iterator(&data_[size_]);
}

template<class T>
typename Vector<T>::iterator Vector<T>::end() noexcept {
    return iterator(&data_[size_]);
}

template<class T>
typename Vector<T>::const_iterator Vector<T>::cend() const noexcept {
    return const_iterator(&data_[size_]);
}

// MARK: capacity -i
template<class T>
bool Vector<T>::empty() const noexcept {
    return size_ == 0;
}

template<class T>
typename Vector<T>::size_type Vector<T>::size() const noexcept {
    return size_;
}

template<class T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept {
    return capacity_;
}

// MARK: modifiers -i
template<class T>
void Vector<T>::clear() noexcept {
    for (size_type i = 0; i < size_; ++i) {
        data_[i] = T();
    }
    size_ = 0;
}

template<class T>
typename Vector<T>::iterator Vector<T>::insert(Vector<T>::const_iterator pos, const T &value) {

}

template<class T>
typename Vector<T>::iterator Vector<T>::erase(Vector::const_iterator pos) {
    difference_type dist = pos - cbegin();
    iterator el = begin() + dist;

    if (el == end() - 1) {
        *el = T();
        size_--;
        return end();
    }

    iterator last = end() - 1;
    for (auto it = el; it != last; ++it) {
        *it = std::move(*(it + 1));
    }
    size_--;
    return end();
}

template<class T>
void Vector<T>::pushBack(const T &value) {
    if (capacity_ == 0) {
        resize(INITIAL_CAPACITY);
    }
    if (size_ == capacity_) {
        resize(2 * capacity_);
    }

    data_[size_++] = value;
}

template<class T>
void Vector<T>::pushBack(T &&value) {
    if (capacity_ == 0) {
        resize(INITIAL_CAPACITY);
    }
    if (size_ == capacity_) {
        resize(2 * capacity_);
    }

    data_[size_++] = std::move(value);
}

template<class T>
void Vector<T>::popBack() {
    if (empty()) {
        throw std::length_error("vector is empty!");
    }
    size_--;

    if (capacity_ > 4 * size_) {
        resize(capacity_ / 2);
    }
}

template<class T>
void Vector<T>::resize(size_t capacity) {
    capacity_ = capacity;
    T *newData = new T[capacity_];

    for (size_t i = 0; i < size_; ++i) {
        newData[i] = data_[i];
    }

    free();
    data_ = newData;
}

// MARK: big 6 helpers -i
template<class T>
void Vector<T>::free() {
    delete[] data_;
    data_ = nullptr;
}

template<class T>
void Vector<T>::copyFrom(const Vector<T> &other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new T[capacity_];

    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

template<class T>
void Vector<T>::moveFrom(Vector<T> &&other) {
    size_ = other.size_;
    capacity_ = other.capacity_;

    data_ = other.data_;
    other.data_ = nullptr;
}