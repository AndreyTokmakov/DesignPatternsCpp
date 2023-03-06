//============================================================================
// Name        : Flyweight.cpp
// Created on  : 12.04.2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Flyweight pattern src
//============================================================================

#include "Flyweight.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>



namespace Flyweight::FlyweightCharacter
{
    class Character {
    public:
        char mSymbol {};
        int  mWidth {};
        int  mHeight {};
        int  mAscent {};
        int  mDescent {};
        int  mPointSize {};

    public:
        virtual ~Character() = default;
        virtual void display() const noexcept = 0;
    };


    class ConcreteCharacter : public Character {
    public:
        ConcreteCharacter(char aSymbol, int aPointSize)
        {
            mSymbol = aSymbol;
            mWidth = 120;
            mHeight = 100;
            mAscent = 70;
            mDescent = 0;
            mPointSize = aPointSize;
            std::cout << __FUNCTION__ << "[" << mSymbol << ", " << mPointSize << " ]" << std::endl;
        }

        void display() const noexcept override {
            std::cout << mSymbol << " ( PointSize " << mPointSize << " )" << std::endl;
        }
    };

    /** Flyweight factory: **/
    template <const int POINT_SIZE>
    class CharacterFactory {
    private:
        using Characters = std::unordered_map<char, std::unique_ptr<const Character>>;
        Characters mCharacters;

    public:
        const Character& getCharacter(char aKey) {
            if (const auto it = mCharacters.find(aKey); mCharacters.end() == it) {
                mCharacters[aKey] = std::make_unique<const ConcreteCharacter>(aKey, POINT_SIZE);
                return *mCharacters[aKey];
            }
            else {
                return *it->second;
            }
        }
    };


	void Test() {
		std::string document = "AAZZBBZB";

		CharacterFactory<12> characterFactory;

		for (auto it : document) {
			auto&& character = characterFactory.getCharacter(it);
			character.display();
		}
	}

}

void IconFlyweightTest();


void Flyweight::Test()
{
	// FlyweightCharacter::Test();

    IconFlyweightTest();
}
