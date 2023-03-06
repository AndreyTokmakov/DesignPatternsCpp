/**============================================================================
Name        : VirtualConstructor.cpp
Created on  : 27.11.2022
Author      : Tokmakov Andrey
Version     : 1.0
Copyright   : Your copyright notice
Description : VirtualConstructor
============================================================================**/

#include "VirtualConstructor.h"

#include <iostream>
#include <memory>


/**
 * Intent of Virtual Constructor: To create a copy or new object without knowing its concrete type.
**/


namespace VirtualConstructor::SampleOne
{
    struct animal
    {
        virtual ~animal() = default;

        [[nodiscard]]
        virtual std::unique_ptr<animal> create() = 0;

        [[nodiscard]]
        virtual std::unique_ptr<animal> clone() = 0;
    };

    struct dog : animal
    {
        [[nodiscard]]
        std::unique_ptr<animal> create() override {
            return std::make_unique<dog>();
        }

        [[nodiscard]]
        std::unique_ptr<animal> clone() override {
            return std::make_unique<dog>(*this);
        }
    };

    struct cat : animal
    {
        [[nodiscard]]
        std::unique_ptr<animal> create() override {
            return std::make_unique<cat>();
        }

        [[nodiscard]]
        std::unique_ptr<animal> clone() override {
            return std::make_unique<cat>(*this);
        }
    };


    void Test()
    {
        auto who_am_i = [] (animal *who) {
            auto new_who = who->create();// `create` the object of same type i.e. pointed by who ?
            auto duplicate_who = who->clone(); // `copy` object of same type i.e. pointed by who ?
        };

        dog d;
        who_am_i(&d);
    }

};

void VirtualConstructor::Test()
{
    SampleOne::Test();
};
