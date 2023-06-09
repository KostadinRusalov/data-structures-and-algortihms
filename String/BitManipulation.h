#pragma once

#include <cstddef>

namespace BitManipulation {
    const char shift = 7;
    const char mask = (char) (1 << shift);
    const size_t size_tMask = 1ul << 63;

    void clearLeftmostBit(char &);

    void setLeftmostBit(char &);

    bool leftmostBitIsSet(char);

    size_t ignoreLeftmostBit(size_t);
}