//============================================================================
// Name        : Filter.cpp
// Created on  : 13.08.2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Filter pattern src
//============================================================================

#include "Filter.h"

#include <utility>



namespace Filter {

    /** Person class: **/
    class Person {
    private:
        std::string name;
        std::string gender;
        std::string maritalStatus;

    public:
        Person(std::string name, std::string gender, std::string maritalStatus):
                name (std::move(name)), gender (std::move(gender)), maritalStatus (std::move(maritalStatus)) {
        }

        [[nodiscard]]
        inline const std::string& getName() const noexcept {
            return name;
        }

        [[nodiscard]]
        inline const std::string& getGender() const noexcept {
            return gender;
        }

        [[nodiscard]]
        inline const std::string& getMaritalStatus() const noexcept  {
            return maritalStatus;
        }

        friend std::ostream& operator<<(std::ostream& stream, const Person& person);
    };


    /** Criteria interface: **/
    class Criteria: public std::enable_shared_from_this<Criteria> {
    public:
        virtual std::vector<Person> meetCriteria(const std::vector<Person>& persons) = 0;

        std::shared_ptr<class AND_Criteria> operator&&(const std::shared_ptr<Criteria>& other) {
            return std::make_shared<AND_Criteria>( shared_from_this(), other);
        }

        virtual ~Criteria() = default;
    };


    /** CriteriaMale. **/
    class CriteriaMale: public Criteria {
    public:
        std::vector<Person> meetCriteria(const std::vector<Person>& persons) override
        {
            std::vector<Person> result;
            result.reserve(persons.size());
            std::for_each(persons.cbegin(), persons.cend(), [&](const Person& P) {
                if (0 == P.getGender().compare("Male"))
                    result.push_back(P);
            });
            result.shrink_to_fit();
            return result;
        }
    };

    /** CriteriaFemale. **/
    class CriteriaFemale: public Criteria {
    public:
        std::vector<Person> meetCriteria(const std::vector<Person> &persons) override
        {
            std::vector<Person> result;
            result.reserve(persons.size());
            std::for_each(persons.cbegin(), persons.cend(), [&](const Person& P) {
                if (0 == P.getGender().compare("Female"))
                    result.push_back(P);
            });
            result.shrink_to_fit();
            return result;
        }
    };

    /** CriteriaSingle. **/
    class CriteriaSingle: public Criteria {
    public:
        std::vector<Person> meetCriteria(const std::vector<Person>& persons) override
        {
            std::vector<Person> result;
            result.reserve(persons.size());
            std::for_each(persons.cbegin(), persons.cend(), [&](const Person& P) {
                if (0 == P.getMaritalStatus().compare("Single"))
                    result.push_back(P);
            });
            result.shrink_to_fit();
            return result;
        }
    };

    /** AND_Criteria. **/
    class AND_Criteria: public Criteria {
    protected:
        std::shared_ptr<Criteria> criteriaFirst;
        std::shared_ptr<Criteria> criteriaSecond;

    public:
        AND_Criteria(std::shared_ptr<Criteria> first,
                     std::shared_ptr<Criteria> second);

    public:
        std::vector<Person> meetCriteria(const std::vector<Person>& persons) override;
    };


    /** OR_Criteria. **/
    class OR_Criteria : public Criteria {
    protected:
        std::shared_ptr<Criteria> criteriaFirst;
        std::shared_ptr<Criteria> criteriaSecond;

    public:
        OR_Criteria(std::shared_ptr<Criteria> first,
                    std::shared_ptr<Criteria> second);

    public:
        std::vector<Person> meetCriteria(const std::vector<Person>& persons) override;
    };
};

namespace Filter {

	std::ostream& operator<<(std::ostream& stream, const Person& person) {
		stream << "Name: " << person.name << ", Gender: " << person.gender << ", Status: " << person.maritalStatus;
		return stream;
	}




	AND_Criteria::AND_Criteria(std::shared_ptr<Criteria> first,
		                       std::shared_ptr<Criteria> second):
                               criteriaFirst(std::move(first)), criteriaSecond(std::move(second)) {
	}

	std::vector<Person> AND_Criteria::meetCriteria(const std::vector<Person>& persons)
	{
		std::vector<Person> result = this->criteriaFirst->meetCriteria(persons);
		return criteriaSecond->meetCriteria(result);
	}


	OR_Criteria::OR_Criteria(std::shared_ptr<Criteria> first,
					         std::shared_ptr<Criteria> second) :
                             criteriaFirst(std::move(first)), criteriaSecond(std::move(second)) {
	}

	std::vector<Person> OR_Criteria::meetCriteria(const std::vector<Person>& persons)
	{
		std::vector<Person> items1 = this->criteriaFirst->meetCriteria(persons);
		std::vector<Person> items2 = this->criteriaSecond->meetCriteria(persons);
		// TODO: Fix
		throw std::runtime_error("Method unimplemented");
		return items1;
	}

	// Print util:
	void printPersons(const std::string& text, const std::vector<Person>& persons) {
		std::cout << text << std::endl;
		for (const auto& P : persons)
			std::cout << P << std::endl;
	}
}

namespace Filter
{

    std::vector<Person> getTestData()
    {
        std::vector<Person> persons;

        persons.emplace_back("Robert", "Male", "Single");
        persons.emplace_back("John", "Male", "Married");
        persons.emplace_back("Laura", "Female", "Married");
        persons.emplace_back("Diana", "Female", "Single");
        persons.emplace_back("Mike", "Male", "Single");
        persons.emplace_back("Bobby", "Male", "Single");

        return persons;
    }

    void Test_MaleFilter()
    {
        const std::vector<Person> persons  { getTestData() };
        const auto result = CriteriaMale{}.meetCriteria(persons);

        printPersons("Males: ", result);
    }

    void Test_FemaleFilter()
    {
        const std::vector<Person> persons  { getTestData() };
        const auto result = CriteriaFemale{}.meetCriteria(persons);

        printPersons("Females: ", result);
    }

    void Test1()
    {
        const std::vector<Person> persons  { getTestData() };

        std::shared_ptr<Criteria> male = std::make_shared<CriteriaMale>();
        std::shared_ptr<Criteria> female = std::make_shared<CriteriaFemale>();
        std::shared_ptr<Criteria> single = std::make_shared<CriteriaSingle>();
        std::shared_ptr<Criteria> singleMale = std::make_shared<AND_Criteria>(single, male);
        std::shared_ptr<Criteria> singleOrFemale = std::make_shared<OR_Criteria>(single, female);

        printPersons("Males: ", male->meetCriteria(persons));
        printPersons("\nFemales: ", female->meetCriteria(persons));
        printPersons("\nSingle: ", singleMale->meetCriteria(persons));

        printPersons("\nSingle Males: ", singleMale->meetCriteria(persons));
        // printPersons("\nSingle or FeMales: ", singleOrFemale->meetCriteria(persons));
    }

    void Test2()
    {
        const std::vector<Person> persons  { getTestData() };
        std::shared_ptr<Criteria> male = std::make_shared<CriteriaMale>();
        std::shared_ptr<Criteria> single = std::make_shared<CriteriaSingle>();

        std::shared_ptr<AND_Criteria> singleMan = *(male) && single;

        printPersons("Males: ", singleMan->meetCriteria(persons));
    }
}

void Filter::Test()
{
    Test_MaleFilter();
    Test_FemaleFilter();

    // Test1();
    // Test2();
}
