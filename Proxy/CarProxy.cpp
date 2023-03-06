//============================================================================
// Name        : Proxy.cpp
// Created on  : 12.04.2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Proxy src
//============================================================================

#include "Proxy.h"

namespace Proxy::CarProxy
{
    class ICar {
    public:
        virtual ~ICar() {
            std::cout << "ICar destructor!" << std::endl;
        }

        virtual void DriveCar() noexcept = 0;
    };


    class Car : public ICar {
    public:
        void DriveCar() noexcept override {
            std::cout << "Car has been driven!" << std::endl;
        }
    };


    class ProxyCar : public ICar {
    private:
        std::unique_ptr<ICar> real_car_ = std::make_unique<Car>();
        int driver_age_;

    public:
        explicit ProxyCar(int driver_age) : driver_age_(driver_age) { /** **/ }
        void DriveCar() noexcept override {
            if (this->driver_age_ > 16) {
                this->real_car_->DriveCar();
            }
            else {
                std::cout << "Sorry, the driver is too young to drive." << std::endl;
            }
        }
    };
}

void Proxy::CarTest()
{
    using namespace CarProxy;

    {
        std::unique_ptr<ICar> car = std::make_unique<ProxyCar>(14);
        car->DriveCar();
    }

    std::cout << "\nAttempt 2: \n" << std::endl;

    {
        std::unique_ptr<ICar> car = std::make_unique<ProxyCar>(28);
        car->DriveCar();
    }
}