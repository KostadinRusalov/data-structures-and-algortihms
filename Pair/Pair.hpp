#pragma once

#include <utility>

template<class T, class U>
struct Pair {
    typedef T first_type;
    typedef U second_type;

    T first;
    U second;

    Pair() = default;

    Pair(const T &first, const U &second);

    Pair(T &&first, U &&second);

    void swap(Pair<T, U> &with) noexcept;
};

template<class T, class U>
Pair<T, U>::Pair(const T &first, const U &second)
        : first{first}, second{second} {}

template<class T, class U>
Pair<T, U>::Pair(T &&first, U &&second)
        : first{std::move(first)}, second{std::move(second)} {}

template<class T, class U>
void Pair<T, U>::swap(Pair<T, U> &with) noexcept {
    Pair<T, U> temp(*this);
    *this = with;
    with = temp;
}