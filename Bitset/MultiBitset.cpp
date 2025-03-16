#include "MultiBitset.h"
#include <utility>

constexpr short DEFAULT_N = 16;
constexpr short DEFAULT_K = 2;

const short MultiBitset::BITS_IN_BYTE = 8;
const short MultiBitset::BITS_IN_BUCKET = sizeof(Bucket) * MultiBitset::BITS_IN_BYTE;

MultiBitset::MultiBitset() : MultiBitset(DEFAULT_N, DEFAULT_K) {}

MultiBitset::MultiBitset(MultiBitset::value_type n, MultiBitset::bits k)
        : maxNumber(n),
          bitsPerNumber(k),
          maxNumCount((1 << k) - 1),
          bucketsCount(bucketCount(n)),
          numsInBucket(BITS_IN_BUCKET / k),
          buckets(new Bucket[bucketsCount]{}) {
}

MultiBitset::MultiBitset(const MultiBitset &other) {
    copyFrom(other);
}

MultiBitset::MultiBitset(MultiBitset &&other) noexcept {
    moveFrom(std::move(other));
}

MultiBitset &MultiBitset::operator=(const MultiBitset &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

MultiBitset &MultiBitset::operator=(MultiBitset &&other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

MultiBitset::~MultiBitset() {
    free();
}

MultiBitset::value_type MultiBitset::getMaxNumber() const {
    return maxNumber;
}

void MultiBitset::insert(MultiBitset::value_type num) {
    value_type numCount = count(num);
    if (num > maxNumber || numCount == maxNumCount) {
        return;
    }

    numCount++;
    replace(num, numCount);
}

void MultiBitset::remove(MultiBitset::value_type num) {
    value_type numCount = count(num);
    if (numCount == 0) {
        return;
    }

    numCount--;
    replace(num, numCount);
}

MultiBitset::value_type MultiBitset::count(MultiBitset::value_type num) const {
    if (num > maxNumber) {
        return 0;
    }

    if (!isSplit(num)) {
        return (buckets[bucket(num)] & position(num)) >> shift(num);
    }

    value_type bucketIdx = bucket(num);
    auto [leftBits, rightBits] = splitBits(bucketIdx);

    value_type count = buckets[bucketIdx] & leftBitsPosition(leftBits);
    count <<= rightBits;
    count |= buckets[bucketIdx + 1] >> rightBitsShift(rightBits);
    return count;
}

void MultiBitset::replace(MultiBitset::value_type num, MultiBitset::value_type count) {
    value_type bucketIdx = bucket(num);
    if (!isSplit(num)) {
        buckets[bucketIdx] &= ~position(num);
        buckets[bucketIdx] |= (count << shift(num));
        return;
    }

    auto [leftBits, rightBits] = splitBits(bucketIdx);
    bits rightShift = rightBitsShift(rightBits);

    buckets[bucketIdx] &= ~leftBitsPosition(leftBits);
    buckets[bucketIdx] |= (count >> rightBits);

    buckets[bucketIdx + 1] &= ~(leftBitsPosition(rightBits) << rightShift);
    buckets[bucketIdx + 1] |= (count << rightShift);
}

MultiBitset::value_type MultiBitset::bucketCount(MultiBitset::value_type num) const {
    return bucket(num) + isSplit(num) + 1;
}

MultiBitset::value_type MultiBitset::bucket(MultiBitset::value_type num) const {
    return firstBitIdx(num) / BITS_IN_BUCKET;
}

MultiBitset::value_type MultiBitset::firstBitIdx(MultiBitset::value_type num) const {
    return num * bitsPerNumber;
}

MultiBitset::value_type MultiBitset::lastBitIdx(MultiBitset::value_type num) const {
    return (num + 1) * bitsPerNumber - 1;
}

std::pair<MultiBitset::bits, MultiBitset::bits> MultiBitset::splitBits(value_type bucket) const {
    bits leftBits = (bucket + 1) * BITS_IN_BUCKET % bitsPerNumber;
    bits rightBits = bitsPerNumber - leftBits;
    return {leftBits, rightBits};
}

bool MultiBitset::isSplit(value_type num) const {
    return firstBitIdx(num) / BITS_IN_BUCKET != lastBitIdx(num) / BITS_IN_BUCKET;
}

MultiBitset::bits MultiBitset::shift(MultiBitset::value_type num) const {
    return BITS_IN_BUCKET - 1 - lastBitIdx(num) % BITS_IN_BUCKET;
}

MultiBitset::Position MultiBitset::position(MultiBitset::value_type num) const {
    return maxNumCount << shift(num);
}

MultiBitset::bits MultiBitset::leftBitsPosition(MultiBitset::bits leftBits) {
    return (1 << leftBits) - 1;
}

MultiBitset::bits MultiBitset::rightBitsShift(MultiBitset::bits rightBits) {
    return BITS_IN_BUCKET - rightBits;
}

void MultiBitset::free() {
    delete[] buckets;
    buckets = nullptr;
}

void MultiBitset::copyFrom(const MultiBitset &other) {
    maxNumber = other.maxNumber;
    numsInBucket = other.numsInBucket;
    maxNumCount = other.maxNumCount;
    bucketsCount = other.bucketsCount;
    bitsPerNumber = other.bitsPerNumber;

    buckets = new Bucket[bucketsCount];
    for (value_type i = 0; i < bucketsCount; ++i) {
        buckets[i] = other.buckets[i];
    }
}

void MultiBitset::moveFrom(MultiBitset &&other) {
    maxNumber = other.maxNumber;
    numsInBucket = other.numsInBucket;
    maxNumCount = other.maxNumCount;
    bucketsCount = other.bucketsCount;
    bitsPerNumber = other.bitsPerNumber;

    buckets = other.buckets;
    other.buckets = nullptr;
}

std::ostream &operator<<(std::ostream &os, const MultiBitset &multiset) {
    for (int i = 0; i < multiset.getMaxNumber(); ++i) {
        MultiBitset::value_type countNum = multiset.count(i);
        while (countNum--) {
            os << i << ' ';
        }
    }

    return os;
}

MultiBitset intersection(const MultiBitset &lhs, const MultiBitset &rhs) {
    MultiBitset::value_type n = std::min(lhs.maxNumber, rhs.maxNumber);
    MultiBitset::bits k = std::min(lhs.bitsPerNumber, rhs.bitsPerNumber);
    MultiBitset intersection(n, k);

    for (MultiBitset::value_type i = 0; i <= n; ++i) {
        intersection.replace(i, std::min(lhs.count(i), rhs.count(i)));
    }

    return intersection;
}


MultiBitset difference(const MultiBitset &lhs, const MultiBitset &rhs) {
    MultiBitset difference(lhs.maxNumber, lhs.bitsPerNumber);

    for (MultiBitset::value_type i = 0; i <= lhs.maxNumber; ++i) {
        difference.replace(i, std::max(0, (int) lhs.count(i) - (int) rhs.count(i)));
    }

    return difference;
}


MultiBitset complement(const MultiBitset &multiBitset) {
    MultiBitset complement(multiBitset.maxNumber, multiBitset.bitsPerNumber);
    MultiBitset::value_type max = multiBitset.maxNumCount;

    for (MultiBitset::value_type i = 0; i <= multiBitset.maxNumber; ++i) {
        complement.replace(i, max - multiBitset.count(i));
    }

    return complement;
}

