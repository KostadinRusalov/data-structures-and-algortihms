#pragma once

#include <iterator>

template<class T>
class VectorIterator {
public:
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;

private:
    pointer i;

public:
    VectorIterator(pointer i = nullptr);

    reference operator*() const;

    pointer operator->() const;

    VectorIterator &operator++();

    VectorIterator operator++(int);

    VectorIterator &operator--();

    VectorIterator operator--(int);

    VectorIterator &operator+=(difference_type d);

    VectorIterator &operator-=(difference_type d);

    VectorIterator operator+(difference_type d) const;

    VectorIterator operator-(difference_type d) const;

    reference operator[](difference_type d) const;

    pointer base() const;
};

template<class T>
VectorIterator<T>::VectorIterator(VectorIterator::pointer i) : i(i) {}

template<class T>
typename VectorIterator<T>::reference VectorIterator<T>::operator*() const {
    return *i;
}

template<class T>
typename VectorIterator<T>::pointer VectorIterator<T>::operator->() const {
    return i;
}

template<class T>
VectorIterator<T> &VectorIterator<T>::operator++() {
    ++i;
    return *this;
}

template<class T>
VectorIterator<T> &VectorIterator<T>::operator--() {
    --i;
    return *this;
}

template<class T>
VectorIterator<T> VectorIterator<T>::operator++(int) {
    VectorIterator<T> temp(*this);
    ++i;
    return temp;
}

template<class T>
VectorIterator<T> VectorIterator<T>::operator--(int) {
    VectorIterator<T> temp(*this);
    --i;
    return temp;
}

template<class T>

VectorIterator<T> &VectorIterator<T>::operator+=(difference_type d) {
    i += d;
    return *this;
}

template<class T>

VectorIterator<T> &VectorIterator<T>::operator-=(difference_type d) {
    i -= d;
    return *this;
}

template<class T>

VectorIterator<T> VectorIterator<T>::operator+(difference_type d) const {
    VectorIterator<T> temp(*this);
    temp += d;
    return temp;
}

template<class T>

VectorIterator<T> VectorIterator<T>::operator-(difference_type d) const {
    VectorIterator<T> temp(*this);
    temp -= d;
    return temp;
}

template<class T>
typename VectorIterator<T>::reference VectorIterator<T>::operator[](difference_type d) const {
    return i[d];
}

template<class T>
typename VectorIterator<T>::pointer VectorIterator<T>::base() const {
    return i;
}

template<class T>
bool operator!=(VectorIterator<T> rhs, VectorIterator<T> lhs) {
    return rhs.base() != lhs.base();
}

template<class T>
bool operator==(VectorIterator<T> rhs, VectorIterator<T> lhs) {
    return rhs.base() == lhs.base();
}

template<class T>
bool operator<(VectorIterator<T> rhs, VectorIterator<T> lhs) {
    return rhs.base() < lhs.base();
}

template<class T>
bool operator<=(VectorIterator<T> rhs, VectorIterator<T> lhs) {
    return rhs.base() <= lhs.base();
}

template<class T>
bool operator>(VectorIterator<T> rhs, VectorIterator<T> lhs) {
    return rhs.base() > lhs.base();
}

template<class T>
bool operator>=(VectorIterator<T> rhs, VectorIterator<T> lhs) {
    return rhs.base() >= lhs.base();
}

template<class T>
typename VectorIterator<T>::difference_type operator-(VectorIterator<T> rhs, VectorIterator<T> lhs) {
    return rhs.base() - lhs.base();
}