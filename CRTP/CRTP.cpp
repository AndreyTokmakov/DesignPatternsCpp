/**============================================================================
Name        : CRTP.cpp
Created on  : 09.04.2021
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : CRTP src
============================================================================**/

#include <iostream>
#include "CRTP.h"
#include "ObjectCounter.h"


namespace CRTP {
	
	template <typename Derived>
	class Base
	{
	private:
		using underlying_type = Derived;

	protected:
		inline constexpr underlying_type& underlying() noexcept {
			return static_cast<underlying_type&>(*this);
		}

		inline constexpr const underlying_type& underlying() const noexcept {
			return static_cast<const underlying_type&>(*this);
		}

	public:
		void info() {
			underlying().info_impl();
		}

	protected:
		virtual void info_impl() = 0;
	};


	class Triangle : public Base<Triangle> {
	public:
		void info_impl() {
			std::cout << "Triangle::info_impl()\n";
		}
	};

	class Square : public Base<Square> {
	public:
		void info_impl() {
			std::cout << "Square::info_impl()\n";
		}
	};

}

void CRTP::Test()
{
	// Triangle().info();
	// Square().info();

    ObjectCounter::Test();
}