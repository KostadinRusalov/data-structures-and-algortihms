#pragma once

#include <cstddef>
#include <cstdint>

class Bitset {
public:
    typedef uint32_t Bucket;
    typedef size_t size_type;
    typedef unsigned value_type;
    typedef size_type position_idx;

    friend class BitsetIterator;

    static const unsigned short ONE_BYTE = 8;
    static const size_type BUCKET_SIZE = ONE_BYTE * sizeof(Bucket);
private:
    Bucket *data;
    value_type max;
    size_type count;

public:
    explicit Bitset(value_type max);

    Bitset(const Bitset &other);

    Bitset(Bitset &&other) noexcept;

    Bitset &operator=(const Bitset &other);

    Bitset &operator=(Bitset &&other) noexcept;

    ~Bitset();

    // capacity
    bool empty() const;

    size_type size() const;

    value_type capacity() const;

    // modifiers
    void clear();

    void add(value_type num);

    void remove(value_type num);

    // element access
    bool contains(value_type num) const;

private:
    void free();

    void copyFrom(const Bitset &other);

    void moveFrom(Bitset &&other);

    void resize(value_type newMax);

    size_type bucketCount() const;

    size_type bucket(value_type num) const;

    position_idx position(value_type num) const;
};