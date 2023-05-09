#pragma once
#include "Character.hpp"

namespace ariel
{

    class Cowboy : public Character
    {
    public:
        static constexpr int HUNDRED10 = 100;
        static constexpr int SIX = 6;

        int amountOfBalls;

        Cowboy(std::string name, const Point &location) : Character(std::move(name), location, HUNDRED10), amountOfBalls(SIX) {}

        Cowboy(const Cowboy &) = delete;
        Cowboy &operator=(const Cowboy &) = delete;
        Cowboy(Cowboy &&) = delete;
        Cowboy &operator=(Cowboy &&) = delete;

        void shoot(Character *target);
        bool hasBullets();
        void reload();
        int getAmountOfBalls();
        std::string print() override;
        ~Cowboy() override {}
    };
}