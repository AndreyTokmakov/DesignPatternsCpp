//============================================================================
// Name        : Command.h
// Created on  : 12.04.2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Command pattern src
//============================================================================

#include "Command.h"

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

namespace Command::Switch_ON_OFF_Light
{
    // Command Interface
    struct ICommand {
        virtual void execute() = 0;
        virtual ~ICommand() = default;
    };

    // Receiver Class
    struct Light {
        virtual void on() {
            std::cout << "The light is ON" << std::endl;
        }

        virtual void off() {
            std::cout << "The light is OFF" << std::endl;
        }

        virtual ~Light() = default;
    };

    // Command for turning on the light
    struct LightOnCommand: ICommand {
        explicit LightOnCommand(std::shared_ptr<Light> light) : mLight(std::move(light)) {
        }

        void execute() override {
            this->mLight->on();
        }

    private:
        std::shared_ptr<Light> mLight;
    };

    // Command for turning off the light
    struct LightOffCommand: ICommand {
        explicit LightOffCommand(std::shared_ptr<Light> light) : mLight(std::move(light)) {
        }

        void execute() override {
            this->mLight->off();
        }

    private:
        std::shared_ptr<Light> mLight;
    };

    // Invoker: Stores the ConcreteCommand object
    class RemoteControl {
    private:
        std::shared_ptr<ICommand> command;

    public:
        void setCommand(const std::shared_ptr<ICommand>& cmd) {
            this->command = cmd;
        }

        void buttonPressed() {
            command->execute();
        }
    };

    void Test()
    {
        std::shared_ptr<Light> light = std::make_shared<Light>();
        std::shared_ptr<RemoteControl> control = std::make_shared<RemoteControl>();

        // concrete Command objects
        // std::unique_ptr<LightOnCommand> lightOn = std::make_unique<LightOnCommand>(new LightOnCommand(light));
        std::shared_ptr<LightOnCommand> lightOn = std::make_shared<LightOnCommand>(light);
        std::shared_ptr<LightOffCommand> lightOff = std::make_shared<LightOffCommand>(light);

        // execute
        control->setCommand(lightOn);
        control->buttonPressed();
        control->setCommand(lightOff);
        control->buttonPressed();
    }
}

void Test_MethodPtr();

void Command::TestAll()
{

    // Switch_ON_OFF_Light::Test();
    Test_MethodPtr();
}
