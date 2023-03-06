/**============================================================================
Name        : Iterator.cpp
Created on  : 28.08.2022
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Iterator pattern/idiom
============================================================================**/

#include "Iterator.h"

#include <iostream>

namespace Iterator
{
    class Stack
    {
        int items[10] {};
        int sp {-1};

    public:
        friend class StackIter;

        void push(int in) {
            items[++sp] = in;
        }

        int pop()
        {
            return items[sp--];
        }

        [[nodiscard]]
        inline bool isEmpty() const noexcept {
            return (sp ==  - 1);
        }

        [[nodiscard]]
        class StackIter *createIterator() const;
    };

    class StackIter
    {
        const Stack& stk;
        int index {0};

    public:
        explicit StackIter(const Stack& s): stk {s} {
        }

        void first() {
            index = 0;
        }

        void next() {
            index++;
        }

        [[nodiscard]]
        inline bool isDone() const {
            return index == stk.sp + 1;
        }

        int currentItem() {
            return stk.items[index];
        }
    };

    StackIter *Stack::createIterator()const
    {
        return new StackIter(*this);
    }

    bool operator == (const Stack &l, const Stack &r)
    {
        StackIter *itl = l.createIterator(), *itr = r.createIterator();

        for (itl->first(), itr->first(); !itl->isDone(); itl->next(), itr->next()) {
            if (itl->currentItem() != itr->currentItem()) {
                break;
            }
        }

        const bool ans { itl->isDone() && itr->isDone() };

        delete itl;
        delete itr;
        return ans;
    }
};

void RangeIteratorTests();

void Iterator::Test()
{
    RangeIteratorTests();

    /*
    Stack s1;
    for (int i = 1; i < 5; i++)
        s1.push(i);

    Stack s2(s1), s3(s1), s4(s1), s5(s1);

    s3.pop();
    s5.pop();
    s4.push(2);
    s5.push(9);

    std::cout << "1 == 2 is " << (s1 == s2) << std::endl;
    std::cout << "1 == 3 is " << (s1 == s3) << std::endl;
    std::cout << "1 == 4 is " << (s1 == s4) << std::endl;
    std::cout << "1 == 5 is " << (s1 == s5) << std::endl;
    */
};

/*
1 == 2 is 1
1 == 3 is 0
1 == 4 is 0
1 == 5 is 0
*/