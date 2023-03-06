//============================================================================
// Name        : ObjectPools.cpp
// Created on  : 29.06.2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Object pools pattern src
//============================================================================

#include "ObjectPools.h"

#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <vector>

namespace ObjectPools {

	class Resource {
	private:
		std::string name {};

	public:
		Resource() = default;

		explicit Resource(std::string name): name(std::move(name)) {
		}

		virtual ~Resource() = default;

		void reset() noexcept  {
			this->name.clear();
		}

		[[nodiscard]]
        const std::string& getValue() const noexcept {
			return this->name;
		}

		void setName(const std::string& name) noexcept {
			this->name = name;
		}

		friend std::ostream& operator<<(std::ostream& os, const Resource& res); 
	};

	std::ostream& operator<<(std::ostream& os, const Resource& res) {
		os << res.name;
		return os;
	}


	/* Note, that this class is a singleton. */
	class ObjectPool final {
	private:
		static ObjectPool* instance;

	private:
		std::vector<std::shared_ptr<Resource>> resources;

		ObjectPool() = default;
		
	public:
		ObjectPool(const ObjectPool& obj) = delete;

		static ObjectPool* getInstance() {
			if (nullptr == instance) {
				instance = new ObjectPool;
			}
			return instance;
		}

		std::shared_ptr<Resource> getResource() {
			if (resources.empty()) {
				std::cout << "Creating new." << std::endl;
				return std::make_shared<Resource>();
			}
			
			std::cout << "Reusing existing." << std::endl;
			std::shared_ptr<Resource> resource = resources.back();
			resources.pop_back();
			return resource;
		}

		void returnResource(const std::shared_ptr<Resource>& resource) {
			resource->reset();
			resources.push_back(resource);
		}
	};

	ObjectPool* ObjectPool::instance = nullptr;

	void SimpleTest()
	{
	
		ObjectPool* pool = ObjectPool::getInstance();
		std::shared_ptr<Resource> one, two;

		one = pool->getResource();
		one->setName("1111");
		std::cout << "one = " << one->getValue() << " [" << one << "]" << std::endl;
		two = pool->getResource();
		two->setName("22222");
		std::cout << "two = " << two->getValue() << " [" << two << "]" << std::endl;
		pool->returnResource(one);
		pool->returnResource(two);


		one = pool->getResource();
		std::cout << "one = " << one->getValue() << " [" << one << "]" << std::endl;
		two = pool->getResource();
		std::cout << "two = " << two->getValue() << " [" << two << "]" << std::endl;
	}
};