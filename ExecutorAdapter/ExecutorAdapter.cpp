/**============================================================================
Name        : ExecutorAdapter.cpp
Created on  : 30.08.2022
Author      : Tokmakov Andrey
Version     : 1.0
Copyright   : Your copyright notice
Description : ExecutorAdapter
============================================================================**/

#include "ExecutorAdapter.h"

#include <iostream>
#include <memory>

namespace ExecutorAdapter::One
{
    class ExecuteInterface {
    public:
        virtual ~ExecuteInterface() = default;
        virtual void execute() = 0;
    };

    template <class Type>
    class ExecuteAdapter: public ExecuteInterface {
    public:
        ExecuteAdapter(Type *obj, void(Type::*m)()): object {obj}, method {m} {
        }

        ~ExecuteAdapter() override {
            delete object;
        }

        void execute() override {
            (object->*method)();
        }

    private:
        Type *object { nullptr };
        void (Type::*method)();
    };

    class Foo {
    public:
        ~Foo() {
            std::cout << "~Foo::Foo()" << std::endl;
        }

        void doSomething() {
            std::cout << "Foo::doSomething()" << std::endl;
        }
    };

    void Test()
    {
        auto objPtr = new ExecuteAdapter<Foo> (new Foo(), &Foo::doSomething);
        objPtr->execute();
        delete objPtr;
    }
}

namespace ExecutorAdapter::Two
{
    class ExecuteInterface {
    public:
        virtual ~ExecuteInterface() = default;
        virtual void execute() = 0;
    };

    template <class Type>
    class ExecuteAdapter: public ExecuteInterface {
    public:
        ExecuteAdapter(std::unique_ptr<Type> obj, void(Type::*m)()): object { std::move(obj) }, method {m} {
        }

        void execute() override {
            (object.get()->*method)();
        }

    private:
        std::unique_ptr<Type> object {nullptr };
        void (Type::*method)();
    };

    class Foo {
    public:
        ~Foo() {
            std::cout << "~Foo::Foo()" << std::endl;
        }

        void doSomething() {
            std::cout << "Foo::doSomething()" << std::endl;
        }
    };

    void Test()
    {
        auto objPtr = new ExecuteAdapter<Foo> (std::make_unique<Foo>(), &Foo::doSomething);
        objPtr->execute();
        delete objPtr;
    }
}

namespace ExecutorAdapter::Three
{

    template<typename Ret>
    class ExecuteInterface {
    public:
        virtual ~ExecuteInterface() = default;
        virtual Ret execute() = 0;
    };

    template <typename Ret, class Type>
    class ExecuteAdapter: public ExecuteInterface<Ret> {
    public:
        ExecuteAdapter(std::unique_ptr<Type> obj, Ret(Type::*m)()):
                object { std::move(obj) }, method {m} {
        }

        Ret execute() override {
            return (object.get()->*method)();
        }

    private:
        std::unique_ptr<Type> object { nullptr };
        Ret (Type::*method)();
    };

    class Foo {
    public:
        ~Foo() {
            std::cout << "~Foo::Foo()" << std::endl;
        }

        void doSomething() {
            std::cout << "Foo::doSomething()" << std::endl;
        }
    };

    class Bar {
    public:
        ~Bar() {
            std::cout << "~Bar::Bar()" << std::endl;
        }

        std::string getValue() {
            return {"qwerty"};
        }
    };

    void Test()
    {
        auto obj = std::make_unique<ExecuteAdapter<void, Foo>>(std::make_unique<Foo>(), &Foo::doSomething);
        obj->execute();

        auto obj2 = std::make_unique<ExecuteAdapter<std::string, Bar>>(std::make_unique<Bar>(), &Bar::getValue);
        std::cout << obj2->execute() << std::endl;
    }
};

void ExecutorAdapter::TestAll()
{
    // One::Test();
    // Two::Test();
    Three::Test();
};


