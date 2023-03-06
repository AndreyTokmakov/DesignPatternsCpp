//============================================================================
// Name        : Composite.cpp
// Created on  : August 25, 2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Composite design pattern demo
//============================================================================

#include "Composite.h"

namespace Composite::Pages
{
    class IPage {
    public:
        virtual void Add([[maybe_unused]] IPage& page) noexcept {}
        virtual void Remove() noexcept {}
        virtual void Delete([[maybe_unused]] IPage& page) noexcept {}

        virtual ~IPage() = default;
    };

    class Page : public IPage {
    public:
        void Add([[maybe_unused]] IPage& page) noexcept override {
            std::cout << "Something is added to the page" << std::endl;
        }

        void Remove() noexcept override {
            std::cout << "Something is removed from the page" << std::endl;
        }

        void Delete([[maybe_unused]] IPage& page) noexcept override {
            std::cout << "Something is deleted from page " << std::endl;
        }
    };


    class Copy : public IPage {
        std::vector<IPage> copyPages;

    public:
        void AddElement([[maybe_unused]] IPage& page) {
            copyPages.push_back(page);
        }

        void Add([[maybe_unused]] IPage& page) noexcept override {
            std::cout << "something is added to the copy" << std::endl;
        }

        void Remove() noexcept override {
            std::cout << "something is removed from the copy" << std::endl;
        }

        void Delete([[maybe_unused]] IPage& page) noexcept override {
            std::cout << "something is deleted from the copy";
        }
    };


	void Test()
    {
		Page a;
		Page b;
		Copy allcopy;
		allcopy.AddElement(a);
		allcopy.AddElement(b);

		allcopy.Add(a);
		a.Add(b);

		allcopy.Remove();
		b.Remove();
	}
}


namespace Composite::Graphics
{
    class IGraphic {
    public:
        virtual void print() const noexcept = 0;
    };


    class Ellipse: public IGraphic {
    public:
        void print() const noexcept override {
            std::cout << "Ellipse" << std::endl;
        }
    };


    class CompositeGraphic : public IGraphic {
    private:
        std::vector<std::shared_ptr<IGraphic>>  graphicList;

    public:
        void print() const noexcept override {
            for (const auto& a : this->graphicList) {
                a->print();
            }
        }

        void add(std::shared_ptr<IGraphic> aGraphic)  {
            this->graphicList.push_back(aGraphic);
        }
    };



	void Test()
    {
		auto ellipse1 = std::make_shared<Ellipse>();
		auto ellipse2 = std::make_shared<Ellipse>();
		auto ellipse3 = std::make_shared<Ellipse>();
		auto ellipse4 = std::make_shared<Ellipse>();

		// Initialize three composite graphics
		auto graphic = std::make_shared<CompositeGraphic>();
		auto graphic1 = std::make_shared<CompositeGraphic>();
		auto graphic2 = std::make_shared<CompositeGraphic>();

		// Composes the graphics
		graphic1->add(ellipse1);
		graphic1->add(ellipse2);
		graphic1->add(ellipse3);

		graphic2->add(ellipse4);

		graphic->add(graphic1);
		graphic->add(graphic2);

		// Prints the complete graphic (four times the string "Ellipse")
		graphic->print();

	}
}

namespace Composite::Table
{
    struct Component
    {
        virtual void traverse() = 0;
        virtual ~Component() = default;
    };

    struct Primitive: public Component
    {
        int value;

        explicit Primitive(int val): value {val} {
        }

        void traverse() override {
            std::cout << value << "  ";
        }
    };

    class Composite: public Component, public std::vector<Component*>
    {
        int value;

    public:
        explicit Composite(int val) {
            value = val;
        }

        void add(Component *c) {
            push_back(c);
        }

        void traverse() override {
            std::cout << value << "  ";
            for (const Composite& self = *this; const auto& child: self)
                child->traverse();
        }
    };

    class Row: public Composite
    {
    public:
        explicit Row(int val): Composite(val) {
        }

        void traverse() override {
            std::cout << "Row"; // base class.
            Composite::traverse();
        }
    };

    class Column: public Composite
    {
    public:
        explicit Column(int val): Composite(val) {
        }

        void traverse() override {
            std::cout << "Col";
            Composite::traverse();
        }
    };

    void Test()
    {
        Row first(1);                 // Row1
        Column second(2);             //   |
        Column third(3);              //   +-- Col2
        Row fourth(4);                //   |     |
        Row fifth(5);                 //   |     +-- 7
        first.add(&second);           //   +-- Col3
        first.add(&third);            //   |     |
        third.add(&fourth);           //   |     +-- Row4
        third.add(&fifth);            //   |     |     |
        first.add(new Primitive(6));     //   |     |     +-- 9
        second.add(new Primitive(7));    //   |     +-- Row5
        third.add(new Primitive(8));     //   |     |     |
        fourth.add(new Primitive(9));    //   |     |     +-- 10
        fifth.add(new Primitive(10));    //   |     +-- 8
        first.traverse();             //   +-- 6
    }
}

namespace Composite::Leafs
{
    struct IComponent
    {
        virtual void traverse() = 0;
        virtual ~IComponent() = default;
    };

    struct Leaf: IComponent
    {
        int value {0};

        explicit Leaf(int val): value {val} {
        }

        void traverse() override {
            std::cout << value << ' ';
        }
    };

    struct Composite: public IComponent
    {
        std::vector<IComponent*> children {};

        void add(IComponent *element) {
            children.push_back(element);
        }

        void traverse() override {
            for (auto& item : children)
                item->traverse();
        }
    };

    void Test()
    {
        Composite containers[4];

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++)
                containers[i].add(new Leaf(i *3+j));

        for (int i = 1; i < 4; i++)
            containers[0].add(&(containers[i]));

        for (auto & container : containers)
        {
            container.traverse();
            std::cout << std::endl;
        }
    }

}

void Composite::Test()
{
	// Pages::Test();

    // Graphics::Test();

    Table::Test();

    // Leafs::Test();
}
