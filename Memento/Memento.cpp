//============================================================================
// Name        : Memento.cpp
// Created on  : August 14, 2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Memento pattern test
//============================================================================

#include "Memento.h"

#include <utility>

namespace Memento
{
    /**
     * The Memento interface provides a way to retrieve the memento's metadata, such
     * as creation date or name. However, it doesn't expose the Originator's state.
     */
    class Memento {
    public:
        [[nodiscard]]
        virtual std::string getName() const noexcept = 0;

        [[nodiscard]]
        virtual std::string getDate() const noexcept = 0;

        [[nodiscard]]
        virtual std::string getState() const noexcept = 0;

        virtual ~Memento() = default;
    };


    /**
     * The Concrete Memento contains the infrastructure for storing the Originator's
     * state.
     */
    class ConcreteMemento : public Memento {
    private:
        std::string state;
        std::string date;

    public:

        explicit ConcreteMemento(std::string  state): state(std::move(state)) {
            std::time_t now = std::time(nullptr);
            this->date = std::ctime(&now);
        }

        /**
         * The Originator uses this method when restoring its state.
         */
        [[nodiscard]]
        inline std::string getState() const noexcept override {
            return this->state;
        }

        /**
         * The rest of the methods are used by the Caretaker to display metadata.
         */
        [[nodiscard]]
        inline std::string getName() const noexcept override {
            return this->date + " / (" + this->state.substr(0, 9) + "...)";
        }

        /**
         * Returns the Date as string.
         */
        [[nodiscard]]
        inline std::string getDate() const noexcept override {
            return this->date;
        }
    };

    /**
     * The Originator holds some important state that may change over time. It also
     * defines a method for saving the state inside a memento and another method for
     * restoring the state from it.
     */
    class Originator {
    private:
        std::string state;

    protected:
        [[nodiscard]]
        static std::string GenerateRandomString(size_t length = 10) noexcept {
            char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            constexpr size_t stringLength = sizeof(alphanum) - 1;
            static_assert(stringLength > 1);

            std::string random_string;
            for (size_t i = 0; i < length; i++) {
                random_string += alphanum[std::rand() % stringLength];
            }
            return random_string;
        }


    public:
        /**
         * The Originator holds some important state that may change over time. It also
         * defines a method for saving the state inside a memento and another method for
         * restoring the state from it.
         */
        explicit Originator(std::string  state) : state(std::move(state)) {
            std::cout << "Originator: My initial state is: " << this->state << std::endl;
        }

        /**
         * The Originator's business logic may affect its internal state. Therefore,
         * the client should backup the state before launching methods of the business
         * logic via the save() method.
         */
        void DoSomething() {
            std::cout << "Originator: I'm doing something important." << std::endl;
            this->state = Originator::GenerateRandomString(30);
            std::cout << "Originator: and my state has changed to: " << this->state << std::endl;
        }

        /** Saves the current state inside a memento **/
        std::shared_ptr<Memento> Save() {
            return std::make_shared<ConcreteMemento>(this->state);
        }

        /** Restores the Originator's state from a memento object **/
        void Restore(const std::shared_ptr<Memento>& memento) {
            this->state = memento->getState();
            std::cout << "Originator: My state has changed to: " << this->state << std::endl;
        }
    };


    /**
     * The Caretaker doesn't depend on the Concrete Memento class. Therefore, it
     * doesn't have access to the originator's state, stored inside the memento. It
     * works with all mementos via the base Memento interface.
     */
    class Caretaker {
    private:
        // Vector to store saved states:
        std::vector<std::shared_ptr<Memento>> backUps;

        //  Originator
        std::shared_ptr<Originator> originator;

    public:
        /**
         * The Caretaker doesn't depend on the Concrete Memento class. Therefore, it
         * doesn't have access to the originator's state, stored inside the memento. It
         * works with all mementos via the base Memento interface.
         */
        explicit Caretaker(std::shared_ptr<Originator> originator) : originator(std::move(originator)) {

        }

        void Backup() {
            std::cout << "\nCaretaker: Saving Originator's state..." << std::endl;
            this->backUps.push_back(this->originator->Save());
        }

        void Undo() {
            if (this->backUps.empty())
                return;

            std::shared_ptr<Memento> memento = std::move(this->backUps.back());
            this->backUps.pop_back();
            std::cout << "Caretaker: Restoring state to: " << memento->getName() << std::endl;

            try {
                this->originator->Restore(memento);
            } catch (...) {
                this->Undo();
            }
        }

        void ShowHistory() const {
            std::cout << "History:" << std::endl;
            for (const auto& memento : this->backUps) {
                std::cout << "  " << memento->getName() << std::endl;
            }
        }
    };


	void TestAll()
    {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		std::shared_ptr<Originator> originator = std::make_shared<Originator>("Super-duper-super-puper-super.");
		std::shared_ptr<Caretaker> caretaker = std::make_shared<Caretaker>(originator);
		caretaker->Backup();
		originator->DoSomething();
		caretaker->Backup();
		originator->DoSomething();
		caretaker->Backup();
		originator->DoSomething();
		std::cout << "\n";
		caretaker->ShowHistory();
		std::cout << "\nClient: Now, let's rollback!\n\n";
		caretaker->Undo();
		std::cout << "\nClient: Once more!\n\n";
		caretaker->Undo();
	}
}