/**============================================================================
Name        : TypeErasure.cpp
Created on  : 08.05.22.
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : TypeErasure
============================================================================**/

#include "TypeErasure.h"

#include <iostream>
#include <vector>
#include <memory>

namespace TypeErasure::ExperimentFirst
{
    class Object {
    public:
        template<typename T>
        explicit Object(T&& obj):
            concept_(std::make_shared<struct ConcreteCommand<T>>(std::forward<T>(obj))) {
        }

        [[nodiscard]]
        int get_id() const { return concept_->get_id(); }

    private:
        struct ICommand {
            virtual ~ICommand() = default;

            [[nodiscard]]
            virtual int get_id() const = 0;
        };

        template<typename T>
        struct ConcreteCommand final : ICommand {
            explicit ConcreteCommand(T&& obj) noexcept : object_(std::forward<T>(obj)) {

            }

            [[nodiscard]]
            int get_id() const final {
                return object_.get_id();
            }

        private:
            T object_;
        };

        std::shared_ptr<ICommand> concept_;
    };

    class Bar {
    public:
        [[nodiscard]]
        int get_id() const { return 1; }
    };

    struct Foo {
    public:
        [[nodiscard]]
        int get_id() const { return 2; }
    };

    struct FooEx {
    public:
        // [[nodiscard]]
        // int get_id() const { return 2; }
    };

    void Test() {
        Object o1(Bar{});
        Object o2(Foo{});
        // Object o3(FooEx{});

        std::cout << o1.get_id() << std::endl;
        std::cout << o2.get_id() << std::endl;
    }
}

namespace TypeErasure::ExperimentSecond
{
    struct Object
    {
        struct Interface
        {
            virtual ~Interface() = default;

            [[nodiscard]]
            virtual std::string getName() const = 0;
        };

        std::shared_ptr<const Interface> object {};

        template <typename T>
        explicit Object(T&& obj): object {
            std::make_shared<struct Model<T>>(std::forward<T>(obj))} {
        }

        [[nodiscard]]
        std::string getName() const {
            return object->getName();
        }

        template<typename T>
        struct Model : Interface
        {
            explicit Model(const T& t) : object { t } { }
            explicit Model(T&& t) : object { std::move(t) } { }

            [[nodiscard]]
            std::string getName() const override {
                return object.getName();
            }
        private:
            T object;
        };
    };

    struct Bar {
        [[nodiscard]]
        static std::string getName() {
            return "Bar";
        }
    };

    struct Foo {
        [[nodiscard]]
        std::string getName() const {
            return "Foo";
        }
    };

    void Test()
    {
        std::vector<Object> vec{Object(Foo()), Object(Bar())};  // (1)
        for (auto v: vec)
            std::cout << v.getName() << '\n';
    }
}

void TypeErasure::Test()
{
    // ExperimentFirst::Test();
    ExperimentSecond::Test();
};

