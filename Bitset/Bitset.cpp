#include "Bitset.h"
#include <utility>

Bitset::Bitset(value_type max)
        : max{max}, count{0} {
    data = new Bucket[bucketCount()]{};
}

Bitset::Bitset(const Bitset &other) {
    copyFrom(other);
}

Bitset::Bitset(Bitset &&other) noexcept {
    moveFrom(std::move(other));
}

Bitset &Bitset::operator=(const Bitset &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Bitset &Bitset::operator=(Bitset &&other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Bitset::~Bitset() {
    free();
}

bool Bitset::empty() const {
    for (size_type b = 0; b < bucketCount(); ++b) {
        if (data[b] != 0) {
            return false;
        }
    }
    return true;
}

Bitset::size_type Bitset::size() const {
    return count;
}

Bitset::value_type Bitset::capacity() const {
    return max;
}

void Bitset::clear() {
    for (size_type b = 0; b < bucketCount(); ++b) {
        data[b] = 0;
    }
}

void Bitset::add(Bitset::value_type num) {
    if (num >= max) {
        resize(num + 1);
    }
    if (!contains(num)) {
        count++;
        data[bucket(num)] |= position(num);
    }
}

void Bitset::remove(Bitset::value_type num) {
    if (num >= max) {
        return;
    }
    if (contains(num)) {
        count--;
        data[bucket(num)] &= ~position(num);
    }
}

bool Bitset::contains(Bitset::value_type num) const {
    if (num >= max) {
        return false;
    }

    return data[bucket(num)] & position(num);
}

void Bitset::free() {
    delete[] data;
    data = nullptr;
}

void Bitset::copyFrom(const Bitset &other) {
    max = other.max;
    count = other.max;

    size_type buckets = bucketCount();
    data = new Bucket[buckets];
    for (size_type b = 0; b < buckets; ++b) {
        data[b] = other.data[b];
    }
}

void Bitset::moveFrom(Bitset &&other) {
    max = other.max;
    count = other.max;

    data = other.data;
    other.data = nullptr;
}

void Bitset::resize(Bitset::value_type newMax) {
    if (bucket(newMax) <= bucketCount()) {
        max = newMax;
        return;
    }

    size_type oldCount = bucketCount();
    max = newMax;
    auto temp = new Bucket[bucketCount()]{};
    for (size_type b = 0; b < oldCount; ++b) {
        temp[b] = data[b];
    }

    free();
    data = temp;
}

Bitset::size_type Bitset::bucketCount() const {
    return 1 + max / BUCKET_SIZE;
}

Bitset::size_type Bitset::bucket(Bitset::value_type num) const {
    return num / BUCKET_SIZE;
}

Bitset::position_idx Bitset::position(Bitset::value_type num) const {
    size_type shift = (BUCKET_SIZE - 1) - num % BUCKET_SIZE;
    return 1 << shift;
}





