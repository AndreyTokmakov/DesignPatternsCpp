//============================================================================
// Name        : Facade.cpp
// Created on  : 20.08.2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Facade pattern src
//============================================================================

#include "Facade.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>


namespace Facade::Systems
{

    class System1 {
    public:
        [[nodiscard]]
        std::string Operation1() const noexcept {
            return "Subsystem1: Operation1!\n";
        }

        [[nodiscard]]
        std::string OperationA() const noexcept {
            return "Subsystem1: OperationA\n";
        }

    };



    class System2 {
    public:

        [[nodiscard]]
        std::string Operation1() const noexcept {
            return "Subsystem2: Operation1\n";
        }

        [[nodiscard]]
        std::string OperationB() const noexcept {
            return "Subsystem2: OperationB!\n";
        }
    };


    class Facade {
    protected:
        std::unique_ptr<System1> system1;
        std::unique_ptr<System2> system2;

    public:

        Facade(std::unique_ptr<System1> sys1, std::unique_ptr<System2> sys2):
                system1(std::move(sys1)), system2(std::move(sys2)) {
        }

        virtual ~Facade() = default;

        std::string Operation() noexcept
        {
            std::string result = "Facade initializes subsystems:\n";
            result += this->system1->Operation1();
            result += this->system2->Operation1();

            result += "\nFacade orders subsystems to perform the action:\n";
            result += this->system1->OperationA();
            result += this->system2->OperationB();
            return result;
        }
    };

    void Test()
    {
        std::shared_ptr<Facade> facade = std::make_shared<Facade>(
                std::unique_ptr<System1>(),
                std::unique_ptr<System2>()
        );

        std::cout << facade->Operation();
    }
};


namespace Facade::HouseFacade
{
    struct Alarm
    {
        void alarmOn() {
            std::cout << "Alarm is on and house is secured"<<std::endl;
        }

        void alarmOff() {
            std::cout << "Alarm is off and you can go into the house"<<std::endl;
        }
    };

    struct Ac
    {
        void acOn() {
            std::cout << "Ac is on"<<std::endl;
        }

        void acOff() {
            std::cout << "AC is off"<<std::endl;
        }
    };

    struct Tv
    {
        void tvOn() {
            std::cout << "Tv is on"<<std::endl;
        }

        void tvOff() {
            std::cout << "TV is off"<<std::endl;
        }
    };

    struct HouseFacade
    {
        Alarm alarm;
        Ac ac;
        Tv tv;

        void goToWork() {
            ac.acOff();
            tv.tvOff();
            alarm.alarmOn();
        }

        void comeHome() {
            alarm.alarmOff();
            ac.acOn();
            tv.tvOn();
        }
    };

    void Test()
    {
        HouseFacade hf {};

        hf.goToWork();
        hf.comeHome();
    }
};

void Facade::Test()
{
    // Systems::Test();
    HouseFacade::Test();
}
