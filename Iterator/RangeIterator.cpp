/**============================================================================
Name        : RangeIterator.cpp
Created on  : 5.01.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : RangeIterator pattern/idiom
============================================================================**/

#include "Iterator.h"

#include <iostream>

namespace Iterator::RangeIterator
{
    struct num_iterator {
        int i;

        explicit num_iterator(int position = 0) : i{position} {
        }

        num_iterator& operator++() noexcept {
            ++i;
            return *this;
        }

        int operator*() const noexcept { return i;
        }

        bool operator!=(const num_iterator &other) const noexcept {
            return i != other.i;
        }
    };


    class num_range {
        int a {};
        int b {};

    public:
        num_range(int from, int to) : a {from}, b {to} {
        }

        [[nodiscard]]
        inline num_iterator begin() const noexcept {
            return num_iterator {a};
        }

        [[nodiscard]]
        inline num_iterator end() const noexcept {
            return num_iterator {b};
        }
    };

};

void RangeIteratorTests()
{
    using namespace Iterator::RangeIterator;

    for (int i : num_range{100, 110}) {
        std::cout << i << ", ";
    }
};
