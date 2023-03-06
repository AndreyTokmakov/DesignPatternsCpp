/**============================================================================
Name        : ObjectCounter.cpp
Created on  : 05.01.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : ObjectCounter src
============================================================================**/

#include "ObjectCounter.h"

#include <iostream>

namespace CRTP::ObjectCounter
{
    template<typename CountedType>
    class ObjectCounter
    {
    private:
        inline static std::size_t count { 0 };

    protected:
        ObjectCounter() {
            ++count;
        }

        ObjectCounter(const ObjectCounter<CountedType>&) {
            ++count;
        }

        ObjectCounter(ObjectCounter<CountedType> &&) noexcept {
            ++count;
        }

        ~ObjectCounter() {
            --count;
        }

    public:
        static std::size_t live() {
            return count;
        }
    };

    template<typename CharT>
    class MyString : public ObjectCounter<MyString<CharT>> {
    };

}

void CRTP::ObjectCounter::Test()
{
    MyString<char> s1, s2;
    MyString<wchar_t> ws;

    std::cout << "num of MyString<char>: "<< MyString<char>::live() << std::endl;
    std::cout << "num of MyString<wchar_t>: "<< ws.live() << " " << decltype(ws)::live() << std::endl;
};