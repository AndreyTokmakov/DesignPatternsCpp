/**============================================================================
Name        : ObserverBasic.cpp
Created on  : August 14, 2020
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : ObserverBasic pattern test
============================================================================**/

#include "Observer.h"

#include <iostream>
#include <algorithm>
#include <list>

namespace Observer::Basic
{
    struct IObserver {
        virtual void update(struct IObservable* subject) const = 0;
        virtual ~IObserver() = default;
    };

    struct IObservable {
        virtual IObserver* addObserver(IObserver* observer) = 0;
        virtual IObserver* removeObserver(IObserver* observer) = 0;
        virtual void notify() noexcept = 0;
        virtual ~IObservable() = default;
    };

    class ObservableBase: public IObservable
    {
        std::list<IObserver*> observers;

    public:

        IObserver* addObserver(IObserver* observer) override {
            observers.push_back(observer);
            return observer;
        }

        IObserver* removeObserver(IObserver* observer) override {
            observers.remove(observer);
            return observer;
        }

        void notify()  noexcept override
        {
            for (const IObserver* observer : observers) {
                observer->update(this);
            }
        }
    };

    class Subject: public ObservableBase
    {
        std::string internalState { "None" };

    public:

        void setState(const std::string& state) {
            internalState = state;
            notify();
        }

        [[nodiscard]]
        std::string getState() const noexcept {
            return internalState;
        }
    };

    struct ConcreteObserverOne: public IObserver
    {
        void update(IObservable* subject) const override {
            std::cout << "ConcreteObserverOne::update() called ";
            if (auto* sub = dynamic_cast<Subject*>(subject); sub)
                std::cout << "Subject(" << sub->getState() << ")";
            std::cout << std::endl;
        }
    };

    struct ConcreteObserverTwo: public IObserver
    {
        void update(IObservable* subject) const override {
            std::cout << "ConcreteObserverTwo::update() called ";
            if (auto* sub = dynamic_cast<Subject*>(subject); sub)
                std::cout << "Subject(" << sub->getState() << ")";
            std::cout << std::endl;
        }
    };
}


// TODO: Update pointers --> std::shared_ptr<T>
void ObserverBasic_Test()
{
    using namespace Observer::Basic;

    Subject subject {};

    subject.addObserver(new ConcreteObserverOne());
    IObserver* o =subject.addObserver(new ConcreteObserverTwo());

    subject.setState("NEW");
    subject.setState("RUNNING");

    subject.removeObserver(o);

    subject.setState("STOPPED");
}
