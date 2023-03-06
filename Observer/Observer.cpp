/**============================================================================
Name        : Observer.h
Created on  : August 14, 2020
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Observer pattern test
============================================================================**/

#include "Observer.h"

#include <utility>
#include <algorithm>
#include <list>
#include <iostream>
#include <string_view>
#include <memory>

namespace Observer::Test1 {

    class SupervisedString;

    class IObserver
    {
    public:
        virtual void handleEvent(const SupervisedString&) = 0;
        virtual ~IObserver() = default;
    };

    // Observable class
    class SupervisedString {
    private:
        std::string str {};
        std::list<IObserver*> observers;

    private:
        void Notify() {
            for (auto& observer : observers) {
                observer->handleEvent(*this);
            }
        }

    public:
        void add(IObserver& ref) {
            observers.push_back(&ref);
        }

        void remove(IObserver& ref) {
            observers.remove(&ref);
        }

        [[nodiscard]]
        const std::string& get() const {
            return str;
        }

        void reset(std::string s) {
            this->str = std::move(s);
            Notify();
        }
    };


    // Prints the observed string into cout
    class Reflector : public IObserver {
    public:
        void handleEvent(const SupervisedString& ref) override {
            std::cout << "Reflector: " << ref.get() << std::endl;
        }
    };

    // Prints the length of observed string into cout
    class Counter : public IObserver {
    public:
        void handleEvent(const SupervisedString& ref) override {
            std::cout << "Counter: length = " << ref.get().length() << std::endl;
        }
    };

    void Test()
    {
        SupervisedString supervisedString;
        Reflector refl;
        Counter cnt;

        supervisedString.add(refl);
        supervisedString.reset("Hello, World!");
        std::cout << std::endl;

        supervisedString.reset("Hello, World 123");
        std::cout << std::endl;

        supervisedString.remove(refl);
        supervisedString.add(cnt);
        supervisedString.reset("World, Hello!");
    }
}

namespace Observer::Test2
{

    /*
    template<class T>
    class IObserver {
    public:
        virtual void Update(const T&) = 0;
        virtual ~IObserver() = default;
    };

    template<class T>
    class IObservable {
    public:
        virtual void addObserver(std::shared_ptr<T> observer) = 0;
        virtual void deleteObserver(const std::shared_ptr<T>& observer) = 0;

        virtual ~IObservable() = default;
    };

    template<class T>
    class TestObserver : public IObserver<T> {
        virtual void Update(const T& params ) override {
            std::cout << params << std::endl;
        }
    };

    template<class T = std::string>
    class Worker : public IObservable<T> {
    protected:
        std::vector<std::shared_ptr<TestObserver<T>>> observers;

    public:
        virtual void addObserver(std::shared_ptr<TestObserver<T>> observer) override {
            this->observers.push_back(observer);
        }
    };

    */

    class IObserver {
    public:
        virtual void Update(const std::string& params) = 0;
        virtual ~IObserver() = default;
    };

    class IObservable {
    public:
        virtual void addObserver(std::shared_ptr<IObserver> observer) = 0;
        virtual void deleteObserver(const std::shared_ptr<IObserver>& observer) = 0;
        virtual ~IObservable() = default;
    };


    class TestObserver : public IObserver {
        void Update(const std::string& params) override {
            std::cout <<  params << std::endl;
        }
    };

#define USE_VECTOR

    class Worker : public IObservable
    {
    protected:
#ifdef USE_VECTOR
        std::vector<std::shared_ptr<IObserver>> observers;
#elif
        std::list<std::shared_ptr<IObserver>> observers;
#endif

    public:
        void addObserver(std::shared_ptr<IObserver> observer) override {
            this->observers.push_back(observer);
        }

        /*
        template<typename ... T>
        decltype(auto) emplacedObserver(T&& ... params) {
            return this->observers.emplace_back(std::forward<T>(params)...);
        }
        */

#ifdef USE_VECTOR
        void deleteObserver(const std::shared_ptr<IObserver>& observer) override
        {
            std::cout << "Observers count: " << observers.size() << std::endl;

            auto iter = remove_if(observers.begin(), observers.end(), [&observer](const auto& ptr) {
                return (ptr.get() == observer.get());
            });
            observers.erase(iter, observers.end());

            std::cout << "Observers count: " << observers.size() << std::endl;
        }
#elif

        void deleteObserver(const std::shared_ptr<IObserver>& observer) override
        {
            std::cout << "Observers count: " << observers.size() << std::endl;
            observers.remove(observer);
            std::cout << "Observers count: " << observers.size() << std::endl;
        }
#endif

        void NotifyObservers(const std::string& str) {
            for (auto& observer : this->observers)
                observer->Update(str);
        }

        void SendMessage(const std::string& str) {
            NotifyObservers(str);
        }
    };


    void Test()
    {
        Worker worker;
        worker.addObserver(std::make_shared<TestObserver>());
        worker.addObserver(std::make_shared<TestObserver>());

        std::shared_ptr<IObserver> observer2 = std::make_shared<TestObserver>();
        worker.addObserver(observer2);


        // std::shared_ptr<IObserver> observer2 = worker.emplacedObserver();
        // std::shared_ptr<IObserver> observer3 = worker.emplacedObserver();

        worker.SendMessage("Message 1");

        worker.deleteObserver(observer2);

        worker.SendMessage("Message 2");
    }
}

namespace Observer::Parsons
{
    template<typename T>
    struct Observer {
        virtual void fieldChanged(T& source,
                                   const std::string& field_name) = 0;
        virtual ~Observer() = default;
    };

    template<typename T>
    struct Observable
    {
        void notify(T& source, const std::string& field_name) {
            for (auto observer: m_observers)
                observer->fieldChanged(source, field_name);
        }

        void subscribe(Observer<T>& observer) {
            m_observers.push_back(&observer);
        }

        void unsubscribe(Observer<T>& observer) {
            m_observers.erase(remove(m_observers.begin(), m_observers.end(), &observer), m_observers.end());
        }

    private:
        std::vector<Observer<T>*>  m_observers;
    };

    struct Person : Observable<Person>
    {
        void set_age(uint8_t age)
        {
            const bool old_can_vote = get_can_vote();
            this->m_age = age;

            notify(*this, "age");

            //if (old_can_vote != get_can_vote())
            //    notify(*this, "can_vote");
        }

        [[nodiscard]]
        inline uint8_t get_age() const {
            return m_age;
        }

        [[nodiscard]]
        inline bool get_can_vote() const {
            return m_age >= 16;
        }

    private:
        uint8_t m_age {0};
    };

    struct TrafficAdministration : Observer<Person>
    {
        void fieldChanged(Person &source,
                          const std::string& field_name) override
        {
            if (field_name == "age")
            {
                if (source.get_age() < 17)
                    std::cout << "Not old enough to drive!\n";
                else {
                    std::cout << "Mature enough to drive!\n";
                    source.unsubscribe(*this);
                }
            }
        }
    };

    void Test()
    {
        Person p;
        TrafficAdministration ta;
        p.subscribe(ta);


        p.set_age(16);
        p.set_age(17);
    }
}


void ObserverBasic_Test();    /// ObserverBasic.cpp
void SubjectObserver_Test();  /// ObserverSubject.cpp

void Observer::TestAll()
{
    // Test1::Test();
    // Test2::Test();
    // Parsons::Test();

    // ObserverBasic_Test();

    SubjectObserver_Test();
}