#pragma once

#include "../String/String.h"

class StringView {
public:
    typedef char value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef char &reference;
    typedef const char &const_reference;
    typedef char *pointer;
    typedef const char *const_pointer;
    typedef String::const_iterator iterator;
    typedef String::const_iterator const_iterator;

private:
    const_pointer begin_;
    const_pointer end_;

public:
    StringView() = default;

    StringView(const_pointer begin, const_pointer end);

    StringView(const_pointer begin, size_type count);

    StringView(const_pointer c_str);

    StringView(const String &str);

    StringView(const String &str, size_type count);

    const_iterator begin() const;

    const_iterator cbegin() const;

    const_iterator end() const;

    const_iterator cend() const;

    const_reference operator[](size_type pos) const;

    const_reference at(size_type pos) const;

    const_reference front() const;

    const_reference back() const;

    const_pointer data() const;

    size_type size() const;

    size_type length() const;

    bool empty() const;

    StringView substr(size_type pos) const;

    StringView substr(size_type pos, size_type count) const;

};

std::ostream &operator<<(std::ostream &os, const StringView &strView);

StringView operator ""sv(const char *str);
