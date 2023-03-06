/**============================================================================
Name        : TemplateMethod_ExampleThree.h
Created on  : 10.01.2023
Author      : Tokmakov Andrei
Version     : 1.0
Copyright   : Your copyright notice
Description : TemplateMethod_ExampleThree
============================================================================**/

#include "TemplateMethod.h"

#include <iostream>
#include <memory>

namespace TemplateMethod::TemplateMethod_ExampleThree
{

    struct Base
    {
        void a() { std::cout << "a" << std::endl; }
        void b() { std::cout << "b" << std::endl; }
        void c() { std::cout << "c" << std::endl; }

        virtual void abstractOperationOne() = 0;
        virtual void abstractOperationTwo() = 0;

        void templateMethod()
        {
            a();
            abstractOperationOne();
            b();
            abstractOperationTwo();
            c();
        }

        virtual ~Base() = default;
    };

    class One: public Base
    {
        void abstractOperationOne() override {
            std::cout << "One::abstractOperationOne()" << std::endl;
        }

        void abstractOperationTwo() override {
            std::cout << "One::abstractOperationTwo()" << std::endl;
        }
    };

    class Two: public Base
    {
        void abstractOperationOne() override {
            std::cout << "Two::abstractOperationOne()" << std::endl;
        }

        void abstractOperationTwo() override {
            std::cout << "Two::abstractOperationTwo()" << std::endl;
        }
    };

};

void TemplateMethod_ExampleThree_Test()
{
    using namespace TemplateMethod::TemplateMethod_ExampleThree;

    const std::array<std::unique_ptr<Base>, 2> array { std::make_unique<One>(), std::make_unique<Two>() };
    for (auto&& ptr: array) {
        ptr->templateMethod();
        std::cout << std::endl;
    }
};
