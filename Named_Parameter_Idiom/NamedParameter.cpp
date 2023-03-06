//============================================================================
// Name        : NamedParameter.h
// Created on  : February 21, 2021
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Named parameters idiom/pattern
//============================================================================

#include "NamedParameter.h"

#include <iostream>
#include <string>

namespace NamedParameter {
	
	class Employee final {
	private:
		std::string firstName {"Jonh"};
		std::string secondsName {"Dow"};
		unsigned int id { 0 };

	private:
		Employee() {
			std::cout << "Employee (" << id << ", " << firstName << ", " << secondsName << ")\n";
		}
		Employee(std::string&& name, std::string&& secName, unsigned int n) :
				firstName{std::move(name)},secondsName{ std::move(secName )}, id{ std::move(n)} {
			std::cout << "Employee (" << id << ", " << firstName << ", " << secondsName << ")\n";
		}

	public:
		Employee(const Employee& obj): firstName{ obj.firstName },
				secondsName{ obj.secondsName }, id{ obj.id } {
			std::cout << "Employee (" << id << ", " << firstName << ", " << secondsName << ") Copy constructor\n";
		}

		Employee& operator=(const Employee& obj) {
			if (this == &obj) {
				return *this;
			}
			firstName.assign(obj.firstName);
			secondsName.assign(obj.secondsName);
			id = obj.id;
			return *this;
		}

		//Employee(Employee&& obj) noexcept = delete;
		//Employee& operator=(Employee&& obj) noexcept = delete;

	public:
		static Employee build() {
			return Employee{};
		}

		Employee& setFirstName(std::string&& name) {
			firstName.assign(std::move(name));
			return *this;
		}

		Employee& setSecondName(std::string&& name) {
			secondsName.assign(std::move(name));
			return *this;
		}

		Employee& setId(unsigned int id) {
			this->id = id;
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& stream, const Employee& empl);
		friend Employee create();
	};

	std::ostream& operator<<(std::ostream& stream, const Employee& empl) {
		stream << "Employee [id = " << empl.id << ", " << empl.firstName << ", " << empl.secondsName << "]\n";
		return stream;
	}

	Employee create() {
		return Employee{"Max", "Pain" , 123};
	}


	//-----------------------------------------------------//

	void Test1() {
		Employee empl = Employee::build()
			.setFirstName("Max")
			.setSecondName("Pain")
			.setId(123);
		std::cout << empl << std::endl;
	}

	void Test2() {
		Employee empl = create();
		std::cout << empl << std::endl;
	}
}

void NamedParameter::Test() {
	Test1();
	Test2();
}