#pragma once

#include <cstdint>
#include <cstddef>
#include <iostream>

class MultiBitset {
public:
    using Bucket = uint32_t;
    using Position = Bucket;
    using value_type = size_t;
    using bits = uint8_t;

    static const short BITS_IN_BYTE;
    static const short BITS_IN_BUCKET;

private:
    bits bitsPerNumber;
    value_type maxNumber;
    value_type numsInBucket;
    value_type maxNumCount;
    value_type bucketsCount;
    Bucket *buckets;

public:
    MultiBitset();

    MultiBitset(value_type n, bits k);

    MultiBitset(const MultiBitset &other);

    MultiBitset(MultiBitset &&other) noexcept;

    MultiBitset &operator=(const MultiBitset &other);

    MultiBitset &operator=(MultiBitset &&other) noexcept;

    ~MultiBitset();

    value_type getMaxNumber() const;

    void insert(value_type num);

    void remove(value_type num);

    value_type count(value_type num) const;

    friend MultiBitset intersection(const MultiBitset &lhs, const MultiBitset &rhs);

    friend MultiBitset difference(const MultiBitset &lhs, const MultiBitset &rhs);

    friend MultiBitset complement(const MultiBitset &multiBitset);

private:
    void free();

    void copyFrom(const MultiBitset &other);

    void moveFrom(MultiBitset &&other);

    void replace(value_type num, value_type count);

    value_type firstBitIdx(value_type num) const;

    value_type lastBitIdx(value_type num) const;

    value_type bucketCount(value_type num) const;

    value_type bucket(value_type num) const;

    std::pair<bits, bits> splitBits(value_type bucket) const;

    bool isSplit(value_type num) const;

    bits shift(value_type num) const;

    Position position(value_type num) const;

    static bits leftBitsPosition(bits remainder);

    static bits rightBitsShift(bits remainder);
};

std::ostream &operator<<(std::ostream &os, const MultiBitset &multiset);

MultiBitset intersection(const MultiBitset &lhs, const MultiBitset &rhs);

MultiBitset difference(const MultiBitset &lhs, const MultiBitset &rhs);

MultiBitset complement(const MultiBitset &multiBitset);
