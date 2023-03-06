//============================================================================
// Name        : Subject.cpp
// Created on  : 30.08.2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Proxy src
//============================================================================

#include <iostream>
#include <memory>
#include <utility>

namespace Proxy::Subject
{
    /**
     * The Subject interface declares common operations for both RealSubject and the
     * Proxy. As long as the client works with RealSubject using this interface,
     * you'll be able to pass it a proxy instead of a real subject.
     */
    class Subject {
    public:
        virtual void Request() const = 0;
    };


    /**
     * The RealSubject contains some core business logic. Usually, RealSubjects are
     * capable of doing some useful work which may also be very slow or sensitive -
     * e.g. correcting input data. A Proxy can solve these issues without any
     * changes to the RealSubject's code.
     */
    class RealSubject : public Subject {
    public:
        void Request() const override
        {
            std::cout << "RealSubject: Handling request." << std::endl;
        }
    };


    /**
     * The Proxy has an interface identical to the RealSubject.
     */
    class Proxy : public Subject {
    private:
        std::shared_ptr<RealSubject> realSubject;

        bool CheckAccess() const {
            // Some real checks should go here.
            std::cout << "  Proxy: Checking access prior to firing a real request." << std::endl;
            return true;
        }

        void LogAccess() const {
            std::cout << "  Proxy: Logging the time of request." << std::endl;;
        }

        /**
         * The Proxy maintains a reference to an object of the RealSubject class. It
         * can be either lazy-loaded or passed to the Proxy by the client.
         */
    public:
        explicit Proxy(std::shared_ptr<RealSubject> realSubject):
                realSubject(std::move(realSubject)) {
            // Do something more maybe,
        }

        ~Proxy() = default;

        /**
         * The most common applications of the Proxy pattern are lazy loading,
         * caching, controlling the access, logging, etc. A Proxy can perform one of
         * these things and then, depending on the result, pass the execution to the
         * same method in a linked RealSubject object.
         */
        void Request() const override {
            if (this->CheckAccess()) {
                this->realSubject->Request();
                this->LogAccess();
            }
        }
    };
}


namespace Proxy
{
    void SubjectTest() 
    {
        using namespace Subject;
        
        std::cout << "Client: Executing the client code with a real subject:\n";
        std::shared_ptr<RealSubject> realSubject = std::make_shared<RealSubject>();

        realSubject->Request();

        std::cout << "-----------------" << std::endl;

        std::cout << "Client: Executing the same client code with a proxy:\n";
        auto *proxy = new Proxy(realSubject);

        proxy->Request();
    }
}
