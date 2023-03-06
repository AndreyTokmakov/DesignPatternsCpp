/**============================================================================
Name        : ChainOfResponsibility.cpp
Created on  : 19.04.2020
Author      : Tokmakov Andrey
Version     : 1.0
Copyright   : Your copyright notice
Description : Chain of pesponsibility pattern src
============================================================================**/

#include "ChainOfResponsibility.h"

#include <vector>

namespace ChainOfResponsibility
{
    struct Handler {
    public:
        virtual Handler *SetNext(Handler *handler) = 0;
        virtual std::string Handle(const std::string& request) = 0;
        virtual ~Handler() = default;
    };


    struct AbstractHandler: Handler
    {
        Handler *nextHandler { nullptr };
        std::string handlerName {};

        explicit AbstractHandler(std::string name): handlerName {std::move(name)} {
            //
        }

        Handler *SetNext(Handler *handler) override {
            this->nextHandler = handler;
            return handler;
        }

        std::string Handle(const std::string& request) override {
            if (this->nextHandler)
                return this->nextHandler->Handle(request);
            return {};
        }
    };

    struct MonkeyHandler: AbstractHandler
    {
        explicit MonkeyHandler(std::string name):
                AbstractHandler {std::move(name)} {
        }

        std::string Handle(const std::string& request) override {
            if (request == "Banana") {
                return handlerName + ": i will\n";
            } else {
                std::cout << "  " << handlerName + ": i will NOT\n";
                return AbstractHandler::Handle(request);
            }
        }
    };

    struct SquirrelHandler: AbstractHandler
    {
        explicit SquirrelHandler(std::string name):
                AbstractHandler {std::move(name)} {
        }

        std::string Handle(const std::string& request) override {
            if (request == "Nut") {
                return handlerName + ": i will\n";
            } else {
                std::cout << "  " << handlerName + ": i will NOT\n";
                return AbstractHandler::Handle(request);
            }
        }
    };

    struct DogHandler: AbstractHandler
    {
        explicit DogHandler(std::string name):
                AbstractHandler {std::move(name)} {
        }

        std::string Handle(const std::string& request) override {
            if (request == "MeatBall") {
                return handlerName + ": i will\n";
            } else {
                std::cout << "  " << handlerName + ": i will NOT\n";
                return AbstractHandler::Handle(request);
            }
        }
    };

    void ClientCode(Handler &handler)
    {
        const std::vector<std::string> food {"Nut", "Banana", "Cup of coffee"};

        for (const std::string &f : food) {
            std::cout << "Client: Who wants a " << f << "?\n";
            const std::string result = handler.Handle(f);
            if (!result.empty()) {
                std::cout << "  " << result;
            } else {
                std::cout << "  " << f << " was left untouched.\n";
            }
        }
    }
}

void ChainOfResponsibility::Example2_Test()
{
    std::unique_ptr<MonkeyHandler> monkey { std::make_unique<MonkeyHandler>("Monkey")};
    std::unique_ptr<SquirrelHandler> squirrel { std::make_unique<SquirrelHandler>("Squirrel")};
    std::unique_ptr<DogHandler> dog { std::make_unique<DogHandler>("Dog")};

    monkey->SetNext(squirrel.get())->SetNext(dog.get());

    std::cout << "Chain: Monkey > Squirrel > Dog\n\n";
    ClientCode(*monkey);


    std::cout << "\nSubchain: Squirrel > Dog\n\n";
    ClientCode(*squirrel);
}