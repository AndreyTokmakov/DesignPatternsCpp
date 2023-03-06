
#include <iostream>
#include <memory>

namespace Proxy
{
    struct IPage {
        virtual ~IPage() = default;

        virtual void displayText()  = 0;
        virtual void displayImage() = 0;
        virtual void displayVideo() = 0;
        virtual void displayEmpty() = 0;
    };

    /////////////////////////////////////////////////////

    class Page : public IPage
    {
    public:
        Page() {
            std::cout << __FUNCTION__ << std::endl;
        }
        ~Page() override  {
            std::cout << std::endl << __FUNCTION__ << std::endl;
        }

        void displayText() override {
            std::cout << "Displaying text." << std::endl;
        }

        void displayImage() override {
            std::cout << "Displaying an image." << std::endl;
        }

        void displayVideo() override{
            std::cout << "Displaying a video." << std::endl;
        }

        void displayEmpty() override {
            std::cout << "Sorry nothing to display." << std::endl;
        }
    };


    ////////////////////////////////////////////////////////

    class PageProxy : public IPage
    {
    public:
        PageProxy() {
            std::cout << __FUNCTION__ << std::endl;
            _page = NULL;
        }

        ~PageProxy() override {
            std::cout << __FUNCTION__ << std::endl;
        }

        void displayText() override { } ;
        void displayImage() override { };
        void displayVideo() override { };
        void displayEmpty() override { };

        void setCurrentPage(int currentPage) noexcept {
            _currentPage = currentPage;
        }

        [[nodiscard]]
        int getCurrentPage() const noexcept {
            return _currentPage;
        }

        std::shared_ptr<Page> getPage() {
            if (nullptr == _page) {
                _page = std::make_shared<Page>();
            }
            return _page;
        }

        void displayContent(int pageNumber) {
            setCurrentPage(pageNumber);
            std::cout << std::endl << "On page \"" << getCurrentPage() << "\":" << std::endl;
            switch (pageNumber)
            {
                case 1:
                    getPage()->displayText();
                    break;
                case 24:
                    getPage()->displayText();
                    getPage()->displayImage();
                    break;
                case 37:
                    getPage()->displayText();
                    getPage()->displayImage();
                    getPage()->displayVideo();
                    break;

                default:
                    getPage()->displayEmpty();
                    break;
            }
            std::cout << std::endl;
        }

    private:
        int _currentPage;
        std::shared_ptr<Page> _page;
    };



    class Document
    {
    public:
        Document() {
            std::cout << __FUNCTION__ << std::endl;
            initProxy();
        }

        ~Document() {
            std::cout << __FUNCTION__ << std::endl;
        }

        void open(int pageNumber = 1)  {
            _proxy.displayContent(pageNumber);
        }

        void initProxy() {
        }

        void changeToPage(int pageNumber) {
            _proxy.displayContent(pageNumber);
        }

    private:
        PageProxy _proxy;
    };
}

namespace Proxy
{
    void DocumentTest()
    {
        Document doc;
        doc.open();             // by default, it opens page 1
        doc.changeToPage(4);
        doc.changeToPage(15);
        doc.changeToPage(24);
        doc.changeToPage(1);
        doc.changeToPage(37);
        doc.changeToPage(59);
    }
}