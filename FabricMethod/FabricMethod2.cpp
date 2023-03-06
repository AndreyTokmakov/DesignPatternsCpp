#include "FabricMethod.h"

#include <memory>

namespace FabricMethod
{
    struct Product {
        virtual ~Product() = default;

        [[nodiscard]]
        virtual std::string Operation() const = 0;
    };


    class ConcreteProductOne : public Product {
    public:
        [[nodiscard]]
        std::string Operation() const override {
            return "{ ConcreteProductOne::Operation() }";
        }
    };

    class ConcreteProductTwo : public Product {
    public:
        [[nodiscard]]
        std::string Operation() const override {
            return "{ ConcreteProductTwo::Operation() }";
        }
    };


    struct Creator
    {
        virtual ~Creator() = default;

        [[nodiscard]]
        virtual std::unique_ptr<Product> FactoryMethod() const = 0;

        /**
         * Also note that, despite its name, the Creator's primary responsibility is not creating products.
         * Usually, it contains some core business logic that relies on Product objects, returned by the factory method.
         * Subclasses can indirectly change that business logic by overriding the factory method and returning a
         * different type of product from it.
         */

        [[nodiscard]]
        std::string SomeOperation() const {
            std::unique_ptr<Product> product = FactoryMethod();
            return std::string {"Creator: "}.append(product->Operation());
        }
    };

    struct ConcreteCreator1 : Creator
    {    /**
         * Note that the signature of the method still uses the abstract product type,
         * even though the concrete product is actually returned from the method. This
         * way the Creator can stay independent of concrete product classes.
         */
        [[nodiscard]]
        std::unique_ptr<Product> FactoryMethod() const override {
            return std::make_unique<ConcreteProductOne>();
        }
    };


    struct ConcreteCreator2:  Creator
    {
        [[nodiscard]]
        std::unique_ptr<Product> FactoryMethod() const override {
            return std::make_unique<ConcreteProductTwo>();
        }
    };

    void ClientCode(const Creator* creator)
    {
        std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
                  << creator->SomeOperation() << std::endl << std::endl;
    }

    void Test2()
    {
        std::cout << "App: Launched with the ConcreteCreator1.\n";
        std::unique_ptr<Creator> creator { std::make_unique<ConcreteCreator1>()};
        ClientCode(creator.get());

        std::cout << "App: Launched with the ConcreteCreator2.\n";
        creator =  std::make_unique<ConcreteCreator2>();
        ClientCode(creator.get());
    }
}
