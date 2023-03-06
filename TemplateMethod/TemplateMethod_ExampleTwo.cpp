/**============================================================================
Name        : TemplateMethod_ExampleTwo.h
Created on  : 10.01.2023
Author      : Tokmakov Andrei
Version     : 1.0
Copyright   : Your copyright notice
Description : TemplateMethod
============================================================================**/

#include "TemplateMethod.h"

#include <iostream>
#include <memory>

namespace TemplateMethod::TemplateMethod_ExampleTwo
{
    struct AbstractClass
    {
        void TemplateMethod() const {
            this->BaseOperation1();
            this->RequiredOperations1();
            this->BaseOperation2();
            this->Hook1();
            this->RequiredOperation2();
            this->BaseOperation3();
            this->Hook2();
        }

    protected:
        void BaseOperation1() const {
            std::cout << "AbstractClass: I am doing the bulk of the work\n";
        }

        void BaseOperation2() const {
            std::cout << "AbstractClass: But I let subclasses override some operations\n";
        }

        void BaseOperation3() const {
            std::cout << "AbstractClass: But I am doing the bulk of the work anyway\n";
        }

        /// These operations have to be implemented in subclasses:

        virtual void RequiredOperations1() const = 0;
        virtual void RequiredOperation2() const = 0;
        virtual void Hook1() const {}
        virtual void Hook2() const {}

        virtual ~AbstractClass() = default;
    };

    class ConcreteClassOne : public AbstractClass {
    protected:
        void RequiredOperations1() const override {
            std::cout << "ConcreteClassOne: Implemented Operation1\n";
        }
        void RequiredOperation2() const override {
            std::cout << "ConcreteClassOne: Implemented Operation2\n";
        }
    };

    class ConcreteClassTwo : public AbstractClass {
    protected:
        void RequiredOperations1() const override {
            std::cout << "ConcreteClassTwo: Implemented Operation1\n";
        }
        void RequiredOperation2() const override {
            std::cout << "ConcreteClassTwo: Implemented Operation2\n";
        }
        void Hook1() const override {
            std::cout << "ConcreteClassTwo: Overridden Hook1\n";
        }
    };

    void invokeTemplateMethod(AbstractClass *ptr) {
        ptr->TemplateMethod();
    }
};

void TemplateMethod_ExampleTwo_Test()
{
    using namespace TemplateMethod::TemplateMethod_ExampleTwo;

    auto ptr1 = std::make_unique<ConcreteClassOne>();
    invokeTemplateMethod(ptr1.get());

    std::cout << std::endl;

    auto ptr2 = std::make_unique<ConcreteClassTwo>();
    invokeTemplateMethod(ptr2.get());
};
