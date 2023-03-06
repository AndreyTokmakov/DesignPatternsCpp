//============================================================================
// Name        : Strategy.cpp
// Created on  : 15.04.2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Strategy pattern src
//============================================================================

#include "Strategy.h"


#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <vector>


namespace Strategy::SimpleStrategy
{
    struct IStrategy
    {
        virtual ~IStrategy() = default;
        virtual void use() noexcept = 0;
    };

    struct Strategy_1 : public IStrategy
    {
        void use() noexcept override {
            std::cout << "Strategy_1" << std::endl;
        }
    };

    struct Strategy_2 : public IStrategy
    {
        void use() noexcept override {
            std::cout << "Strategy_2" << std::endl;
        }
    };

    struct Strategy_3 : public IStrategy
    {
        void use() noexcept override {
            std::cout << "Strategy_3" << std::endl;
        }
    };

    class IContext {
    protected:
        std::unique_ptr<IStrategy> operation;

    public:
        virtual ~IContext() = default;

        virtual void useStrategy() = 0;

        virtual void setStrategy(std::unique_ptr<IStrategy>) = 0;
    };

    class Client : public IContext {
    public:
        void useStrategy() override {
            operation->use();
        }

        void setStrategy(std::unique_ptr<IStrategy> strategy) override {
            operation = std::move(strategy);
        }
    };

    void Test()
    {
        Client customClient;

        customClient.setStrategy(std::make_unique<Strategy_1>());
        customClient.useStrategy();
        customClient.setStrategy(std::make_unique<Strategy_2>());
        customClient.useStrategy();
        customClient.setStrategy(std::make_unique<Strategy_3>());
        customClient.useStrategy();

    }
}


namespace Strategy::Calculations
{
    // Strategy interface
    struct IStrategy
    {
        virtual ~IStrategy() = default;

        // Essential: Algorithm encapsulated by strategy object
        [[nodiscard]]
        virtual double compute(double x, double y) const = 0;

        // Optional: Provides strategy metadata
        [[nodiscard]]
        virtual std::string name() const noexcept = 0;

        // Clone this object (Note: This is a virtual constructor)
        [[nodiscard]]
        virtual IStrategy* clone() const = 0;
    };


    class AddStrategy: public IStrategy {
    public:
        [[nodiscard]]
        std::string name() const noexcept override {
            return "add";
        }

        [[nodiscard]]
        double compute(double x, double y) const override  {
            return x + y;
        }

        [[nodiscard]]
        IStrategy* clone() const override {
            std::cerr << " [TRACE] AddStrategy => I was cloned" << "\n";
            return new AddStrategy(*this);
        }
    };


    struct MultStrategy: public IStrategy {
    public:
        [[nodiscard]]
        std::string name() const noexcept override {
            return "mult";
        }

        [[nodiscard]]
        double compute(double x, double y) const override  {
            return x * y;
        }

        [[nodiscard]]
        IStrategy* clone() const override {
            std::cerr << " [TRACE] MultStrategy => I was cloned" << "\n";
            return new MultStrategy(*this);
        }
    };

    struct LinearCombStrategy: public IStrategy {
        double a { 0.0 }, b { 0.0 }, c { 0.0 };

        LinearCombStrategy(double a, double b, double c): a(a), b(b), c(c) {
        }

        [[nodiscard]]
        std::string name() const noexcept override {
            return "Linear combination a * x + b * y + c";
        }

        [[nodiscard]]
        double compute(double x, double y) const override  {
            return a * x + b * y + c;
        }

        [[nodiscard]]
        IStrategy* clone() const override {
            std::cerr << " [TRACE] LinearCombStrategy => I was cloned" << "\n";
            return new LinearCombStrategy(*this);
        }
    };



    class Context {
    private:
        std::unique_ptr<IStrategy> strategy;

    public:
        Context(): strategy {nullptr} { }
        explicit Context(IStrategy* s): strategy {s} { }
        explicit Context(const IStrategy& s): strategy {s.clone()} { }

        void setStrategy(IStrategy* s) {
            strategy.reset(s);
        }

        auto setStrategy(const IStrategy& s){
            strategy.reset(s.clone());
        }

        void compute(double x, double y) {
            if (nullptr == strategy)
                throw std::runtime_error("Error: strategy not set");

            const double result = strategy->compute(x, y);
            std::cout << " strategy = " << strategy->name() << " "
                      << "( x = " << x << " ; "
                      << "y = " << y << " )"
                      << "\n" ;
            std::cout << "Result = " << result << "\n";
        }
    };

    void Test()
    {
        Context ctx;
        std::cout << "==== Strategy = ADD ====" << "\n";
        ctx.setStrategy(new AddStrategy);
        ctx.compute(3.0, 4.0);

        std::cout << "==== Strategy = MULT ====" << "\n";
        ctx.setStrategy(new MultStrategy);
        ctx.compute(3.0, 4.0);

        std::cout << "==== Strategy = Linear combination ====" << "\n";
        ctx.setStrategy(new LinearCombStrategy(5, 3, 4));
        ctx.compute(3.0, 4.0);

        std::cout << "==== Strategy = Linear combination [2] ====" << "\n";
        auto comb1 = LinearCombStrategy(6.0, 5.0, 10.0);
        // Copy stack-allocated object comb1 using the virtual constructor

        ctx.setStrategy(comb1);
        ctx.compute(5.0, 3.0);

        std::cout << "==== Strategy = Linear combination [2] ====" << "\n";
        // Copy stack-allocated temporary object comb1 using the virtual constructor clone

        ctx.setStrategy(LinearCombStrategy{6.0, 5.0, 10.0});
        ctx.compute(2.0, 6.0);
    }
}

namespace Strategy::Strategy_Text
{
    enum class Format {
        Markdown,
        Html
    };

    struct ListStrategy
    {
        virtual void add_list_item(std::ostringstream& oss, const std::string& item) { };
        virtual void start(std::ostringstream& oss) { };
        virtual void end(std::ostringstream& oss) { };

        virtual ~ListStrategy() = default;
    };

    struct MarkdownListStrategy: ListStrategy {
        void add_list_item(std::ostringstream& oss, const std::string& item) override {
            oss << " - " << item << std::endl;
        }
    };

    struct HtmlListStrategy: ListStrategy
    {
        void start(std::ostringstream& oss) override {
            oss << "<ul>" << std::endl;
        }

        void end(std::ostringstream& oss) override {
            oss << "</ul>" << std::endl;
        }

        void add_list_item(std::ostringstream& oss, const std::string& item) override {
            oss << "\t<li>" << item << "</li>" << std::endl;
        }
    };

    struct TextProcessor
    {
        void clear()
        {
            strStream.str("");
            strStream.clear();
        }

        void append_list(const std::vector<std::string>& items)
        {
            listStrategy->start(strStream);
            for (auto& item: items)
                listStrategy->add_list_item(strStream, item);
            listStrategy->end(strStream);
        }

        void set_output_format(Format format)
        {
            switch (format)
            {
                case Format::Markdown:
                    listStrategy = std::make_unique<MarkdownListStrategy>();
                    break;
                case Format::Html:
                    listStrategy = std::make_unique<HtmlListStrategy>();
                    break;
            }
        }

        std::string str() {
            return strStream.str();
        }

    private:
        std::ostringstream             strStream;
        std::unique_ptr<ListStrategy>  listStrategy;
    };


    void Test() {
        // markdown
        TextProcessor tp;
        tp.set_output_format(Format::Markdown);
        tp.append_list({ "foo", "bar", "baz" });

        std::cout << tp.str() << std::endl;
        // html
        tp.clear();
        tp.set_output_format(Format::Html);
        tp.append_list({ "foo", "bar", "baz" });
        std::cout << tp.str() << std::endl;
    }
}


void Strategy::Test()
{
    // SimpleStrategy::Test();

    Calculations::Test();

    // Strategy_Text::Test();
}
