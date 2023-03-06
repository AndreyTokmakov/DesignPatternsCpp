//============================================================================
// Name        : ChainOfResponsibility.cpp
// Created on  : 19.04.2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Chain of pesponsibility pattern src
//============================================================================

#include "ChainOfResponsibility.h"

#include <utility>

namespace ChainOfResponsibility
{
    using String = std::string;
    using CString = const String&;

    /** Criminal action class: **/
    class CriminalAction {
    private:
        friend class Policeman;

        /** Case complexity: **/
        int complexity;

        /** Case brif description: **/
        String description;

    public:
        CriminalAction(int complexity, std::string  description) :
                complexity(complexity), description(std::move(description)) {
        }

        virtual ~CriminalAction() = default;
    };



    /** Abstract policeman who can investigate crimes. **/
    class Policeman {
    protected:
        /** Deduction (the ability to unravel complex cases) with this police officer. **/
        int deduction;

        /** a more skilled policeman who will receive a case if it is too complicated for the current one. **/
        std::shared_ptr<Policeman> next;

        /** The investigation. **/
        virtual void investigateConcrete(CString description) = 0;

    public:
        explicit Policeman(int deduction): deduction(deduction), next(nullptr) {
        }

        ~Policeman() {
            // delete next;
            // std::cout << __FUNCTION__ << " " << typeid(*this).name() <<  std::endl;
        }

        // Adds to the chain of responsibility a more experienced policeman who can take over investigation if the current fails
        std::shared_ptr<Policeman> setNext(std::shared_ptr<Policeman> policeman) {
            next = policeman;
            return next;
        }

        // A policeman begins an investigation or, if the case is too complicated, passes it to a more experienced colleague
        void investigate(const std::shared_ptr<CriminalAction>& criminalAction) {
            if (deduction < criminalAction->complexity) {
                if (next) {
                    next->investigate(criminalAction);
                }
                else {
                    std::cout << "This case is not disclosed to anyone." << std::endl;
                }
            }
            else {
                investigateConcrete(criminalAction->description);
            }
        }
    };


    /** Martin Riggs the Policeman. **/
    class MartinRiggs : public Policeman {
    protected:
        void investigateConcrete(const std::string& description) override {
            std::cout << "Case investigation '" << description << "' leads Sergeant Martin Riggs" << std::endl;
        }
    public:
        explicit MartinRiggs(int deduction) : Policeman(deduction) {
        }
    };


    /** John McClane the Policeman. **/
    class JohnMcClane : public Policeman {
    protected:
        void investigateConcrete(const std::string& description) override {
            std::cout << "Case investigation '" << description << "' leads Detective John McClanes" << std::endl;
        }
    public:
        explicit JohnMcClane(int deduction) : Policeman(deduction) {
        }
    };

    /** Vincent Hanna the Policeman. **/
    class VincentHanna : public Policeman {
    protected:
        void investigateConcrete(const std::string&  description) override {
            std::cout << "Case investigation '" << description << "' leads Lieutenant Vincent Hanna" << std::endl;
        }
    public:

        explicit VincentHanna(int deduction) : Policeman(deduction) {
        }
    };



	void Test()
	{
		std::shared_ptr<Policeman> policeman = std::make_shared<MartinRiggs>(3);
		policeman->setNext(std::make_shared<JohnMcClane>(5))
                  ->setNext(std::make_shared<VincentHanna>(8));
		policeman->investigate(std::make_shared<CriminalAction>(2, "Drug trade from Vietnam"));
		policeman->investigate(std::make_shared<CriminalAction>(7, "Cheeky bank robbery in downtown Los Angeles"));
		policeman->investigate(std::make_shared<CriminalAction>(5, "A series of explosions in downtown New York"));
	}

    void TestAll()
    {
        // Test();
        Example2_Test();
    }
}