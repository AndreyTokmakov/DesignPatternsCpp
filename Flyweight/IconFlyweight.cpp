//============================================================================
// Name        : FlyweightIcon.cpp
// Created on  : 12.04.2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Flyweight pattern src
//============================================================================

#include "Flyweight.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>


namespace Flyweight::FlyweightIcon {

    class Icon {
    private:
        inline static constexpr std::string_view goIconName = "go";
        inline static constexpr std::string_view stopIconName = "stop";
        inline static constexpr std::string_view selectIconName = "select";
        inline static constexpr std::string_view undoIconName = "go";

    protected:
        std::string name;
        size_t width;
        size_t height;

    public:

        template<typename S>
        explicit Icon(S &&name) : name{std::forward<S>(name)} {
            if (Icon::goIconName == name) {
                this->width = 20;
                this->height = 20;
            } else if (Icon::stopIconName == name) {
                this->width = 40;
                this->height = 40;
            } else if (Icon::selectIconName == name) {
                this->width = 60;
                this->height = 60;
            } else if (Icon::undoIconName == name) {
                this->width = 30;
                this->height = 30;
            } else {
                // TODO: Handle this somehow
            }
            std::cout << "Icon '" << name << "' constructed" << std::endl;
        }

        [[nodiscard]]
        inline const std::string &getName() const noexcept {
            return this->name;
        }

        void draw(size_t x, size_t y) const noexcept {
            std::cout << "   drawing " << name << ": upper left (" << x << "," << y
                      << ") - lower right (" << x + width << "," << y + height << ")"
                      << std::endl;
        }
    };


    class FlyweightFactory final {
    private:
        std::unordered_map<std::string_view , std::shared_ptr<Icon>> icons;
        inline static constexpr size_t INITIAL_CAPACITY{10};

    public:
        static FlyweightFactory *getFactory() {
            static FlyweightFactory theSingleInstance;
            return &theSingleInstance;
        }

    public:
        template<typename S>
        std::shared_ptr<Icon> getIcon(S &&iconName) {
            if (auto iter = this->icons.find(std::forward<S>(iconName)); this->icons.end() != iter)
                return iter->second;
            return this->icons.emplace(std::forward<S>(iconName),
                                       std::make_shared<Icon>(std::forward<S>(iconName))).first->second;
        }

        // std::shared_ptr<Icon> getIcon(const std::string& iconName);

        void reportTheIcons() const noexcept {
            std::cout << "\nActive Flyweights: " << std::endl;
            for (const auto &[k, v]: this->icons)
                std::cout << "   [ " << k << " ]" << std::endl;
        }

    private:
        FlyweightFactory() {
            this->icons.reserve(INITIAL_CAPACITY);
        }

        // Seal copy & move constructor
        FlyweightFactory(const FlyweightFactory &root) = delete;

        FlyweightFactory(FlyweightFactory &&root) noexcept = delete;

        // Disable copy assign
        FlyweightFactory operator=(const FlyweightFactory &) = delete;

        FlyweightFactory operator=(FlyweightFactory &&) noexcept = delete;
    };

}

namespace Flyweight::FlyweightIcon_Impl1 {

    using namespace FlyweightIcon;

    // DialogBox abstract class:
    struct DialogBox {
        std::vector<std::shared_ptr<Icon>> icons;
        int iconsOriginX;
        int iconsOriginY;
        int iconsXIncrement;
        inline const static int ICON_MAX = 3;

    public:
        DialogBox(int x, int y, int incr): iconsOriginX(x), iconsOriginY(y), iconsXIncrement(incr) {
            // Reserve some space.
            this->icons.reserve(DialogBox::ICON_MAX);
        }

        virtual void draw() const noexcept = 0;

        virtual ~DialogBox() = default;
    };


    struct FileSelection: DialogBox {
        FileSelection(const std::shared_ptr<Icon>& first,
                      const std::shared_ptr<Icon>& second,
                      const std::shared_ptr<Icon>& third) : DialogBox(100, 100, 100)
        {
            icons.push_back(first);
            icons.push_back(second);
            icons.push_back(third);
        }

        void draw() const noexcept override {
            std::cout << "drawing FileSelection:" << std::endl;
            for (int i = 0; i < 3; i++)
                icons[i]->draw(iconsOriginX + (i *iconsXIncrement), iconsOriginY);
        }
    };

    struct CommitTransaction: DialogBox {
        CommitTransaction(const std::shared_ptr<Icon>& first,
                          const std::shared_ptr<Icon>& second,
                          const std::shared_ptr<Icon>& third) : DialogBox(150, 150, 150)
        {
            icons.push_back(first);
            icons.push_back(second);
            icons.push_back(third);
        }
        void draw() const noexcept override
        {
            std::cout << "drawing CommitTransaction:" << std::endl;
            for (int i = 0; i < 3; i++)
                icons[i]->draw(iconsOriginX + (i *iconsXIncrement), iconsOriginY);
        }
    };

    void Test()
    {
        FlyweightFactory* factory = FlyweightFactory::getFactory();

        std::vector<std::shared_ptr<DialogBox>> dialogs;
        dialogs.push_back(std::make_shared<FileSelection>(
                factory->getIcon("go"),
                factory->getIcon("stop"),
                factory->getIcon("select")));

        dialogs.push_back(std::make_shared<CommitTransaction>(
                factory->getIcon("select"),
                factory->getIcon("stop"),
                factory->getIcon("undo")));


        for (const auto& D : dialogs)
            D->draw();

        factory->reportTheIcons();
    }
}


namespace Flyweight::FlyweightIcon_Impl2{

    using namespace FlyweightIcon;

    struct DialogBox
    {
        std::vector<std::shared_ptr<Icon>> icons;

        int iconsOriginX;
        int iconsOriginY;
        int iconsXIncrement;

        inline const static int ICON_MAX = 3;
        inline static FlyweightFactory* iconFactory = FlyweightFactory::getFactory();

    public:
        DialogBox(int x, int y, int incr):
                iconsOriginX(x), iconsOriginY(y), iconsXIncrement(incr) {
            this->icons.reserve(DialogBox::ICON_MAX);
        }

        virtual void draw() const noexcept = 0;
        virtual ~DialogBox() = default;

    protected:

        void addIcon(std::string_view iconName) {
            icons.push_back(iconFactory->getIcon(iconName));
        }
    };


    struct FileSelection: DialogBox {
        FileSelection(std::string_view first,
                      std::string_view second,
                      std::string_view third) : DialogBox(100, 100, 100)
        {
            addIcon(first);
            addIcon(second);
            addIcon(third);
        }

        void draw() const noexcept override {
            std::cout << "drawing FileSelection:" << std::endl;
            for (int i = 0; const auto& icon: icons)
                icon->draw(iconsOriginX + ((i++) *iconsXIncrement), iconsOriginY);
        }
    };

    struct CommitTransaction: DialogBox {
        CommitTransaction(std::string_view first,
                          std::string_view second,
                          std::string_view third) : DialogBox(150, 150, 150)
        {
            addIcon(first);
            addIcon(second);
            addIcon(third);
        }
        void draw() const noexcept override
        {
            std::cout << "drawing CommitTransaction:" << std::endl;
            for (int i = 0; const auto& icon: icons)
                icon->draw(iconsOriginX + ((i++) *iconsXIncrement), iconsOriginY);
        }
    };

    void Test()
    {
        FlyweightFactory* factory = FlyweightFactory::getFactory();

        std::vector<std::shared_ptr<DialogBox>> dialogs;
        dialogs.push_back(std::make_shared<FileSelection>("go","stop","select"));
        dialogs.push_back(std::make_shared<CommitTransaction>("select","stop","undo"));

        for (const auto& D : dialogs)
            D->draw();

        factory->reportTheIcons();
    }
}

void IconFlyweightTest()
{
    // Flyweight::FlyweightIcon_Impl1::Test();
    Flyweight::FlyweightIcon_Impl2::Test();
}