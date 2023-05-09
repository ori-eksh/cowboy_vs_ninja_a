#pragma once
#include <string>

namespace ariel
{
    class Point
    {
    private:
        double x;
        double y;

    public:
        Point(double x_toInsert, double y_toInsert) : x(x_toInsert), y(y_toInsert) {}
        Point() : x(0.0), y(0.0) {}
        Point(const Point &other) : x(other.x), y(other.y) {}
        Point(Point &&other) noexcept : x((other.x)), y((other.y)) {}

        Point &operator=(const Point &other)
        {
            if (this != &other)
            {
                x = other.x;
                y = other.y;
            }
            return *this;
        }

        Point &operator=(Point &&other) noexcept
        {
            if (this != &other)
            {
                x = (other.x);
                y = (other.y);
            }
            return *this;
        }

        double distance(Point point2);

        double getX() const { return x; }
        double getY() const { return y; }

        std::string print();

        static Point moveTowards(const Point &from, Point &target, double distance)
        {
            return Point(0, 0);
        }
        ~Point() {}
    };
}
