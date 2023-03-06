/**============================================================================
Name        : UserBuilder.cpp
Created on  :
Author      : Tokmakov Andrei
Version     : 1.0
Copyright   : Your copyright notice
Description : User builder example
============================================================================**/

#include "Builder.h"
#include <string>
#include <vector>

namespace Builder
{
    class User
    {
    private:
        uint32_t     id = 0;
        std::string  name;
        std::string  lastName;
        std::string  email;

    public:
        /*
        User() {
            std::cout << "User::User()" << std::endl;
        }

        ~User() {
            std::cout << "User::~User()" << std::endl;
        }

        User(const User& u): id { u.id }, name { u.name },
                lastName { u.lastName }, email { u.email }
        {
            std::cout << "User::User(const User&)" << std::endl;
        }

        User& operator=(const User& u)
        {
            std::cout << "User operator=(const User& u)" << std::endl;
            //
            return *this;
        }

        User(User&& u) noexcept : id { std::exchange(u.id, 0) },
            name { std::exchange(u.name, "") },
            lastName { std::exchange(u.lastName, "") },
            email { std::exchange(u.email, "") }
        {
            std::cout << "User::User(User&&)" << std::endl;
        }

        User& operator=(User&& u) noexcept
        {
            std::cout << "User operator=(User&& u) noexcept" << std::endl;
            //
            return *this;
        }*/

        void show() const noexcept
        {
            std::cout << "User {"
                      << "\n" << "  id        = " << id
                      << "\n" << "  name      = " << name
                      << "\n" << "  last name = " << lastName
                      << "\n" << "  email     = " << email
                      << "\n" << "}\n";
        }

        friend class UserBuilder;
    };

    class UserBuilder
    {
    private:
        User user {};

    public:

        UserBuilder& setID(ulong userID) {
            user.id = userID;
            return *this;
        }

        UserBuilder& setName(const std::string& name) {
            user.name = name;
            return *this;
        }

        UserBuilder& setLastName(const std::string& name){
            user.lastName = name;
            return *this;
        }

        UserBuilder& setEmail(const std::string& email){
            user.email = email;
            return *this;
        }

        User build() {
            return this->user;
        }
    };


    void Test_User()
    {

        User user0 = UserBuilder()
                .setID(2065).setName("John").setLastName("Von Neumman")
                .setEmail("nx098774a@sknmap.co").build();

        User user1 = UserBuilder()
                        .setID(1065).setName("Blaise")
                        .setLastName("Pascal").setEmail("dummyEmail@service1.co.uk").build();

        User user2 = UserBuilder()
                        .setID(2001).setName("Nikola")
                        .setLastName("Tesla").setEmail("wsx752@couk.com.sk").build();

        user0.show();
        user1.show();
        user2.show();
    }
};