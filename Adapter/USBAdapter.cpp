//============================================================================
// Name        : USBAdapter.cpp
// Created on  : 15.08.2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Adapter src
//============================================================================

#include "Adapter.h"

namespace Adapter::USBAdapter
{

    struct USBDevice {
        virtual void connectWithUsbCable() noexcept = 0;
        virtual ~USBDevice() = default;
    };

    struct ICard {
        virtual void insert() = 0;
        virtual void copyData() = 0;
        virtual ~ICard() = default;
    };


    class MemoryCard: public ICard {
    public:
        void insert() override {
            std::cout << "Memory card inserted successfully!" << std::endl;
        }
        void copyData() override {
            std::cout << "Data has been copied to your computer!" << std::endl;
        }
    };


    class CardReader : public USBDevice {
    private:
        std::unique_ptr<ICard> card;

    public:
        explicit CardReader(std::unique_ptr<ICard> memoryCard) : card { std::move(memoryCard) } {
            // Do smth
        }
        void connectWithUsbCable() noexcept override {
            this->card->insert();
            this->card->copyData();
        }
    };
}

void Adapter::USBAdapterTest()
{
    using namespace USBAdapter;

    std::unique_ptr<ICard> card { std::make_unique<MemoryCard>() };
    std::unique_ptr<USBDevice> reader { std::make_unique<CardReader>(std::move(card)) };

    reader->connectWithUsbCable();
}
