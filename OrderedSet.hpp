#pragma once

#include "Vector/Vector.hpp"

template<class T>
class OrderedSet {
public:
    typedef T value_type;
    typedef typename Vector<T>::size_type size_type;
    typedef typename Vector<T>::iterator iterator;
    typedef typename Vector<T>::const_iterator const_iterator;
private:
    Vector<T> elements;
public:
    OrderedSet() = default;

    OrderedSet(const Vector<T> &elements);

    OrderedSet(Vector<T> &&elements);

    bool empty() const;

    size_type size() const;

    void clear();

    void add(const T &element);

    void add(T &&element);

    void remove(const T &element);

    bool contains(const T &element) const;

    iterator find(const T &element);

    const_iterator find(const T &element) const;

    iterator begin();

    const_iterator begin() const;

    const_iterator cbegin() const;

    iterator end();

    const_iterator end() const;

    const_iterator cend() const;
};