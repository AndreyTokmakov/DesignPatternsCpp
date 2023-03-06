/**============================================================================
Name        : DrawingBridge.cpp
Created on  : 27.12.2022
Author      : Tokmakov Andrey
Version     : 1.0
Copyright   : Your copyright notice
Description : DrawingBridge src
============================================================================**/

#include <iostream>

namespace Bridge
{
    struct DrawingAPI {
        virtual void drawCircle() = 0;
    };

    struct DrawingAPI_1 : DrawingAPI
    {
        void drawCircle() override {
            std::cout << "Drawn by API 1"<< std::endl;
        }
    };

    struct DrawingAPI_2 : DrawingAPI
    {
        void drawCircle() override {
            std::cout << "Drawn by API 2"<< std::endl;
        }
    };

    struct Shape
    {
        explicit Shape(DrawingAPI &drawingAPI) : drawApi { drawingAPI } {
        }

        virtual void draw() = 0;

    protected:
        // Now Shapes does not need to worry about drawing APIs
        DrawingAPI& drawApi;
    };

    struct Circle : Shape
    {
        explicit Circle(DrawingAPI &drawingAPI) : Shape{drawingAPI} {
        }

        void draw() override {
            drawApi.drawCircle();
        }
    };
}

void DrawingAPITest()
{
    using namespace Bridge;

    DrawingAPI_1 API_1;
    DrawingAPI_2 API_2;
    Circle(API_1).draw();
    Circle(API_2).draw();
}