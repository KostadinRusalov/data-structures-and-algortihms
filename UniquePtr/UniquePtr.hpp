#pragma once

#include <utility>

template<class T>
class UniquePtr {
private:
    T *ptr;
public:
    UniquePtr();

    explicit UniquePtr(T *ptr);

    UniquePtr(const UniquePtr<T> &other) = delete;

    UniquePtr &operator=(const UniquePtr<T> &other) = delete;

    UniquePtr(UniquePtr<T> &&other) noexcept;

    UniquePtr &operator=(UniquePtr<T> &&other) noexcept;

    ~UniquePtr();

    T *release() noexcept;

    void reset(T *p = nullptr);

    T *get() const noexcept;

    explicit operator bool() const noexcept;

    const T &operator*() const;

    T &operator*();

    const T *operator->() const noexcept;

    T *operator->() noexcept;

private:
    void free();

    void moveFrom(UniquePtr<T> &&other);
};

template<class T>
UniquePtr<T> makeUnique(const T &value) {
    T *ptr = new T(value);
    return UniquePtr<T>(ptr);
}

template<class T>
UniquePtr<T>::UniquePtr() : ptr{nullptr} {}

template<class T>
UniquePtr<T>::UniquePtr(T *ptr) : ptr{ptr} {}

template<class T>
UniquePtr<T>::UniquePtr(UniquePtr<T> &&other) noexcept {
    moveFrom(std::move(other));
}

template<class T>
UniquePtr<T> &UniquePtr<T>::operator=(UniquePtr<T> &&other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template<class T>
UniquePtr<T>::~UniquePtr() {
    free();
}

template<class T>
T *UniquePtr<T>::release() noexcept {
    T *temp = ptr;
    ptr = nullptr;
    return temp;
}

template<class T>
void UniquePtr<T>::reset(T *p) {
    if (ptr != p) {
        free();
        ptr = p;
    }
}

template<class T>
T *UniquePtr<T>::get() const noexcept {
    return ptr;
}

template<class T>
UniquePtr<T>::operator bool() const noexcept {
    return ptr != nullptr;
}

template<class T>
const T &UniquePtr<T>::operator*() const {
    return *ptr;
}

template<class T>
T &UniquePtr<T>::operator*() {
    return *ptr;
}

template<class T>
const T *UniquePtr<T>::operator->() const noexcept {
    return ptr;
}

template<class T>
T *UniquePtr<T>::operator->() noexcept {
    return ptr;
}

template<class T>
void UniquePtr<T>::free() {
    delete ptr;
    ptr = nullptr;
}

template<class T>
void UniquePtr<T>::moveFrom(UniquePtr<T> &&other) {
    ptr = other.ptr;
    other.ptr = nullptr;
}