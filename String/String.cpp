#include <cstring>
#include "String.h"
#include "BitManipulation.h"

String::String(size_t capacity) : data{} {
    if (capacity > ssoCapacity) {
        dynamicStr() = new char[capacity + 1]{};
        useDynamicStr(0, capacity + 1);
    } else {
        useOptimisation(0);
    }
}

String::String() : String("") {}

String::String(const char *str) : data{} {
    setData(str);
}

String::String(const String &other) : data{} {
    copyFrom(other);
}

String &String::operator=(const String &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

String::~String() {
    free();
}

// the wrappers
char *String::staticStr() {
    return data.staticStr;
}

const char *String::staticStr() const {
    return data.staticStr;
}

char *&String::dynamicStr() {
    return data.dynamicStr.data;
}

const char *String::dynamicStr() const {
    return data.dynamicStr.data;
}

void String::setData(const char *str) {
    if (!str) {
        staticStr()[0] = '\0';
        useOptimisation(0);
        return;
    }
    size_t len = strlen(str);

    if (len <= ssoCapacity) {
        strcpy(staticStr(), str);
        useOptimisation(len);
        return;
    }

    if (len <= capacity()) {
        strcpy(dynamicStr(), str);
        useDynamicStr(len, capacity() + 1);
        return;
    }

    free();
    dynamicStr() = new char[len + 1];
    strcpy(dynamicStr(), str);
    useDynamicStr(len, len + ssoCapacity + 1);
}

void String::useOptimisation(size_t size) {
    staticStr()[ssoCapacity] = (char) (ssoCapacity - size);
    BitManipulation::clearLeftmostBit(staticStr()[ssoCapacity]);
}

void String::useDynamicStr(size_t size, size_t capacity) {
    data.dynamicStr.size = size;
    data.dynamicStr.capacity = capacity;
    BitManipulation::setLeftmostBit(staticStr()[ssoCapacity]);
}

bool String::isOptimised() const {
    return !BitManipulation::leftmostBitIsSet(staticStr()[ssoCapacity]);
}

void String::free() {
    if (!isOptimised()) {
        delete[] dynamicStr();
        dynamicStr() = nullptr;
    }
}

void String::copyFrom(const String &other) {
    if (other.isOptimised()) {
        strcpy(staticStr(), other.c_str());
        useOptimisation(other.length());
    } else {
        dynamicStr() = new char[other.capacity() + 1];
        strcpy(dynamicStr(), other.c_str());
        useDynamicStr(other.length(), other.capacity() + 1);
    }
}

size_t String::length() const {
    if (isOptimised()) {
        return ssoCapacity - staticStr()[ssoCapacity];
    }
    return data.dynamicStr.size;
}

size_t String::capacity() const {
    if (isOptimised()) {
        return ssoCapacity;
    }
    return BitManipulation::ignoreLeftmostBit(data.dynamicStr.capacity) - 1;
}

const char *String::c_str() const {
    return isOptimised() ? staticStr() : dynamicStr();
}

char &String::operator[](size_t idx) {
    return isOptimised() ? staticStr()[idx] : dynamicStr()[idx];
}

char String::operator[](size_t idx) const {
    return isOptimised() ? staticStr()[idx] : dynamicStr()[idx];
}

char String::at(size_t idx) const {
    if (idx >= length()) {
        throw std::out_of_range("Index is out of range!");
    }
    return operator[](idx);
}

char &String::at(size_t idx) {
    if (idx >= length()) {
        throw std::out_of_range("Index is out of range!");
    }
    return operator[](idx);
}

String String::substr(size_t from, size_t size) {
    if (from > length()) {
        throw std::out_of_range("Index is out of range!");
    }

    if (from + size - 1 >= length()) {
        size = length() - from;
    }

    String res(size);

    char *resStr = res.isOptimised() ? res.staticStr() : res.dynamicStr();

    for (size_t i = 0; i < size; ++i) {
        resStr[i] = operator[](from + i);
    }

    return res;
}

String String::substr(size_t from) {
    return substr(from, length() - from);
}

std::ostream &operator<<(std::ostream &os, const String &str) {
    return os << str.c_str();
}

std::istream &operator>>(std::istream &is, String &str) {
    char buff[1024];
    is >> buff;

    str.setData(buff);

    return is;
}


String &String::operator+=(const String &other) {
    size_t newLen = length() + other.length();

    if (isOptimised() && newLen <= ssoCapacity) {
        strcat(staticStr(), other.c_str());
        useOptimisation(newLen);
        return *this;
    }

    if (newLen <= capacity()) {
        strcat(dynamicStr(), other.c_str());
        useDynamicStr(newLen, capacity() + 1);
        return *this;
    }

    char *newData = new char[newLen + ssoCapacity + 1]{};

    strcat(newData, c_str());
    strcat(newData, other.c_str());

    free();
    dynamicStr() = newData;
    useDynamicStr(newLen, newLen + ssoCapacity + 1);
    return *this;
}

String &String::operator+=(char c) {
    size_t newLen = length() + 1;
    if (isOptimised() && newLen <= ssoCapacity) {
        staticStr()[newLen - 1] = c;
        staticStr()[newLen] = '\0';
        useOptimisation(newLen);
        return *this;
    }

    if (newLen <= capacity()) {
        dynamicStr()[newLen - 1] = c;
        dynamicStr()[newLen] = '\0';
        useDynamicStr(newLen, capacity() + 1);
        return *this;
    }

    char *newData = new char[newLen + ssoCapacity + 1];
    strcat(newData, c_str());
    newData[newLen - 1] = c;
    newData[newLen] = '\0';

    free();
    dynamicStr() = newData;
    useDynamicStr(newLen, newLen + ssoCapacity + 1);
    return *this;
}

String operator+(const String &lhs, const String &rhs) {
    size_t len = lhs.length() + rhs.length();

    if (len <= String::ssoCapacity) {
        String res(len);
        strcat(res.staticStr(), lhs.c_str());
        strcat(res.staticStr(), rhs.c_str());
        res.useOptimisation(len);
        return res;
    }
    size_t capacity = lhs.capacity() + rhs.capacity();
    String res(capacity);

    strcat(res.dynamicStr(), lhs.c_str());
    strcat(res.dynamicStr(), rhs.c_str());
    res.useDynamicStr(len, capacity + 1);
    return res;
}

bool operator<(const String &lhs, const String &rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const String &lhs, const String &rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>(const String &lhs, const String &rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const String &lhs, const String &rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator==(const String &lhs, const String &rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String &lhs, const String &rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}