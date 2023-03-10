/**============================================================================
Name        : Visitor.cpp
Created on  : 17.04.2020
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Visitor pattern src
============================================================================**/

#include "Visitor.h"

namespace Visitor
{

    class IVisitor {
    public:
        virtual void visit(class Foo &ref) = 0;
        virtual void visit(class Bar &ref) = 0;
        virtual void visit(class Baz &ref) = 0;

        virtual ~IVisitor() = default;
    };

    class IElement {
    public:
        virtual void accept(IVisitor &v) = 0;
        virtual ~IElement() = default;
    };

    class Foo : public IElement {
    public:
        void accept(IVisitor & v) override {
            v.visit(*this);
        }
    };

    class Bar : public IElement {
    public:
        void accept(IVisitor & v) override {
            v.visit(*this);
        }
    };

    class Baz : public IElement {
    public:
        void accept(IVisitor &v) override{
            v.visit(*this);
        }
    };

    class CustomVisitor : public IVisitor {
    public:
        std::string value;

    public:
        void visit([[maybe_unused]] Foo &ref) override {
            value = "Foo";
        }

        void visit([[maybe_unused]] Bar &ref) override {
            value = "Bar";
        }

        void visit([[maybe_unused]] Baz &ref) override{
            value = "Baz";
        }
    };
}

void StockVisitorTest();
void DynamicComponentsVisitorTest();
void CarVisitorTest();

void Visitor::test()
{
    /*
	Foo foo;
	Bar bar;
	Baz baz;
	IElement *elements[] = { &foo, &bar, &baz };

    CustomVisitor visitor;
	for (auto elem : elements) {
		elem->accept(visitor);
		std::cout << visitor.value << std::endl;
	}
    */

    // StockVisitorTest();
    // DynamicComponentsVisitorTest();
    CarVisitorTest();
}