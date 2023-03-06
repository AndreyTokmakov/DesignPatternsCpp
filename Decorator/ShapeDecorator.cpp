/**============================================================================
Name        : ShapeDecorator.cpp
Created on  :
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : ShapeDecorator src
============================================================================**/

#include "ShapeDecorator.h"
#include <iostream>

namespace ShapeDecorator
{
    struct Point
    {
        double x { 0.0f};
        double y { 0.0f};
        Point(double x, double y):x(x), y(y) {}
    };


    struct Color
    {
        unsigned short r :8;
        unsigned short g :8;
        unsigned short b :8;
        Color(unsigned char r, unsigned char g, unsigned char b):
            r {r}, g {g}, b {b} { /** **/ }
    };


    struct Shape
    {
        virtual void show() const = 0;
        virtual ~Shape() = default;
    };


    class Circle : public Shape
    {
    private:
        Point center;
        double radius;

    public:
        Circle(Point pnt, double rds):center(pnt), radius(rds) {  /** **/ }

        void show() const override
        {
            std::cout << "I draw a Circle: "<<std::endl;
            std::cout << "center: " << "("<<center.x<<","<<center.y<<")"<<"\t";
            std::cout << "radius: " << radius<<std::endl;
        }
    };


    class ShapeDecorator : public Shape
    {
    protected:
        Shape* shape { nullptr };

    public:
        explicit ShapeDecorator(Shape* shp): shape {shp} { }

        void show() const override = 0;
        ~ShapeDecorator() override = default;
    };


    class ColorShapeDecorator : public ShapeDecorator
    {
    private:
        Color color;

    public:
        ColorShapeDecorator(Shape* shp, Color clr):
                ShapeDecorator {shp}, color { clr } {
        }

        void show() const override
        {
            std::cout << "Use RGB: " << "("
                      << color.r << "," << color.g << "," << color.b << ")" << std::endl;
            shape->show();
        }

        ~ColorShapeDecorator() override {
            delete shape;
        }
    };
}

void ShapeDecorator::Test()
{
    Shape* circle = new ColorShapeDecorator(new Circle(Point(3, 4), 1.0),
                                            Color {255, 0, 0 });
    circle->show();

}