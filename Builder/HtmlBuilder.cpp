//============================================================================
// Name        : HtmlBuilder.cpp
// Created on  :
// Author      : Tokmakov Andrei
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : HtmlBuilder example
//============================================================================

#include "Builder.h"
#include <string>
#include <utility>
#include <vector>
#include <memory>

namespace Builder {

    struct HtmlElement {
        std::string name {};
        std::string text {};
        std::vector <HtmlElement> elements;

        explicit HtmlElement(std::string name) :
                name(std::move(name)) {
        }

        HtmlElement(std::string name, std::string text) :
                name(std::move(name)), text(std::move(text)) {
        }

        HtmlElement& addChild(std::string child_name,
                              std::string child_text) noexcept{
            elements.emplace_back(std::move(child_name), std::move(child_text) );
            return *this;
        }

        [[nodiscard]]
        std::string toString(int indent = 0) const noexcept {
            std::string block {"<" + name + ">"};
            if (text.empty())
                for (const auto& element: elements)
                    block.append(element.toString());
            else
                block.append(text);
            block.append("</" + name + ">");
            return block;
        }
    };


    struct HtmlBuilder {
        HtmlElement root;

        explicit HtmlBuilder(std::string root_name): root (std::move(root_name)) {
        }

        HtmlBuilder& addChild(std::string child_name, std::string child_text) noexcept {
            root.addChild(std::move(child_name), std::move(child_text) );
            return *this;
        }

        [[nodiscard]]
        std::string toString() const noexcept {
            return root.toString();
        }
    };

    void Test_HTML()
    {
        {
            HtmlBuilder builder{"ul"};
            builder.addChild("li", "hello").addChild("li", "world");

            std::cout << builder.toString() << std::endl;
        }

    }
};