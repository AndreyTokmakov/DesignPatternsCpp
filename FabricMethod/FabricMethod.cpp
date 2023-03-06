#include "FabricMethod.h"

namespace FabricMethod {

    class IProduct {
    public:
        IProduct() = default;
        virtual ~IProduct() = default;

        virtual std::string getName() = 0;
    };


    class ICreator {
    public:
        virtual std::unique_ptr<IProduct> factoryMethod() = 0;
    };


    class ProductA : public IProduct {
    public:
        ProductA() = default;

        std::string getName() final {
            return "ProductA";
        }
    };


    class ProductB : public IProduct {
    public:
        ProductB() = default;

        std::string getName() final {
            return "ProductB";
        }
    };


    class FabricOne : public ICreator {
    public:
        std::unique_ptr<IProduct> factoryMethod() final {
            return std::make_unique<ProductA>();
        }
    };


    class FabricTwo : public ICreator {
    public:
        std::unique_ptr<IProduct> factoryMethod() final {
            return std::make_unique<ProductB>();
        }
    };


	void Test1() {
        FabricOne one;
        FabricTwo two;
		ICreator* creators[] = {&one, &two};

		for (auto&& creator : creators) {
			std::unique_ptr<IProduct> product = creator->factoryMethod();
			std::cout << "New product: " <<  product->getName() << std::endl;
		}
	}

    // from FabricMethod2
    void Test2();

    void TestAll()
    {
        // Test1();
        Test2();
    }
}
