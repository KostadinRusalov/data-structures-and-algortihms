#pragma once

#include <cstddef>
#include <utility>
#include <stdexcept>

template<class T>
class Queue {
private:
    T *data;
    size_t size_;
    size_t capacity;
    size_t put;
    size_t get;

    static const short INITIAL_CAPACITY = 4;
public:
    Queue();

    Queue(const Queue<T> &other);

    Queue(Queue<T> &&other) noexcept;

    Queue &operator=(const Queue<T> &other);

    Queue &operator=(Queue<T> &&other) noexcept;

    ~Queue();

    bool empty() const;

    size_t size() const;

    void push(const T &element);

    void push(T &&element);

    const T &peek() const;

    void pop();

private:
    void free();

    void copyFrom(const Queue<T> &other);

    void moveFrom(Queue<T> &&other);

    void resize(size_t newCapacity);

    static void next(size_t &idx, size_t max);
};

template<class T>
Queue<T>::Queue()
        : size_{0}, capacity{INITIAL_CAPACITY}, get{0}, put{0} {
    data = new T[capacity];
}

template<class T>
Queue<T>::Queue(const Queue<T> &other) {
    copyFrom(other);
}

template<class T>
Queue<T>::Queue(Queue<T> &&other) noexcept {
    moveFrom(std::move(other));
}

template<class T>
Queue<T> &Queue<T>::operator=(const Queue<T> &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template<class T>
Queue<T> &Queue<T>::operator=(Queue<T> &&other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template<class T>
Queue<T>::~Queue() {
    free();
}

template<class T>
bool Queue<T>::empty() const {
    return size_ == 0;
}

template<class T>
size_t Queue<T>::size() const {
    return size_;
}

template<class T>
void Queue<T>::push(const T &element) {
    if (size_ == capacity) {
        resize(2 * capacity);
    }
    size_++;
    data[put] = element;
    next(put, capacity);
}

template<class T>
void Queue<T>::push(T &&element) {
    if (size_ == capacity) {
        resize(2 * capacity);
    }
    size_++;
    data[put] = std::move(element);
    next(put, capacity);
}

template<class T>
const T &Queue<T>::peek() const {
    if (empty()) {
        throw std::logic_error("queue is empty");
    }
    return data[get];
}

template<class T>
void Queue<T>::pop() {
    if (empty()) {
        throw std::logic_error("queue is empty");
    }
    size_--;
    next(get, capacity);

    if (capacity > 4 * size_) {
        resize(capacity / 2);
    }
}

template<class T>
void Queue<T>::free() {
    delete[] data;
    data = nullptr;
}

template<class T>
void Queue<T>::copyFrom(const Queue<T> &other) {
    size_ = other.size_;
    capacity = other.capacity;
    get = other.get;
    put = other.put;

    data = new T[capacity];

    for (size_t i = 0; i < size_; ++i) {
        data[i] = other.data[i];
    }
}

template<class T>
void Queue<T>::moveFrom(Queue<T> &&other) {
    size_ = other.size_;
    capacity = other.capacity;
    get = other.get;
    put = other.put;

    data = other.data;
    other.data = nullptr;
}

template<class T>
void Queue<T>::resize(size_t newCapacity) {
    capacity = newCapacity;
    T *temp = new T[capacity];

    for (size_t i = 0; i < size_; ++i) {
        temp[i] = data[get];
        next(get, capacity);
    }

    free();
    data = temp;
    get = 0;
    put = size_;
}

template<class T>
void Queue<T>::next(size_t &idx, size_t max) {
    idx = (idx == max - 1) ? 0 : ++idx;
}