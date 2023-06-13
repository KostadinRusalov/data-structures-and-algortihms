#pragma once

template<class T>
void swap(T &rhs, T &lhs) {
    T copy(rhs);
    rhs = lhs;
    lhs = copy;
}

template<class Iter, class T>
Iter find(Iter first, Iter last, const T &element) {
    for (auto it = first; it != last; ++it) {
        if (element == *it) {
            return it;
        }
    }
    return last;
}