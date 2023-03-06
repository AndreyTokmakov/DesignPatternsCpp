/**============================================================================
Name        : StockVisitor.cpp
Created on  : 14.08.2020
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : StockVisitor pattern src
============================================================================**/

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Visitor.h"


namespace Visitor::StockVisitor
{

    class Stock {
    public:
        virtual void accept(std::shared_ptr<class IVisitor> visitor) = 0;
    };

    class Apple : public Stock, public std::enable_shared_from_this<Apple> {
    public:
        virtual void accept(std::shared_ptr<IVisitor> visitor) override;

        void buy() {
            std::cout << "Apple::buy" << std::endl;
        }

        void sell() {
            std::cout << "Apple::sell" << std::endl;
        }
    };

    class Google : public Stock, public std::enable_shared_from_this<Google> {
    public:
        virtual void accept(std::shared_ptr<IVisitor> visitor) override;

        void buy() {
            std::cout << "Apple::buy" << std::endl;
        }

        void sell() {
            std::cout << "Apple::sell" << std::endl;
        }
    };



    class IVisitor {
    protected:
        static inline int m_num_apple = 0;
        static inline int m_num_google = 0;

    public:
        virtual void visit(std::shared_ptr<Apple> stock) = 0;
        virtual void visit(std::shared_ptr<Google> stock) = 0;

        void total_stocks() {
            std::cout << "m_num_apple " << m_num_apple << ", m_num_google " << m_num_google << std::endl;
        }
    };

    class BuyVisitor : public IVisitor {
    public:
        BuyVisitor() {
            m_num_apple = 0;
            m_num_google = 0;
        }

        void visit(std::shared_ptr<Apple> stock) override {
            m_num_apple++;
            stock->buy();
            std::cout << "m_num_apple " << m_num_apple << std::endl;
        }

        void visit(std::shared_ptr<Google> stock) override {
            m_num_google++;
            stock->buy();
            std::cout << " m_num_google " << m_num_google << std::endl;
        }
    };

    class SellVisitor : public IVisitor {
    public:
        // SellVisitor();

        void visit(std::shared_ptr<Apple> stock) override {
            m_num_apple--;
            stock->sell();
            std::cout << "m_num_apple " << m_num_apple << std::endl;
        }

        void visit(std::shared_ptr<Google> stock) override {
            m_num_google--;
            stock->sell();
            std::cout << "m_num_google " << m_num_google << std::endl;
        }
    };

    void Google::accept(std::shared_ptr<IVisitor> visitor) {
        visitor->visit(this->shared_from_this());
    }

	void Apple::accept(std::shared_ptr<IVisitor> visitor) {
		visitor->visit(this->shared_from_this());
	}
}

void StockVisitorTest()
{
    using namespace Visitor::StockVisitor;

    std::vector<std::shared_ptr<Stock>> stocks;

    stocks.push_back(std::make_shared<Apple>());
    stocks.push_back(std::make_shared<Google>());
    stocks.push_back(std::make_shared<Google>());
    stocks.push_back(std::make_shared<Apple>());
    stocks.push_back(std::make_shared<Apple>());

    std::shared_ptr<IVisitor> buy = std::make_shared<BuyVisitor>();
    for (auto stock : stocks)
        stock->accept(buy);
    buy->total_stocks();


    std::shared_ptr<IVisitor> sell = std::make_shared<SellVisitor>();
    for (auto stock : stocks)
        stock->accept(sell);
    sell->total_stocks();

}