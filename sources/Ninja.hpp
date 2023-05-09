#pragma once
#include "Character.hpp"
using namespace std;

namespace ariel
{
    constexpr int FORTEEN = 14;
    constexpr int TWELVE = 12;
    constexpr int HUNDRED = 100;
    constexpr int EIGHT = 8;
    constexpr int HUNDRED20 = 120;
    constexpr int HUNDRED50 = 150;

    class Ninja : public Character
    {
    private:
        int speed;

    public:
        Ninja(string name, Point const &location, int hpoints, int const speed) : Character(std::move(name), location, hpoints), speed(speed) {}
        Ninja(const Ninja &other) : Character(other), speed(other.speed) {}
        Ninja() : Character("anonimic", Point(0, 0), 0), speed(0) {}

        // Copy assignment operator
        Ninja &operator=(const Ninja &other)
        {
            if (this != &other)
            {
                Character::operator=(other);
                speed = other.speed;
            }
            return *this;
        }
        Ninja &operator=(Ninja &&other) noexcept
        {
            if (this != &other)
            {
                Character::operator=(other);
                speed = (other.speed);
            }
            return *this;
        }
        Ninja(Ninja &&other) noexcept
            : Character(std::move(other)), speed(other.speed)
        {
        }

        int getSpeed();
        void slash(Character *target);
        void move(Character *target);
        std::string print() override;
        ~Ninja() override {}
    };

    // the Special ninja
    class YoungNinja : public Ninja
    {
    public:
        YoungNinja(string name, Point const &location) : Ninja(std::move(name), location, HUNDRED, FORTEEN) {}
        //~YoungNinja() override {}
    };

    class TrainedNinja : public Ninja
    {
    public:
        TrainedNinja(string name, Point const &location) : Ninja(std::move(name), location, HUNDRED20, TWELVE) {}
        //~TrainedNinja() override {}
    };

    class OldNinja : public Ninja
    {
    public:
        OldNinja(string name, Point const &location) : Ninja(std::move(name), location, HUNDRED50, EIGHT) {}
        // ~OldNinja() override {}
    };
}