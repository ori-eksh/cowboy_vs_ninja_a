#include "Character.hpp"

using namespace std;

namespace ariel
{

    bool Character::isAlive()
    {
        return false;
    }

    double Character::distance(Character *toCheckWith)
    {
        return 0.0;
    }

    void Character::hit(int num)
    {
        return;
    }

    string Character::getName()
    {
        return "ori";
    }

    Point Character::getLocation()
    {
        return Point(0, 0);
    }

    int Character::getHitPoints()
    {
        return 0;
    }

}