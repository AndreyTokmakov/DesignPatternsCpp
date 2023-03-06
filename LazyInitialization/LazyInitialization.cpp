/**============================================================================
Name        : LazyInitialization.cpp
Created on  : 01.01.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : LazyInitialization
============================================================================**/

#include "LazyInitialization.h"

#include <iostream>
#include <memory>
#include <unordered_map>

namespace LazyInitialization
{
    class Fruit {
    public:
        static std::weak_ptr<Fruit> GetFruit(std::string_view type) {
            const auto [it, inserted] = types.emplace(type, nullptr);
            if (inserted) {
                it->second = std::shared_ptr<Fruit>(new Fruit(type));
            }
            return it->second;

            // return types.emplace(type, type).first->second;
        }

        static void PrintCurrentTypes() noexcept {
            std::cout << "Fruits count: " << types.size() << ", { ";
            for (const auto& [type, fruit] : types)
                std::cout << type << ' ';
            std::cout << "}\n";
        }

    private:
        explicit Fruit(std::string_view type) : type(type) {
        }

        static inline std::unordered_map<std::string, std::shared_ptr<Fruit>> types;

        std::string type {};
    };
}

void LazyInitialization::TestAll()
{
    Fruit::GetFruit("Banana");
    Fruit::PrintCurrentTypes();

    Fruit::GetFruit("Apple");
    Fruit::PrintCurrentTypes();

    // Returns pre-existing instance from first time |Fruit| with "Banana" was
    // created.
    Fruit::GetFruit("Banana");
    Fruit::PrintCurrentTypes();
}