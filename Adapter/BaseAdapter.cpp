/**============================================================================
Name        : BaseAdapter.h
Created on  : 26.12.2022
Author      : Tokmakov Andrei
Version     : 1.0
Copyright   : Your copyright notice
Description : Base
============================================================================**/

#include "Adapter.h"
#include <memory>

namespace Adapter
{
    // The Target defines the domain-specific interface used by the client code.
    struct Target
    {
        virtual ~Target() = default;

        [[nodiscard]]
        virtual std::string Request() const {
            return "Target : The default target's behavior.";
        }
    };

    // The ToBeAdapted contains some useful behavior, but its interface is incompatible with the
    // existing client code. The ToBeAdapted needs some adaptation before the client code can use it.
    struct ToBeAdapted
    {
        [[nodiscard]]
        std::string SpecificRequest() const {
            return ".eetpadA eht fo roivaheb laicepS";
        }
    };

    // The Adapter makes the 'ToBeAdapted' interface compatible with the Target's interface.
    class TargetAdapter : public Target {
    private:
        std::unique_ptr<ToBeAdapted> toBeAdapted;

    public:
        explicit TargetAdapter(std::unique_ptr<ToBeAdapted> obj) : toBeAdapted { std::move(obj) } {

        }

        [[nodiscard]]
        std::string Request() const override {
            std::string to_reverse = this->toBeAdapted->SpecificRequest();
            std::reverse(to_reverse.begin(), to_reverse.end());
            return "Adapter: " + to_reverse + " (TRANSLATED)";
        }
    };

    // The client code supports all classes that follow the Target interface.
    void ClientCode(const Target *target) {
        std::cout << target->Request();
    }
}

void BaseAdapterTest()
{
    using namespace Adapter;

    std::unique_ptr<Target> target { std::make_unique<Target>()};
    ClientCode(target.get());

    std::cout << std::endl;

    std::unique_ptr<ToBeAdapted> toBeAdapted { std::make_unique<ToBeAdapted>()};
    std::unique_ptr<Target> adapter { std::make_unique<TargetAdapter>(std::move(toBeAdapted))};
    ClientCode(adapter.get());

}