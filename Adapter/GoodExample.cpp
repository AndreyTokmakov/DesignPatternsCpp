/**============================================================================
Name        : GoodExample.cpp
Created on  : 26.12.2022
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : GoodExample
============================================================================**/

#include "Adapter.h"
#include <memory>

namespace Adapter
{
    struct OldApiInterface
    {
        virtual ~OldApiInterface() = default;

        virtual void oldApiCall() const {
            std::cout << "OldApiInterface::oldApiCall()" << std::endl;
        }
    };

    struct ModernApiInterface
    {
        virtual ~ModernApiInterface() = default;

        virtual void call() const {
            std::cout << "ModernApiInterface::call()" << std::endl;
        }
    };

    class ApiAdapter: public OldApiInterface, public ModernApiInterface {
        OldApiInterface& oldIface;

    public:
        explicit ApiAdapter(OldApiInterface& oldIfaceObject): oldIface { oldIfaceObject } {
        }

        void call() const override {
            std::cout << "Some new logic: ";
            oldIface.oldApiCall();
        }

    private:

        void oldApiCall() const override {
            std::cout << "DEPRECATED" << std::endl;
        }
    };


    void useApi(const ModernApiInterface *target) {
        target->call();
    }

    void useApiOLD(const OldApiInterface *target) {
        target->oldApiCall();
    }
}

void GoodExample_Test()
{
    using namespace Adapter;

    OldApiInterface oldApiObject;
    ModernApiInterface modernApiObject;

    useApi(&modernApiObject);
    // useApi(oldApiObject); // ERROR
    useApiOLD(&oldApiObject);

    std::cout << std::endl;

    ApiAdapter apiAdapter { oldApiObject};
    useApi(&modernApiObject);
    useApi(&apiAdapter);
    useApiOLD(&apiAdapter);
}