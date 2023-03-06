/**============================================================================
Name        : TemplateMethod.h
Created on  : 01.12.2022
Author      : Tokmakov Andrei
Version     : 1.0
Copyright   : Your copyright notice
Description : TemplateMethod
============================================================================**/

#include "TemplateMethod.h"

#include <iostream>

namespace TemplateMethod::Game
{
    struct Game
    {
        explicit Game(uint32_t players): m_no_of_players { players}  {
        }

        /** Template method. **/
        void run()
        {
            start();
            while (!have_winner())
                take_turn();
            std::cout << "Player " << get_winner() << " wins.\n";
        }

    protected:
        virtual void start() = 0;
        virtual bool have_winner() = 0;
        virtual void take_turn() = 0;
        virtual uint32_t get_winner() = 0;

        uint32_t m_current_player{0};
        uint32_t m_no_of_players{0};
    };

    struct Chess : Game
    {
        explicit Chess(): Game {2} {
        }
    protected:
        void start() override {
            std::cout << "Starting chess with " << m_no_of_players << " players\n";
        }

        bool have_winner() override {
            return m_turns == m_max_turns;
        }

        void take_turn() override {
            std::cout << "Turn " << m_turns << " taken by player " << m_current_player << "\n";
            m_turns++;
            m_current_player = (m_current_player + 1) % m_no_of_players;
        }

        uint32_t get_winner() override {
            return m_current_player;
        }
    private:
        uint32_t m_turns{0}, m_max_turns{4};
    };

    void Test()
    {
        Chess chess;
        chess.run();
    }
};

void TemplateMethod_ExampleTwo_Test();
void TemplateMethod_ExampleThree_Test();

void TemplateMethod::TestAll()
{
    // Game::Test();

    // TemplateMethod_ExampleTwo_Test();

    TemplateMethod_ExampleThree_Test();
};
