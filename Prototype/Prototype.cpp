//============================================================================
// Name        : Prototype.cpp
// Created on  : October 26, 2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Prototype pattern test
//============================================================================

#include "Prototype.h"

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <utility>

namespace Prototype {

	enum class Type {
		PROTOTYPE_1 = 0,
		PROTOTYPE_2
	};

	struct PrototypeTypeHasher {
		std::size_t operator()(Type type) const noexcept {
			return std::hash<int>{} ( static_cast<int>(type));
		}
	};

	class Prototype {
	protected:
		std::string prototype_name_;

	public:
		Prototype() = default;

		explicit Prototype(std::string prototype_name):
                prototype_name_(std::move(prototype_name)) {
		}

		virtual ~Prototype() = default;

		[[nodiscard]]
        virtual std::unique_ptr<Prototype> Clone() const noexcept = 0;

		virtual void Info() const noexcept = 0;
	};

	/*
	struct PrototypeHash {
		std::size_t operator()(const Prototype& s) const noexcept {
			return std::hash<int>{}(s.prototype_field_) +
				std::hash<std::string>{}(s.prototype_name_);
		}
	};
	*/

	class ConcretePrototype1 : public Prototype {
	public:
		explicit ConcretePrototype1(std::string prototype_name):
                Prototype(std::move(prototype_name)) {
			std::cout << "Creating ConcretePrototype1(" << prototype_name_ << ")" << std::endl;
		}

		[[nodiscard]]
        std::unique_ptr<Prototype> Clone() const noexcept override {
			return std::make_unique<ConcretePrototype1>(this->prototype_name_);
		}

		void Info() const noexcept override {
			std::cout << "ConcretePrototype1::Info(): " << prototype_name_ << "\n";
		}
	};

	class ConcretePrototype2 : public Prototype {
	private:
		int concrete_prototype_field { 0 };

	public:
		explicit ConcretePrototype2(std::string prototype_name)
			: Prototype(std::move(prototype_name)) {
			std::cout << "Creating ConcretePrototype2(" << prototype_name_ << ")" << std::endl;
		}

		[[nodiscard]]
        std::unique_ptr<Prototype> Clone() const noexcept override {
			return std::make_unique<ConcretePrototype2>(this->prototype_name_);
		}

		void Info() const noexcept override {
			std::cout << "ConcretePrototype2::Info(): " << prototype_name_ << "\n";
		}
	};


	/**
	 * In PrototypeFactory you have two concrete prototypes, one for each concrete
	 * prototype class, so each time you want to create a bullet , you can use the
	 * existing ones and clone those.
	 */
	class PrototypeFactory {
	private:
		std::unordered_map<Type, std::unique_ptr<Prototype>, PrototypeTypeHasher> prototypes_;

	public:
		PrototypeFactory() {
			prototypes_[Type::PROTOTYPE_1] = std::make_unique<ConcretePrototype1>("PROTOTYPE_1");
			prototypes_[Type::PROTOTYPE_2] = std::make_unique<ConcretePrototype2>("PROTOTYPE_2");
		}

		/**
		 * Be carefull of free all memory allocated. Again, if you have smart pointers
		 * knowelege will be better to use it here.
		 */
		~PrototypeFactory()  = default;

		/**
		 * Notice here that you just need to specify the type of the prototype you
		 * want and the method will create from the object with this type.
		 */
		std::unique_ptr<Prototype> CreatePrototype(Type type) {
			return prototypes_[type]->Clone();
		}
	};

	void Client(PrototypeFactory* prototype_factory) {
		std::cout << "Let's create a Prototype 1\n";
		
		auto prototype = prototype_factory->CreatePrototype(Type::PROTOTYPE_1);
		prototype->Info();

		std::cout << "\nLet's create a Prototype 2 \n";

		prototype = prototype_factory->CreatePrototype(Type::PROTOTYPE_2);
		prototype->Info();
	}

	void Test1() {
		std::unique_ptr<PrototypeFactory> prototype_factory = std::make_unique<PrototypeFactory>();
		Client(prototype_factory.get());
	}
};

void Prototype::Test() {

	Test1();
}