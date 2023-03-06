//============================================================================
// Name        : TagDispatching.h
// Created on  : 23.07.2022
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : TagDispatching
//============================================================================

#include "TagDispatching.h"

#include <iostream>
#include <vector>
#include <list>
#include <forward_list>

namespace TagDispatching
{
    template <typename InputIterator, typename Distance>
    void advance_impl(InputIterator& iter, Distance n, std::input_iterator_tag) {
        std::cout << "InputIterator used" << '\n';
        if (n >= 0) {
            while (n--)
                ++iter;
        }
    }

    template <typename BidirectionalIterator, typename Distance>
    void advance_impl(BidirectionalIterator& iter, Distance n, std::bidirectional_iterator_tag) {
        std::cout << "BidirectionalIterator used" << '\n';
        if (n >= 0)
            while (n--)
                ++iter;
        else
            while (n++)
                --iter;
    }

    template <typename RandomAccessIterator, typename Distance>
    void advance_impl(RandomAccessIterator& iter, Distance n, std::random_access_iterator_tag) {
        std::cout << "RandomAccessIterator used" << '\n';
        iter += n;
    }

    template <typename InputIterator, typename Distance>
    void advance_(InputIterator& i, Distance n) {
        typename std::iterator_traits<InputIterator>::iterator_category category;
        advance_impl(i, n, category);
    }


    void test_1(){
        std::vector<int> myVec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto myVecIt = myVec.begin();
        std::cout << "\n*myVecIt: " << *myVecIt << '\n';
        advance_(myVecIt, 5);
        std::cout << "*myVecIt: " << *myVecIt << '\n';

        std::list<int> myList{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto myListIt = myList.begin();
        std::cout << "\n*myListIt: " << *myListIt << '\n';
        advance_(myListIt, 5);
        std::cout << "*myListIt: " << *myListIt << '\n';

        std::forward_list<int> myForwardList{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // (3)
        auto myForwardListIt = myForwardList.begin();
        std::cout << "\n*myForwardListIt: " << *myForwardListIt << '\n';
        advance_(myForwardListIt, 5);
        std::cout << "*myForwardListIt: " << *myForwardListIt << '\n';
    }
}


void TagDispatching::Test() {
    test_1();
}