//============================================================================
// Name        : Bridge.cpp
// Created on  : 08.06.2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Bridge src
//============================================================================

#define _CRT_SECURE_NO_WARNINGS

#include "Bridge.h"

#include <chrono>
#include <iostream>
#include <string>
#include <string_view>
#include <thread>

namespace Bridge::Clock
{
    struct AlarmClockImpl
    {
        virtual void ring() noexcept = 0;
        virtual void notify() noexcept = 0;
        virtual ~AlarmClockImpl() = default;
    };


    class AlarmClock {
    private:
        virtual void toWake() = 0;

    protected:
        std::unique_ptr<AlarmClockImpl> bridge;

    public:
        virtual void start() noexcept = 0;
        virtual void stop() noexcept = 0;
        virtual ~AlarmClock() = default;
    };


    class LockupAlarmClock : public AlarmClock {
    private:
        int hourAlarm;
        int minutesAlarm;
        bool waitForWake;

    private:
        void toWake() override 	{
            this->bridge->notify();
            this->bridge->ring();
        }

    public:
        LockupAlarmClock(std::unique_ptr<AlarmClockImpl> bridgeImpl,
                         int hour,
                         int minutes) {
            // this->bridge.reset(bridgeImpl.release());
            this->bridge = std::move(bridgeImpl);
            this->waitForWake = false;
            this->hourAlarm = hour;
            this->minutesAlarm = minutes;
        }

        void start() noexcept override
        {
            time_t rawtime;
            tm *timeinfo;

            std::cout << "ArarmClock stared" << std::endl;

            waitForWake = true;
            while (waitForWake) {
                time(&rawtime);
                timeinfo = localtime(&rawtime);
                if (timeinfo->tm_hour == this->hourAlarm && timeinfo->tm_min == this->minutesAlarm) {
                    waitForWake = false;
                } else {
                    std::cout << "Dont need to Ring" << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            toWake();
        }

        void stop() noexcept override {
            // stop lockup process
            waitForWake = false;
        }

    };

    class ShellMP3AlarmClock : public AlarmClockImpl {
    private:
        std::string cmdplay;

    public:
        explicit ShellMP3AlarmClock(const std::string &cmd) {
            this->cmdplay = cmd;
        }

        virtual ~ShellMP3AlarmClock() = default;

        void ring() noexcept {
            // run command
            // system(cmdplay.c_str());
            std::cout << cmdplay.c_str() << std::endl;
        }

        void notify() noexcept override {
            std::cout << "ALARMING!" << std::endl;
        }

    };


    void Test()
    {
        std::unique_ptr<AlarmClockImpl> clockImpl = std::make_unique<ShellMP3AlarmClock>("DING DING DING");

        std::shared_ptr<AlarmClock> clock = std::make_shared< LockupAlarmClock>(
                std::move(clockImpl), 9, 46);

        clock->start();
    }
}


void DrawingAPITest();


void Bridge::TestAll()
{
    // Clock::Test();

    DrawingAPITest();
}