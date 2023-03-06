#include "AbstractFactory.h"

namespace AbstractFactory
{

    class IProduct {
    public:
        [[nodiscard]]
        virtual std::string getName() const noexcept = 0;

        virtual ~IProduct() = default;
    };

    class IAbstractProductA: public IProduct  {
    public:
        virtual void interact(std::shared_ptr<class IAbstractProductB> b) = 0;

        [[nodiscard]]
        std::string getName() const noexcept override = 0;
    };

    class IAbstractProductB: public IProduct {
    public:
        virtual void interact(std::shared_ptr<class IAbstractProductA> a) = 0;

        [[nodiscard]]
        std::string getName() const noexcept override = 0;
    };



    class IAbstractFactory {
    public:
        [[nodiscard]]
        virtual std::shared_ptr<IAbstractProductA> createProductA() = 0;

        [[nodiscard]]
        virtual std::shared_ptr<IAbstractProductB> createProductB() = 0;

        virtual ~IAbstractFactory() = default;
    };



    class ProductA1 : public IAbstractProductA {
    public:
        void interact(std::shared_ptr<IAbstractProductB> product) override {
            std::cout << this->getName() << " interacts with " << product->getName() << std::endl;
        }

        [[nodiscard]]
        std::string getName() const noexcept override {
            return "ProductA1";
        }
    };

    class ProductB1 : public IAbstractProductB {
    public:
        void interact(std::shared_ptr<IAbstractProductA> product) override {
            std::cout << this->getName() << " interacts with " << product->getName() << std::endl;
        }

        [[nodiscard]]
        std::string getName() const noexcept override {
            return "ProductB1";
        }
    };

    class ConcreteFactory1: public IAbstractFactory {
    public:
        [[nodiscard]]
        std::shared_ptr<IAbstractProductA> createProductA() override {
            return std::make_shared<ProductA1>();
        }

        [[nodiscard]]
        std::shared_ptr<IAbstractProductB> createProductB() override {
            return std::make_shared<ProductB1>();
        }
    };



    class ProductA2 : public IAbstractProductA {
    public:
        void interact(std::shared_ptr<IAbstractProductB> product) override {
            std::cout << this->getName() << " interacts with " << product->getName() << std::endl;
        }

        [[nodiscard]]
        std::string getName() const noexcept override {
            return "ProductA2";
        }
    };

    class ProductB2 : public IAbstractProductB {
    public:
        void interact(std::shared_ptr<IAbstractProductA> product) override {
            std::cout << this->getName() << " interacts with " << product->getName() << std::endl;
        }

        [[nodiscard]]
        std::string getName() const noexcept override {
            return "ProductB2";
        }
    };


    class ConcreteFactory2 : public IAbstractFactory {
    public:
        [[nodiscard]]
        std::shared_ptr<IAbstractProductA> createProductA() override {
            return std::make_shared<ProductA2>();
        }

        [[nodiscard]]
        std::shared_ptr<IAbstractProductB> createProductB() override {
            return std::make_shared<ProductB2>();
        }
    };




    class Client {
    private:
        std::shared_ptr<IAbstractProductA> productA;
        std::shared_ptr<IAbstractProductB> productB;

    public:
        explicit Client(std::shared_ptr<IAbstractFactory> factory);

    public:
        virtual void execute();
    };

	Client::Client(std::shared_ptr<IAbstractFactory> factory) {
		productA = factory->createProductA();
		productB = factory->createProductB();
	}

	void Client::execute() {
		this->productB->interact(this->productA);
	}

	void Test()
	{
		std::shared_ptr<Client> client1 = std::make_shared<Client>(std::make_shared<ConcreteFactory1>());
		client1->execute();
	
		std::shared_ptr<Client> client2 = std::make_shared<Client>(std::make_shared<ConcreteFactory2>());
		client2->execute();
	}

}