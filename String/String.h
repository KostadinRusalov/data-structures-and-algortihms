#pragma once

#include <iostream>
#include "../ArrayIterator/ArrayIterator.hpp"

/*
 * Small String Optimisation
 * inspired by https://github.com/elliotgoodrich/SSO-23.git
 *
 * a union is used to store a dynamic char array (with both size and capacity)
 * and a static char array with length 24 (it can have at most 23 chars)
 *
 * one bit of the capacity (the 64th to be exact) is used to
 * indicate whether the string is optimised or not
 *
 * there is one problem this way, because it could get overridden by
 * inputting a long enough string, however it is practically impossible
 * as it will need a string with length >= 2^64
 *
 * the size of the static string is stored in the last char
 * by its complement to ssoCapacity meaning that
 * if the size is 23 the last char will be 23 - 23 = 0 or a null terminator
 *
 */
class String {
public:
    typedef char value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef char &reference;
    typedef const char &const_reference;
    typedef char *pointer;
    typedef const char *const_pointer;
    typedef ArrayIterator<value_type> iterator;
    typedef ArrayIterator<const value_type> const_iterator;

private:
    union {
        struct {
            char *data;
            size_t size;
            size_t capacity;
        } dynamicStr;
        char staticStr[sizeof(dynamicStr)];
    } data;

    static const unsigned char ssoCapacity = sizeof(data.dynamicStr) - 1;

    // wrapper functions to call instead of
    // data.dynamicStr.data or data.staticStr
    pointer staticStr();

    const_pointer staticStr() const;

    const_pointer dynamicStr() const;

    pointer &dynamicStr();

    // optimisation logic
    // the length and the capacity are set with these funcs
    bool isOptimised() const;

    void useOptimisation(size_t);

    void useDynamicStr(size_t, size_t);

    // the usual helpers with the Big 4
    void free();

    void copyFrom(const String &);

public:
    explicit String(size_t);

    String();

    String(const char *);

    String(const String &);

    String &operator=(const String &);

    ~String();

    void setData(const char *);

    size_type length() const;

    size_type capacity() const;

    const_pointer c_str() const;

    reference operator[](size_t);

    value_type operator[](size_t) const;

    value_type at(size_t) const;

    reference at(size_t);

    iterator begin();

    const_iterator begin() const;

    const_iterator cbegin() const;

    iterator end();

    const_iterator end() const;

    const_iterator cend() const;

    String substr(size_t, size_t);

    String substr(size_t);

    String &operator+=(const String &);

    String &operator+=(char);

    friend String operator+(const String &, const String &);

    friend std::istream &operator>>(std::istream &, String &);
};

std::ostream &operator<<(std::ostream &, const String &);

String operator+(const String &, const String &);

std::istream &operator>>(std::istream &, String &);

bool operator<(const String &, const String &);

bool operator<=(const String &, const String &);

bool operator>(const String &, const String &);

bool operator>=(const String &, const String &);

bool operator==(const String &, const String &);

bool operator!=(const String &, const String &);