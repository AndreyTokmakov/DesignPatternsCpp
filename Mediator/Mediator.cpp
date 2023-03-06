/**============================================================================
Name        : Mediator.cpp
Created on  : 17.08.2020
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Mediator pattern src
============================================================================**/

#include "Mediator.h"
#include <iostream>
#include <string>
#include <memory>
#include <cassert>
#include <utility>


namespace Mediator
{

    /**
     * The Mediator interface declares a method used by components to notify the mediator about various events.
     * The Mediator may react to these events and pass the execution to other components.
     */
    class Mediator {
    public:
        virtual void Notify(std::shared_ptr<class BaseComponent> sender,
                            const std::string& event) const noexcept = 0;

        virtual ~Mediator() = default;
    };


    /**
     * The Base Component provides the basic functionality of storing a mediator's instance inside component objects.
     */
    class BaseComponent {
    protected:
        std::shared_ptr<Mediator> _mediator;

    public:
        explicit BaseComponent(std::shared_ptr<Mediator> mediator = nullptr):
                _mediator { std::move(mediator) } {
        }

        void setMediator(std::shared_ptr<Mediator> med) {
            _mediator = std::move(med);
        }
    };


    /**
     * Concrete Components implement various functionality. They don't depend on
     * other components. They also don't depend on any concrete mediator classes.
     */
    class Component1 : public BaseComponent,
                       public std::enable_shared_from_this<Component1> {
    public:

        /**
         * Concrete Components implement various functionality. They don't depend on
         * other components. They also don't depend on any concrete mediator classes.
         */
        void DoA() {
            std::cout << "Component 1 does A" << std::endl;
            this->_mediator->Notify(this->shared_from_this(), "A");
        }

        void DoB() {
            std::cout << "Component 1 does B" << std::endl;
            this->_mediator->Notify(this->shared_from_this(), "B");
        }
    };

    class Component2 : public BaseComponent,
                       public std::enable_shared_from_this<Component2> {
    public:
        void DoC() {
            std::cout << "Component 2 does C" << std::endl;
            this->_mediator->Notify(this->shared_from_this(), "C");
        }

        void DoD() {
            std::cout << "Component 2 does D" << std::endl;
            this->_mediator->Notify(this->shared_from_this(), "D");
        }
    };


    /**
     * Concrete Mediators implement cooperative behavior by coordinating several
     * components.
 */
    class ConcreteMediator: public Mediator,
                            public std::enable_shared_from_this<ConcreteMediator> {
    private:
        std::shared_ptr<Component1> component1;
        std::shared_ptr<Component2> component2;

    public:
        /** Concrete Mediators implement cooperative behavior by coordinating several components.  **/
        ConcreteMediator(std::shared_ptr<Component1> c1, std::shared_ptr<Component2> c2):
                component1(std::move(c1)), component2(std::move(c2)) {
        }

        void Notify(std::shared_ptr<BaseComponent>,
                    const std::string &event) const noexcept override  {
            std::cout << "Mediator reacts on " << event << " and triggers following operations:\n";

            if ("A" == event) {
                this->component2->DoC();
            }
            else if ("B" == event) {
                this->component1->DoB();
                this->component2->DoC();
            }
        }

        void Init()
        {
            assert(nullptr != this->shared_from_this());
            this->component1->setMediator(this->shared_from_this());
            this->component2->setMediator(this->shared_from_this());
        }
    };
}

/** From CharMediator.cpp **/
void CharRoomMediator();

void Mediator::TestAll()
{

    CharRoomMediator();

    /*
	std::shared_ptr<Component1> c1 = std::make_shared<Component1>();
	std::shared_ptr<Component2> c2           = std::make_shared<Component2>();

	std::shared_ptr<ConcreteMediator> mediator = std::make_shared<ConcreteMediator>(c1, c2);
	mediator->Init();

	std::cout << "Client triggers operation A." << std::endl;
	c1->DoA();


	std::cout << "\n\nClient triggers operation D." << std::endl;
	c2->DoD();
    */
}

