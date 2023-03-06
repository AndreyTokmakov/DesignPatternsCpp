//============================================================================
// Name        : Builder.cpp
// Created on  : 19.04.2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Builder design pattern src
//============================================================================

#include "Builder.h"

#include <utility>

namespace Builder
{

    /** "Product" */
    class Pizza {
    private:
        std::string dough;
        std::string sauce;
        std::string topping;
        std::string name;

    public:
        virtual void setDough(std::string dough) noexcept;
        virtual void setSauce(std::string sauce) noexcept;
        virtual void setTopping(std::string topping) noexcept;

        virtual void setName(std::string name) noexcept;

        [[nodiscard]]
		virtual std::string getName() const noexcept;
    };


    /** "Abstract Builder" */
    class PizzaBuilder {
    protected:
        std::unique_ptr<Pizza> pizza;

    public:
        std::unique_ptr<Pizza> getPizza() noexcept;
        virtual void createNewPizzaProduct();

        virtual void setName() = 0;
        virtual void buildDough() = 0;
        virtual void buildSauce() = 0;
        virtual void buildTopping() = 0;
    };


    /** "HawaiianPizzaBuilder" */
    class HawaiianPizzaBuilder: public PizzaBuilder {
    public:
        void setName() override;
        void buildDough() override;
        void buildSauce() override;
        void buildTopping() override;
    };

    /** SpicyPizzaBuilder:  */
    class SpicyPizzaBuilder : public PizzaBuilder {
    public:
        virtual void setName() override;
        virtual void buildDough() override;
        virtual void buildSauce() override;
        virtual void buildTopping() override;
    };

    /** "Director" */
    class Waiter {
    private:
        std::shared_ptr<PizzaBuilder> pizzaBuilder;

    public:
        void setPizzaBuilder(std::shared_ptr<PizzaBuilder> pizzaBuilder) noexcept;
        std::unique_ptr<Pizza> getPizza() noexcept;

    public:
        void constructPizza() noexcept;
    };



	void Pizza::setName(std::string name) noexcept {
		this->name = std::move(name);
	}

	void Pizza::setDough(std::string dough) noexcept {
		this->dough = std::move(dough);
	}

	void Pizza::setSauce(std::string sauce) noexcept {
		this->sauce = std::move(sauce);
	}

	void Pizza::setTopping(std::string topping) noexcept {
		this->topping = std::move(topping);
	}

	std::string Pizza::getName() const noexcept {
		return this->name;
	}


	std::unique_ptr<Pizza> PizzaBuilder::getPizza() noexcept {
		return std::move(this->pizza);
	}

	void PizzaBuilder::createNewPizzaProduct() {
		this->pizza = std::make_unique<Pizza>();
	}



	void HawaiianPizzaBuilder::setName() {
		this->pizza->setName("HawaiianPizzaBuilder");
	}

	void HawaiianPizzaBuilder::buildDough() {
		this->pizza->setDough("cross");
	}

	void HawaiianPizzaBuilder::buildSauce() {
		this->pizza->setSauce("mild");
	}

	void HawaiianPizzaBuilder::buildTopping() {
		this->pizza->setTopping("ham + pineapple");
	}




	void SpicyPizzaBuilder::setName() {
		this->pizza->setName("SpicyPizzaBuilder");
	}

	void SpicyPizzaBuilder::buildDough() {
		this->pizza->setDough("pan baked");
	}

	void SpicyPizzaBuilder::buildSauce() {
		this->pizza->setSauce("hot");
	}

	void SpicyPizzaBuilder::buildTopping() {
		this->pizza->setTopping("pepperoni + salami");
	}



	void Waiter::setPizzaBuilder(std::shared_ptr<PizzaBuilder> pizzaBuilder) noexcept {
		this->pizzaBuilder = std::move(pizzaBuilder);
	}

	std::unique_ptr<Pizza> Waiter::getPizza() noexcept {
		return this->pizzaBuilder->getPizza();
	}

	void Waiter::constructPizza() noexcept {
		pizzaBuilder->createNewPizzaProduct();
		pizzaBuilder->setName();
		pizzaBuilder->buildDough();
		pizzaBuilder->buildSauce();
		pizzaBuilder->buildTopping();
	}

	void Test()
	{
		Waiter* waiter = new Waiter();
		{
			waiter->setPizzaBuilder(std::make_shared<HawaiianPizzaBuilder>());
			waiter->constructPizza();

			std::unique_ptr<Pizza> pizza = waiter->getPizza();
			std::cout << "Pizza: " << pizza->getName() << std::endl;
		}

		{
			waiter->setPizzaBuilder(std::make_shared<SpicyPizzaBuilder>());
			waiter->constructPizza();

			std::unique_ptr<Pizza> pizza = waiter->getPizza();
			std::cout << "Pizza: " << pizza->getName() << std::endl;
		}
	}
};