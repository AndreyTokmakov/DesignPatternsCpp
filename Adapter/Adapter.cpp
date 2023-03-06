#//============================================================================
// Name        : Adapter.h
// Created on  : 07.07.2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Adapter src
//============================================================================

#include "Adapter.h"

#define interface class

namespace Adapter::Classic {
	
	// Existing environmental temperature sensor class
	struct FahrenheitSensor final
    {
		// Get temperature in degrees Fahrenheit
		float getTemp() {
			float t = 112.0;
			// Some code
			return t;
		}
	};


	interface ISensor {
	public:
		virtual ~ISensor() = default;
		virtual float getTemperature() = 0;
	};


	class Adapter : public ISensor {
	private:
		std::unique_ptr<FahrenheitSensor> sensor;

	public:
		explicit Adapter(std::unique_ptr<FahrenheitSensor> fSensor) : sensor { std::move(fSensor) } {
		}

		~Adapter() override = default;

        float getTemperature() override {
			return (sensor->getTemp() - 32.0f) * 5.0f / 9.0f;
		}
	};


	void Test() {
		std::unique_ptr<FahrenheitSensor> someRealSensor = std::make_unique<FahrenheitSensor>();
        std::cout << "Fahrenheit temperature = " << someRealSensor->getTemp() << std::endl;

		std::shared_ptr<ISensor> sensor = std::make_shared<Adapter>(std::move(someRealSensor));
		std::cout << "Celsius temperature = " << sensor->getTemperature() << std::endl;
	}
}

namespace Adapter::PrivateInheritance {

	// Existing environmental temperature sensor class
	class FahrenheitSensor {
	private:
		float t = 112.0;

	public:
		// Get temperature in degrees Fahrenheit
		float getFahrenheitTemp() {
			// Some code
			return t;
		}

	protected:
		void adjust(float t) { // Sensor setup (protected method)
			this->t = t;
		}
	};

	interface ISensor {
	public:
		virtual ~ISensor() = default;
		virtual float getTemperature() = 0;
		virtual void adjust(float t) = 0;
	};

	class Adapter : public ISensor, private FahrenheitSensor {
	public:
		Adapter()  = default;

		~Adapter() override = default;

	public:
		float getTemperature() override {
			return (getFahrenheitTemp() - 32.0f)*5.0f / 9.0f;
		}

		void adjust(float t) override {
			FahrenheitSensor::adjust(t);
		}
	};

	void Test() {
		std::shared_ptr<ISensor> sensor = std::make_shared<Adapter>();

		std::cout << "Celsius temperature = " << sensor->getTemperature() << std::endl;
		sensor->adjust(133);
		std::cout << "Celsius temperature = " << sensor->getTemperature() << std::endl;
	}
}

void BaseAdapterTest(); // from BaseAdapter.cpp file
void GoodExample_Test(); // from GoodExample.cpp file


void Adapter::TestAll()
{
    // Classic::Test();
    // USBAdapterTest();
	// PrivateInheritance::Test();

    // BaseAdapterTest();

    GoodExample_Test();
}
