#pragma once

#include "Point.hpp"

namespace ariel
{
    class Character
    {
    private:
        Point location;
        std::string name;
        int hit_points;

    public:
        Character(std::string name, const Point &location, int hit_points) : location(location), name(std::move(name)), hit_points(hit_points) {}
        Character(const Character &other) : location(other.location), name(other.name), hit_points(other.hit_points) {}
        Character(Character &&other) noexcept : location(std::move(other.location)), name(std::move(other.name)), hit_points(other.hit_points) {}

        Character &operator=(const Character &other)
        {
            if (this != &other)
            {
                location = other.location;
                name = other.name;
                hit_points = other.hit_points;
            }
            return *this;
        }
        Character &operator=(Character &&other) noexcept
        {
            if (this != &other)
            {
                location = std::move(other.location);
                name = std::move(other.name);
                hit_points = other.hit_points;

                // Reset the other object
                other.location = Point{0, 0};
                other.name.clear();
                other.hit_points = 0;
            }
            return *this;
        }

        int getHitPoints();
        bool isAlive();
        double distance(Character *);
        void hit(int num);
        std::string getName();
        Point getLocation();
        virtual std::string print() = 0;
        virtual ~Character() {}
    };
}