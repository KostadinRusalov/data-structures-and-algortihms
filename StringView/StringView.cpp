#include "StringView.h"
#include <cstring>

StringView::StringView(StringView::const_pointer begin, StringView::const_pointer end)
        : begin_{begin}, end_{end} {}

StringView::StringView(const_pointer begin, size_type count) :
        begin_{begin}, end_{begin_ + count} {}

StringView::StringView(StringView::const_pointer c_str)
        : StringView(c_str, strlen(c_str)) {}

StringView::StringView(const String &str)
        : StringView(str.c_str(), str.c_str() + str.length()) {}

StringView::StringView(const String &str, size_type count)
        : StringView(str.c_str(), count) {}

StringView::const_iterator StringView::begin() const {
    return cbegin();
}

StringView::const_iterator StringView::cbegin() const {
    return {begin_};
}

StringView::const_iterator StringView::end() const {
    return cend();
}

StringView::const_iterator StringView::cend() const {
    return {end_};
}

const char &StringView::operator[](StringView::size_type pos) const {
    return *(begin_ + pos);
}

const char &StringView::at(StringView::size_type pos) const {
    if (pos > size()) {
        throw std::out_of_range("index out of range");
    }
    return operator[](pos);
}

const char &StringView::front() const {
    return *begin_;
}

const char &StringView::back() const {
    return *(end_ - 1);
}

StringView::const_pointer StringView::data() const {
    return begin_;
}

StringView::size_type StringView::size() const {
    return end_ - begin_;
}

StringView::size_type StringView::length() const {
    return size();
}

bool StringView::empty() const {
    return size() == 0;
}

StringView StringView::substr(StringView::size_type pos) const {
    return substr(pos, size());
}

StringView StringView::substr(StringView::size_type pos, StringView::size_type count) const {
    if (pos > size()) {
        throw std::out_of_range("index out of range");
    }
    size_type bound = (count < size() - pos) ? count : size() - pos;
    return {begin_ + pos, begin_ + pos + bound};
}

std::ostream &operator<<(std::ostream &os, const StringView &strView) {
    for (auto it = strView.begin(); it != strView.end(); ++it) {
        os << *it;
    }
    return os;
}

StringView operator ""sv(const char *str) {
    return {str};
}
