#pragma once

#include "../Vector/Vector.hpp"
#include "../Algorithm/Algorithm.hpp"

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

    size_type capacity() const;

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

template<class T>
OrderedSet<T>::OrderedSet(const Vector<T> &elements) {
    for (auto &element: elements) {
        add(element);
    }
}

template<class T>
OrderedSet<T>::OrderedSet(Vector<T> &&elements) {
    for (auto &element: elements) {
        add(std::move(element));
    }
}

template<class T>
bool OrderedSet<T>::empty() const {
    return elements.empty();
}

template<class T>
typename OrderedSet<T>::size_type OrderedSet<T>::size() const {
    return elements.size();
}

template<class T>
typename OrderedSet<T>::size_type OrderedSet<T>::capacity() const {
    return elements.capacity();
}

template<class T>
void OrderedSet<T>::clear() {
    elements.clear();
}

template<class T>
void OrderedSet<T>::add(const T &element) {
    if (contains(element)) {
        return;
    }
    elements.pushBack(element);
    size_type last = elements.size() - 1;

    while (last > 0) {
        if (elements[last - 1] < elements[last]) {
            break;
        }

        swap(elements[last], elements[last - 1]);
        --last;
    }
}

template<class T>
void OrderedSet<T>::add(T &&element) {
    if (contains(element)) {
        return;
    }
    elements.pushBack(std::move(element));
    size_type last = elements.size() - 1;

    while (last > 0) {
        if (elements[last - 1] < elements[last]) {
            break;
        }

        Algorithm::swap(elements[last], elements[last - 1]);
        --last;
    }
}

template<class T>
void OrderedSet<T>::remove(const T &element) {
    const_iterator el = find(element);
    if (el != cend()) {
        elements.erase(el);
    }
}

template<class T>
bool OrderedSet<T>::contains(const T &element) const {
    return find(element) != cend();
}

template<class T>
typename OrderedSet<T>::iterator OrderedSet<T>::find(const T &element) {
    if (empty()) {
        return end();
    }
    int left = 0;
    int right = size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (elements[mid] == element) {
            return iterator(&elements[mid]);
        } else if (elements[mid] < element) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return end();
}

template<class T>
typename OrderedSet<T>::const_iterator OrderedSet<T>::find(const T &element) const {
    if (empty()) {
        return cend();
    }
    int left = 0;
    int right = size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (elements[mid] == element) {
            return const_iterator(&elements[mid]);
        } else if (elements[mid] < element) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return cend();
}

template<class T>
typename OrderedSet<T>::iterator OrderedSet<T>::begin() {
    return elements.begin();
}

template<class T>
typename OrderedSet<T>::const_iterator OrderedSet<T>::begin() const {
    return elements.begin();
}

template<class T>
typename OrderedSet<T>::const_iterator OrderedSet<T>::cbegin() const {
    return elements.cbegin();
}

template<class T>
typename OrderedSet<T>::iterator OrderedSet<T>::end() {
    return elements.end();
}

template<class T>
typename OrderedSet<T>::const_iterator OrderedSet<T>::end() const {
    return elements.end();
}

template<class T>
typename OrderedSet<T>::const_iterator OrderedSet<T>::cend() const {
    return elements.cend();
}