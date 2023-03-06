/**============================================================================
Name        : RAII.cpp
Created on  : 13.08.2020
Author      : Tokmakov Andrey
Version     : 1.0
Copyright   : Your copyright notice
Description : RAII
============================================================================**/

#include "RAII.h"

#include <iostream>

namespace RAII
{
    struct resource
    {
        resource(int x, int y) {
            std::cout << "resource acquired\n";
        }

        ~resource() {
            std::cout << "resource destroyed\n";
        }
    };

    template<class T>
    class smart_ptr
    {
        using value_type = T;

        value_type* m_ptr;

    public:
        template<typename... Args>
        explicit smart_ptr(Args&&... args) : m_ptr(new value_type(std::forward<Args>(args)...)) {
        }

        ~smart_ptr() {
            delete m_ptr;
        }

        smart_ptr(const smart_ptr& rhs) = delete;
        smart_ptr& operator=(const smart_ptr& rhs) = delete;

        smart_ptr(smart_ptr&& rhs) noexcept : m_ptr(exchange(rhs.m_ptr, nullptr)){

        }

        smart_ptr& operator=(smart_ptr&& rhs) noexcept {
            if (&rhs == this)
                return *this;
            delete m_ptr;
            m_ptr = exchange(rhs.m_ptr,nullptr);
            return *this;
        }

        value_type& operator*() const {
            return *m_ptr;
        }

        value_type* operator->() const {
            return m_ptr;
        }
    };
};

void RAII::Test()
{
    // now ptr guarantee the release of resource
    auto ptr = smart_ptr<resource>(1, 2);
};

