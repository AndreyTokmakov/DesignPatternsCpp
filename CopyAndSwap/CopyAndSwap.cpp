//============================================================================
// Name        : CopyAndSwap.h
// Created on  : 05.07.22.
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : C++ CopyAndSwap
//============================================================================

#include "CopyAndSwap.h"

#include <iostream>
#include <memory>
#include <algorithm>
#include <numeric>

namespace CopyAndSwap {

    template<typename T = int>
    class Array {
    private:
        using value_type = T;
        using size_type = size_t;

        static_assert(!std::is_same_v<value_type, void>,
                      "Type of the value shall not be void");

        value_type *data{nullptr};
        size_type size{0};

    public:
        explicit Array(size_type s) : data{new value_type[s]}, size{s} {
        }

        value_type &operator[](size_type idx) {
            return data[idx];
        }

        const value_type &operator[](size_type idx) const {
            return data[idx];
        }

        inline value_type *Data() noexcept {
            return data;
        }

        [[nodiscard]]
        inline size_type Size() const noexcept {
            return size;
        }

        Array(const Array &other) :
                data {new value_type[other.size]}, size{other.size} {
            std::copy_n(other.data, size, data);
        }


        // INFO: Idia
        Array &operator=(const Array &other) {
            Array localCopy(other);
            // swap(localCopy);
            Array::swap(localCopy, *this);
            return *this;
        }

#if 0
        Array(Array &&other) noexcept:
                data{std::exchange(other.data, nullptr)},
                size{std::exchange(other.size, 0)} {
        }

        Array &operator=(Array &&other) noexcept {
            if (this != &other) {
                delete[] data;
                data = std::exchange(other.data, nullptr);
                size = std::exchange(other.size, 0);
            }
            return *this;
        }
#endif

        /*
        [[nodiscard]]
        inline T begin() const noexcept {
            return data[0];
        }

        [[nodiscard]]
        inline T end() const noexcept {
            return data[size - 1];
        }
        */

        void swap(Array &other) noexcept {
            std::swap(this->data, other.data);
            std::swap(this->size, other.size);
        }

        static void swap(Array &first, Array &second) noexcept {
            std::swap(first.data, second.data);
            std::swap(first.size, second.size);
        }

        ~Array() {
            delete[] data;
            data = nullptr;
            size = 0;
        }
    };
}

namespace CopyAndSwap::Tests {

    void Test() {
        Array<uint32_t> numbers {3};
        std::iota(numbers.Data(), numbers.Data() + numbers.Size(), 1);

        for (uint32_t i = 0; i < numbers.Size(); ++i) {
            std::cout << numbers[i] << std::endl;
        }

        std::cout << "--------------------------------------------\n";

        Array<uint32_t> numbers1 (numbers);
        for (uint32_t i = 0; i < numbers1.Size(); ++i) {
            std::cout << numbers1[i] << std::endl;
        }

        std::cout << "--------------------------------------------\n";

        Array<uint32_t> numbers2(3);
        numbers2 = numbers1;
        for (uint32_t i = 0; i < numbers2.Size(); ++i) {
            std::cout << numbers2[i] << std::endl;
        }

        std::cout << "--------------------------------------------\n";

        numbers2 = numbers2;
        for (uint32_t i = 0; i < numbers2.Size(); ++i) {
            std::cout << numbers2[i] << std::endl;
        }
    }
}

/**
The copy-and-swap idiom is an idiom of the C++ programming language
that allows you to develop exception—resistant assignment operators.

The idiom is based on the idiom "RAII".

The idiom assumes the implementation of the following member functions of the class:
- copy constructor;
- assignment operator;
- a swap method that does not throw an exception and accepts a reference to an object of the class.
**/
void CopyAndSwap::TEST_ALL()
{
    Tests::Test();
}

