/**============================================================================
Name        : Decorator.cpp
Created on  :
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Decorator src
============================================================================**/


#include "Decorator.h"
#include "ShapeDecorator.h"

#include <iostream>
#include <memory>
#include <utility>

namespace Decorator
{
    class IComponent {
    public:
        virtual void operation() = 0;
        virtual ~IComponent() = default;
    };


    class Component : public IComponent {
    public:
        void operation() override {
            std::cout << "World!" << std::endl;
        }
    };


    class DecoratorOne : public IComponent {
        std::shared_ptr<IComponent> m_component;

    public:
        explicit DecoratorOne(std::shared_ptr<IComponent> component):
                m_component(std::move(component)) {
        }

        void operation() override {
            std::cout << "...... ";
            m_component->operation();
        }
    };


    class DecoratorTwo : public IComponent {
        std::shared_ptr<IComponent> m_component;

    public:
        explicit DecoratorTwo(std::shared_ptr<IComponent> component):
                m_component(std::move(component)) {
        }

        void operation() override {
            std::cout << "Hello";
            m_component->operation();
        }
    };
}

void Decorator::Test()
{
    /*
	DecoratorTwo obj(std::make_shared<DecoratorOne>(std::make_shared<Component>()));
	obj.operation();
    */

    ShapeDecorator::Test();
}
