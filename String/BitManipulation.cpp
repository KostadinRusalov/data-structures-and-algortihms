#include "BitManipulation.h"

void BitManipulation::clearLeftmostBit(char &var) {
    var &= ~mask;
}

void BitManipulation::setLeftmostBit(char &var) {
    var |= mask;
}

bool BitManipulation::leftmostBitIsSet(char var) {
    return (unsigned char) var >> shift;
}

size_t BitManipulation::ignoreLeftmostBit(size_t var) {
    return var & ~size_tMask;
}
