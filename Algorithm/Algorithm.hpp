#pragma once

namespace kstd {
    template<class InputIt, class T>
    InputIt find(InputIt first, InputIt last, const T &value) {
        for (auto it = first; it != last; ++it) {
            if (value == *it) {
                return it;
            }
        }
        return last;
    }

    template<class InputIt, class UnitaryPredicate>
    InputIt findIf(InputIt first, InputIt last, UnitaryPredicate p) {
        for (auto it = first; it != last; ++it) {
            if (p(*it)) {
                return it;
            }
        }
        return last;
    }

    template<class InputIt, class UnitaryPredicate>
    bool allOf(InputIt first, InputIt last, UnitaryPredicate p) {
        for (auto it = first; it != last; ++it) {
            if (!p(*it)) {
                return false;
            }
        }
        return true;
    }

    template<class InputIt, class UnitaryPredicate>
    bool anyOf(InputIt first, InputIt last, UnitaryPredicate p) {
        for (auto it = first; it != last; ++it) {
            if (p(*it)) {
                return true;
            }
        }
        return false;
    }


    template<class T>
    void swap(T &rhs, T &lhs) {
        T copy(rhs);
        rhs = lhs;
        lhs = copy;
    }

    template<class InputIt, class OutputIt, class UnaryOperation>
    OutputIt transform(InputIt first, InputIt last, OutputIt out, UnaryOperation op) {
        for (auto it = first; it != last; ++it, ++out) {
            *out = op(*it);
        }
        return out;
    }
}