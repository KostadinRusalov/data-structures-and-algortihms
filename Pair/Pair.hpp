#pragma once

#include <utility>

template<class T, class U>
struct Pair {
    typedef T first_type;
    typedef U second_type;

    T first;
    U second;

    Pair();

    Pair(const T &first, const U &second);

    Pair(T &&first, U &&second) noexcept;

    void swap(Pair<T, U> &with) noexcept;
};

template<class T, class U>
Pair<T, U>::Pair() : first{}, second{} {}

template<class T, class U>
Pair<T, U>::Pair(const T &first, const U &second)
        : first{first}, second{second} {}

template<class T, class U>
Pair<T, U>::Pair(T &&first, U &&second) noexcept
        : first{std::move(first)}, second{std::move(second)} {}

template<class T, class U>
void Pair<T, U>::swap(Pair<T, U> &with) noexcept {
    Pair<T, U> temp(*this);
    *this = with;
    with = temp;
}

template<class T1, class U1, class T2, class U2>
bool operator==(const Pair<T1, U1> &rhs, const Pair<T2, U2> &lhs) {
    return rhs.first == lhs.first && rhs.second == rhs.second;
}

template<class T1, class U1, class T2, class U2>
bool operator!=(const Pair<T1, U1> &rhs, const Pair<T2, U2> &lhs) {
    return !(rhs == lhs);
}

template<class T1, class U1, class T2, class U2>
bool operator<(const Pair<T1, U1> &rhs, const Pair<T2, U2> &lhs) {
    return rhs.first < lhs.first && rhs.second < rhs.second;
}

template<class T1, class U1, class T2, class U2>
bool operator<=(const Pair<T1, U1> &rhs, const Pair<T2, U2> &lhs) {
    return rhs < lhs || rhs == lhs;
}

template<class T1, class U1, class T2, class U2>
bool operator>(const Pair<T1, U1> &rhs, const Pair<T2, U2> &lhs) {
    return !(rhs <= lhs);
}

template<class T1, class U1, class T2, class U2>
bool operator>=(const Pair<T1, U1> &rhs, const Pair<T2, U2> &lhs) {
    return !(rhs < lhs);
}