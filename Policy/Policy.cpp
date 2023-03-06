//============================================================================
// Name        : Policy.h
// Created on  : 24.07.22
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Policy pattern/idiom
//============================================================================

#include "Policy.h"

#include <iostream>
#include <string_view>

namespace Policy
{
    template <typename OutputPolicy>
    class Message : private OutputPolicy {            // (1)
    public:
        void write(const std::string& mess) const {
            print(mess);                              // (2)
        }
    private:
        using OutputPolicy::print;
    };

    class WriteToStdOut {
    protected:
        void print(const std::string& message) const {
            std::cout << "To cout: " << message << '\n';
        }
    };

    class WriteToFile {
    protected:
        void print(const std::string& message) const
        {
            // std::ofstream myFile;
            // myFile.open("policyInheritance.txt");
            // myFile << message << '\n';

            std::cout << "To file: " << message << '\n';
        }
    };

};

void Policy::Test()
{
    Message<WriteToStdOut> messageCout {};
    messageCout.write("Hello world");

    Message<WriteToFile> messageFile {};
    messageFile.write("Hello world");
};

