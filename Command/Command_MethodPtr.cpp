/**============================================================================
Name        : Test_MethodPtr.h
Created on  : 03.01.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Test_MethodPtr pattern src
============================================================================**/

#include "Command.h"

#include <iostream>
#include <string>
#include <functional>


namespace Command::MethodPtr
{
    template <class Type>
    class Command
    {
        Type *object { nullptr };
        void (Type::*method)() { nullptr };

    public:
        Command() = default;
        Command(Type *obj, void(Type::*m)()): object {obj}, method {m} {
        }

        void execute() {
            // TODO: std::invoke or call directly....
            // (object->*method)();
            std::invoke(method, object);
        }
    };

    class Person
    {
        std::string name {};
        Command<Person> cmd {};

    public:
        /*
        Person(std::string n, Command<Person> c): name { std::move(n) }, cmd(c) {
        }
        */

        Person(std::string n, Command<Person>&& c): name { std::move(n) }, cmd(c) {
        }

        void talk()
        {
            std::cout << name << " is talking" << std::endl;
            cmd.execute(); // ask the "black box" to callback the receiver
        }

        void passOn()
        {
            std::cout << name << " is passing on" << std::endl;
            // When the sender is ready to callback to the receiver,it calls execute()
            cmd.execute();
        }

        void gossip()
        {
            std::cout << name << " is gossiping" << std::endl;
            cmd.execute();
        }

        void listen()
        {
            std::cout << name << " is listening" << std::endl;
        }
    };

    void Test()
    {
        Person wilma("Wilma", Command<Person>());

        Person betty("Betty", Command(&wilma, &Person::listen));
        Person barney("Barney", Command(&betty, &Person::gossip));
        Person fred("Fred", Command(&barney, &Person::passOn));

        fred.talk();
    }
}

void Test_MethodPtr()
{
    Command::MethodPtr::Test();
}


