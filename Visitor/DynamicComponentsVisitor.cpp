/**============================================================================
Name        : DynamicComponentsVisitor.cpp
Created on  : 10.01.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : DynamicComponentsVisitor pattern src
============================================================================**/

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Visitor.h"

namespace Visitor::DynamicComponentsVisitor
{
    struct IVisitor {
    public:
        virtual void VisitConcreteComponentA(const struct ConcreteComponentA *element) const = 0;
        virtual void VisitConcreteComponentB(const struct ConcreteComponentB *element) const = 0;

        virtual ~IVisitor() = default;
    };


    struct IComponent {
    public:
        virtual ~IComponent() = default;
        virtual void Accept(IVisitor *visitor) const = 0;
    };


    struct ConcreteComponentA : public IComponent
    {
        void Accept(IVisitor *visitor) const override {
            visitor->VisitConcreteComponentA(this);
        }

        [[nodiscard]]
        std::string ExclusiveMethodOfConcreteComponentA() const {
            return "A";
        }
    };

    struct ConcreteComponentB : public IComponent
    {
        void Accept(IVisitor *visitor) const override {
            visitor->VisitConcreteComponentB(this);
        }

        [[nodiscard]]
        std::string SpecialMethodOfConcreteComponentB() const {
            return "B";
        }
    };

    struct ConcreteVisitor1 : public IVisitor
    {
        void VisitConcreteComponentA(const ConcreteComponentA *element) const override {
            std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
        }

        void VisitConcreteComponentB(const ConcreteComponentB *element) const override {
            std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
        }
    };

    struct ConcreteVisitor2 : public IVisitor
    {
        void VisitConcreteComponentA(const ConcreteComponentA *element) const override {
            std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
        }
        void VisitConcreteComponentB(const ConcreteComponentB *element) const override {
            std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
        }
    };

    void ClientCode(std::array<const IComponent*, 2> components, IVisitor* visitor) {
        for (const IComponent *comp : components) {
            comp->Accept(visitor);
        }
    }
}



void DynamicComponentsVisitorTest()
{
    using namespace Visitor::DynamicComponentsVisitor;

    std::array<const IComponent*, 2> components = {new ConcreteComponentA, new ConcreteComponentB};
    auto visitor1 = std::make_unique<ConcreteVisitor1>();
    ClientCode(components, visitor1.get());

    std::cout << "\n";
    auto visitor2 = std::make_unique<ConcreteVisitor2>();
    ClientCode(components, visitor2.get());

    for (const IComponent *comp : components) {
        delete comp;
    }
}