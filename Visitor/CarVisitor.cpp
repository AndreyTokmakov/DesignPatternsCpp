/**============================================================================
Name        : CarVisitor.cpp
Created on  : 14.01.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : CarVisitor pattern src
============================================================================**/

#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <vector>

#include "Visitor.h"

namespace Visitor::CarVisitor
{
    struct CarElement {
        virtual void accept(class CarElementVisitor& visitor) const = 0;
        virtual ~CarElement() = default;
    };

    class CarElementVisitor {
    public:
        virtual void visit(const class Body& body) const = 0;
        virtual void visit(const class Car& car) const = 0;
        virtual void visit(const class Engine& engine) const = 0;
        virtual void visit(const class Wheel& wheel) const = 0;
        virtual ~CarElementVisitor() = default;
    };

    class Wheel: public CarElement {
    public:
        explicit Wheel(std::string n): name(std::move(n)) {
        }

        void accept(CarElementVisitor& visitor) const override {
            visitor.visit(*this);
        }

        [[nodiscard]]
        std::string getName() const {
            return name;
        }

    private:
        std::string name;
    };

    class Body: public CarElement {
    public:
        void accept(CarElementVisitor& visitor) const override {
            visitor.visit(*this);
        }
    };

    class Engine: public CarElement {
    public:
        void accept(CarElementVisitor& visitor) const override {
            visitor.visit(*this);
        }
    };

    class Car: public CarElement {
    public:
        Car(std::initializer_list<CarElement*> carElements ): elements{carElements} {}

        void accept(CarElementVisitor& visitor) const override {
            for (auto elem : elements) {
                elem->accept(visitor);
            }
            visitor.visit(*this);
        }

    private:
        std::vector<CarElement*> elements;
    };

    class CarElementDoVisitor: public CarElementVisitor {

        void visit(const Body& body) const override {
            std::cout << "Moving my body" << '\n';
        }

        void visit(const Car& car) const override {
            std::cout << "Starting my car" << '\n';
        }

        void visit(const Wheel& wheel) const override {
            std::cout << "Kicking my " << wheel.getName() << " wheel" << '\n';
        }

        void visit(const Engine& engine) const override {
            std::cout << "Starting my engine" << '\n';
        }
    };

    class CarElementPrintVisitor: public CarElementVisitor {

        void visit(const Body& body) const override {
            std::cout << "Visiting body" << '\n';
        }

        void visit(const Car& car) const override {
            std::cout << "Visiting car" << '\n';
        }

        void visit(const Wheel& wheel) const override {
            std::cout << "Visiting " << wheel.getName() << " wheel" << '\n';
        }

        void visit(const Engine& engine) const override {
            std::cout << "Visiting engine" << '\n';
        }
    };
}

void CarVisitorTest()
{
    using namespace Visitor::CarVisitor;

    Wheel wheelFrontLeft("front left");
    Wheel wheelFrontRight("front right");
    Wheel wheelBackLeft("back left");
    Wheel wheelBackRight("back right");
    Body body;
    Engine engine;
    Car car {&wheelFrontLeft, &wheelFrontRight, &wheelBackLeft, &wheelBackRight, &body, &engine};

    CarElementPrintVisitor carElementPrintVisitor;

    engine.accept(carElementPrintVisitor);
    car.accept(carElementPrintVisitor);

    std::cout << '\n';

    CarElementDoVisitor carElementDoVisitor;

    engine.accept(carElementDoVisitor);
    car.accept(carElementDoVisitor);
}