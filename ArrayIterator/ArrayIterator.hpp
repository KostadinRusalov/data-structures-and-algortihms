#pragma once

#include <iterator>

template<class T>
class ArrayIterator {
public:
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;

private:
    pointer i;

public:
    ArrayIterator(pointer i = nullptr);

    reference operator*() const;

    pointer operator->() const;

    ArrayIterator &operator++();

    ArrayIterator operator++(int);

    ArrayIterator &operator--();

    ArrayIterator operator--(int);

    ArrayIterator &operator+=(difference_type d);

    ArrayIterator &operator-=(difference_type d);

    ArrayIterator operator+(difference_type d) const;

    ArrayIterator operator-(difference_type d) const;

    reference operator[](difference_type d) const;

    pointer base() const;
};

template<class T>
ArrayIterator<T>::ArrayIterator(ArrayIterator::pointer i) : i(i) {}

template<class T>
typename ArrayIterator<T>::reference ArrayIterator<T>::operator*() const {
    return *i;
}

template<class T>
typename ArrayIterator<T>::pointer ArrayIterator<T>::operator->() const {
    return i;
}

template<class T>
ArrayIterator<T> &ArrayIterator<T>::operator++() {
    ++i;
    return *this;
}

template<class T>
ArrayIterator<T> &ArrayIterator<T>::operator--() {
    --i;
    return *this;
}

template<class T>
ArrayIterator<T> ArrayIterator<T>::operator++(int) {
    ArrayIterator<T> temp(*this);
    ++i;
    return temp;
}

template<class T>
ArrayIterator<T> ArrayIterator<T>::operator--(int) {
    ArrayIterator<T> temp(*this);
    --i;
    return temp;
}

template<class T>

ArrayIterator<T> &ArrayIterator<T>::operator+=(difference_type d) {
    i += d;
    return *this;
}

template<class T>

ArrayIterator<T> &ArrayIterator<T>::operator-=(difference_type d) {
    i -= d;
    return *this;
}

template<class T>

ArrayIterator<T> ArrayIterator<T>::operator+(difference_type d) const {
    ArrayIterator<T> temp(*this);
    temp += d;
    return temp;
}

template<class T>

ArrayIterator<T> ArrayIterator<T>::operator-(difference_type d) const {
    ArrayIterator<T> temp(*this);
    temp -= d;
    return temp;
}

template<class T>
typename ArrayIterator<T>::reference ArrayIterator<T>::operator[](difference_type d) const {
    return i[d];
}

template<class T>
typename ArrayIterator<T>::pointer ArrayIterator<T>::base() const {
    return i;
}

template<class T>
bool operator!=(ArrayIterator<T> rhs, ArrayIterator<T> lhs) {
    return rhs.base() != lhs.base();
}

template<class T>
bool operator==(ArrayIterator<T> rhs, ArrayIterator<T> lhs) {
    return rhs.base() == lhs.base();
}

template<class T>
bool operator<(ArrayIterator<T> rhs, ArrayIterator<T> lhs) {
    return rhs.base() < lhs.base();
}

template<class T>
bool operator<=(ArrayIterator<T> rhs, ArrayIterator<T> lhs) {
    return rhs.base() <= lhs.base();
}

template<class T>
bool operator>(ArrayIterator<T> rhs, ArrayIterator<T> lhs) {
    return rhs.base() > lhs.base();
}

template<class T>
bool operator>=(ArrayIterator<T> rhs, ArrayIterator<T> lhs) {
    return rhs.base() >= lhs.base();
}

template<class T>
typename ArrayIterator<T>::difference_type operator-(ArrayIterator<T> rhs, ArrayIterator<T> lhs) {
    return rhs.base() - lhs.base();
}