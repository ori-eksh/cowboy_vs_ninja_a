#include <stdexcept>
#include <iostream>
#include <sstream>
#include "doctest.h"
#include "sources/Team.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("point")
{
    Point point1(1, 2);
    CHECK(point1.getX() == 1);
    CHECK(point1.getY() == 2);

    Point dist1(0, 0);
    Point dist2(0, 0);
    CHECK(dist1.distance(dist2) == 0);
    CHECK(Point::moveTowards(dist1, dist2, 1.0).getX() == point1.getX());
    CHECK(Point::moveTowards(dist1, dist2, 1.0).getY() == point1.getY());
}

TEST_CASE("YoungNinja is build")
{
    Point point(0, 0);
    YoungNinja young("ori", point);
    CHECK(young.getName() == "ori");
    CHECK(young.getHitPoints() == 100);
    CHECK(young.getSpeed() == 14);
    CHECK(young.getLocation().getX() == point.getX());
    CHECK(young.getLocation().getY() == point.getY());
}
TEST_CASE("TrainedNinja is build")
{
    Point point(0, 0);
    TrainedNinja Trained("ori", point);
    CHECK(Trained.getName() == "ori");
    CHECK(Trained.getHitPoints() == 120);
    CHECK(Trained.getSpeed() == 12);
    CHECK(Trained.getLocation().getX() == point.getX());
    CHECK(Trained.getLocation().getY() == point.getY());
}
TEST_CASE("OldNinja is build")
{
    Point point(0, 0);
    OldNinja Old("ori", point);
    CHECK(Old.getName() == "ori");
    CHECK(Old.getHitPoints() == 150);
    CHECK(Old.getSpeed() == 8);
    CHECK(Old.getLocation().getX() == point.getX());
    CHECK(Old.getLocation().getY() == point.getY());
}
TEST_CASE("cowboy is build")
{
    Point point(0, 0);
    Cowboy boy("ori", point);
    CHECK(boy.getName() == "ori");
    CHECK(boy.getHitPoints() == 110);
    CHECK(boy.amountOfBalls == 6);
    CHECK(boy.getLocation().getX() == point.getX());
    CHECK(boy.getLocation().getY() == point.getY());
}
TEST_CASE("Character is build")
{
    Point point(0, 0);
    Cowboy boy("ori", point);
    OldNinja old("ori", point);
    TrainedNinja Trained("ori", point);
    YoungNinja young("ori", point);

    CHECK(boy.isAlive());
    CHECK(old.isAlive());
    CHECK(Trained.isAlive());
    CHECK(young.isAlive());

    CHECK(boy.distance(&old) == 0);
    CHECK(Trained.distance(&young) == 0);

    CHECK(boy.hasBullets());
    int bulls = boy.amountOfBalls;
    boy.reload();
    CHECK(boy.getAmountOfBalls() == (bulls + 6));
}

TEST_CASE("Character is mooving")
{
    Point point1(0, 0);
    Point point2(8, 6);

    Cowboy boy("ori", point1);
    OldNinja old("ori", point1);
    TrainedNinja Trained("ori", point1);
    YoungNinja young("ori", point1);
    Cowboy toKill("ori", point2);

    old.move(&toKill);
    CHECK((boy.getLocation().getX() + boy.getLocation().getY()) == 8);

    Trained.move(&toKill);
    CHECK(Trained.getLocation().getX() == 8); // the distance is 10 - he dosnt need all the 12 steps
    CHECK(Trained.getLocation().getY() == 6);
    young.move(&toKill);
    CHECK(young.getLocation().getX() == 8); // the distance is 10 - he dosnt need all the 12 steps
    CHECK(young.getLocation().getY() == 6);
}
TEST_CASE("Team is build")
{
    Point point(0, 0);
    Cowboy boy("ori", point);
    OldNinja old("ori", point);

    CHECK(boy.isAlive());
    CHECK(old.isAlive());
    Team newTeam(&old);
    CHECK(newTeam.stillAlive() == 1);
    newTeam.add(&boy);
    CHECK(newTeam.stillAlive() == 2);
}
TEST_CASE("Team2 is build")
{
    Point point(0, 0);
    Cowboy boy("ori", point);
    OldNinja old("ori", point);

    CHECK(boy.isAlive());
    CHECK(old.isAlive());
    Team2 newTeam(&old);
    CHECK(newTeam.stillAlive() == 1);
    newTeam.add(&boy);
    CHECK(newTeam.stillAlive() == 2);
}
TEST_CASE("SmartTeam is build")
{
    Point point(0, 0);
    Cowboy boy("ori", point);
    OldNinja old("ori", point);

    CHECK(boy.isAlive());
    CHECK(old.isAlive());
    SmartTeam newTeam(&old);
    CHECK(newTeam.stillAlive() == 1);
    newTeam.add(&boy);
    CHECK(newTeam.stillAlive() == 2);
}
TEST_CASE("the cowboy shoot 1 time")
{
    Point point(0, 0);
    Cowboy boy("ori", point);
    OldNinja old("ori", point);

    Team newTeam1(&old);
    Team newTeam2(&boy);

    CHECK(newTeam1.stillAlive() == 1);
    boy.shoot(&boy);
    CHECK(boy.getAmountOfBalls() == 5);
    CHECK(old.getHitPoints() == 140);
}
TEST_CASE("the cowboy shoot 6 times and try to shoot again")
{
    Point point(0, 0);
    Cowboy boy("ori", point);
    OldNinja old("ori", point);

    Team newTeam1(&old);
    Team newTeam2(&boy);
    boy.shoot(&boy);
    boy.shoot(&boy);
    boy.shoot(&boy);
    CHECK(boy.getAmountOfBalls() == 3);
    boy.shoot(&boy);
    boy.shoot(&boy);
    boy.shoot(&boy);
    CHECK(boy.hasBullets() == false);
    CHECK(boy.getAmountOfBalls() == 0);
    CHECK(old.getHitPoints() == 90);
    boy.shoot(&boy);
    CHECK(old.getHitPoints() == 90);
    boy.reload();
    CHECK(boy.getAmountOfBalls() == 6);
    boy.shoot(&boy);
    CHECK(old.getHitPoints() == 80);
}
TEST_CASE("old ninja Fighting")
{
    Point point(0, 0);
    Cowboy boy("ori", point);
    OldNinja old("ori", point);

    Team newTeam1(&old);
    Team newTeam2(&boy);
    old.slash(&boy);
    CHECK(boy.getHitPoints() == 87);
    CHECK(old.getHitPoints() == 150);

    Point point2(5, 5);
    OldNinja old2("ori", point);
    newTeam1.add(&old2);
    old.slash(&boy);
    CHECK(boy.getHitPoints() == 87); // he is too far away
}
TEST_CASE("Young ninja Fighting")
{
    Point point(0, 0);
    Cowboy boy("ori", point);
    YoungNinja Young("ori", point);

    Team newTeam1(&Young);
    Team newTeam2(&boy);
    Young.slash(&boy);
    CHECK(boy.getHitPoints() == 87);
    CHECK(Young.getHitPoints() == 100);

    Point point2(5, 5);
    YoungNinja YoungNinja2("ori", point);
    newTeam1.add(&YoungNinja2);
    YoungNinja2.slash(&boy);
    CHECK(boy.getHitPoints() == 87); // he is too far away
}
TEST_CASE("old ninja Fighting")
{
    Point point(0, 0);
    Cowboy boy("ori", point);
    TrainedNinja Trained("ori", point);

    Team newTeam1(&Trained);
    Team newTeam2(&boy);
    Trained.slash(&boy);
    CHECK(boy.getHitPoints() == 87);
    CHECK(Trained.getHitPoints() == 150);

    Point point2(5, 5);
    TrainedNinja Trained2("ori", point);
    newTeam1.add(&Trained2);
    Trained2.slash(&boy);
    CHECK(boy.getHitPoints() == 87); // he is too far away
}
TEST_CASE("the cowboy try to Load the gun with more than 6 bullets")
{
    Point point(0, 0);
    Cowboy boy("ori", point);
    OldNinja old("ori", point);

    Team newTeam1(&old);
    Team newTeam2(&boy);
    boy.shoot(&boy);
    boy.shoot(&boy);
    boy.shoot(&boy);
    CHECK(boy.getAmountOfBalls() == 3);
    CHECK(boy.hasBullets() == true);
    boy.reload();
    CHECK(boy.getAmountOfBalls() == 6);
}
TEST_CASE("try to add a team more than 10 fighters")
{
    Point point(0, 0);
    Cowboy boy1("ori", point);
    Cowboy boy2("ori", point);
    OldNinja boy3("ori", point);
    OldNinja boy4("ori", point);
    TrainedNinja boy5("ori", point);
    TrainedNinja boy6("ori", point);
    YoungNinja boy7("ori", point);
    YoungNinja boy8("ori", point);
    Cowboy boy9("ori", point);
    Cowboy boy10("ori", point);

    Cowboy boy11("ori", point);
    Team newTeam(&boy1);
    newTeam.add(&boy2);
    newTeam.add(&boy3);
    newTeam.add(&boy4);
    newTeam.add(&boy5);
    newTeam.add(&boy6);
    newTeam.add(&boy7);
    newTeam.add(&boy8);
    newTeam.add(&boy9);
    newTeam.add(&boy10);
    newTeam.add(&boy11);
    CHECK(newTeam.stillAlive() == 10);
}
TEST_CASE("try to add player 1 to 2 different teams")
{
    Point point(0, 0);
    Cowboy boy1("ori", point);
    Team newTeam1(&boy1);

    CHECK_THROWS(Team(&boy1)); // creat new grup

    Cowboy boy2("ori", point);
    Team newTeam2(&boy2);
    CHECK_THROWS(newTeam2.add(&boy1)); // to exist grup
}
TEST_CASE("try to add the same player twise")
{
    Point point(0, 0);
    Cowboy boy1("ori", point);
    Team newTeam1(&boy1);
    CHECK_THROWS(newTeam1.add(&boy1));
}
TEST_CASE("full attack")
{
    Point point(0, 0);
    Point pointChif(2, 2);
    Point pointAtack(1, 1);

    Cowboy boy1("ori", point);
    Cowboy boy2("ori", pointChif); // the chif of team2
    OldNinja boy3("ori", point);
    OldNinja boy4("ori", pointAtack); // the on they need to kill
    TrainedNinja boy5("ori", point);
    TrainedNinja boy6("ori", point);

    Team newTeam1(&boy1);
    Team newTeam2(&boy2);

    newTeam1.add(&boy3);
    newTeam2.add(&boy4);
    newTeam1.add(&boy5);
    newTeam2.add(&boy6);

    /*
    newTeam1 =
    chif = boy1
    boy3 ,boy5
    (odd)

    newTeam2 =
    chif = boy
    boy4 ,boy6

    */
    newTeam1.attack(&newTeam2);
    CHECK(boy4.getHitPoints() == 60); // 1 C and 2 N try to kill him -> -36 points
    CHECK(boy6.getHitPoints() == 120);
    CHECK(boy1.getAmountOfBalls() == 5);

    for (int i = 0; i < 5; i++)
    {
        boy1.shoot(&boy4);
    }
    CHECK(boy1.getAmountOfBalls() == 0);
    CHECK(boy1.hasBullets() == false);
    CHECK(boy4.getHitPoints() == 10);

    newTeam1.attack(&newTeam2);
    CHECK(boy4.getHitPoints() == 0); // 2 N try to kill him -> -80 points (the cowboy jast Load the gun)
    CHECK(boy6.getHitPoints() == 120);
    CHECK(boy1.getAmountOfBalls() == 6);
    CHECK(newTeam2.stillAlive() == 2);
}
TEST_CASE("the players get closer")
{
    Point pointChif(20, 20);
    Point point1(10, 10);
    Point point2(3, 4);
    Point point3(0, 0);

    OldNinja theChif1("ori", pointChif);
    OldNinja soldier1("ori", point1); // to kill
    OldNinja soldier2("ori", point2);
    OldNinja theKiller1("ori", point3);
    YoungNinja theKiller2("ori", point3);
    OldNinja theChif2("ori", Point(100, 100));

    Team newTeam1(&theChif1);
    Team newTeam2(&theChif2);
    newTeam1.add(&soldier1);
    newTeam1.add(&soldier2);
    newTeam2.add(&theKiller1);
    newTeam2.add(&theKiller2);

    newTeam2.attack(&newTeam1);
    CHECK((theKiller1.getLocation().getX() + theKiller1.getLocation().getX()) == 8);
    CHECK((theKiller2.getLocation().getX() + theKiller2.getLocation().getX()) == 14);

    newTeam2.attack(&newTeam1);
    CHECK(theKiller1.getLocation().getX() == 10);
    CHECK(theKiller1.getLocation().getY() == 10);
    CHECK(soldier1.getHitPoints() == 110);
}
TEST_CASE("A player tries to kill when he himself is dead /A player tries to kill a dead player")
{

    Point point(0, 0);
    OldNinja soldier1("ori", point);
    OldNinja soldier2("ori", point);
    Cowboy soldier3("ori", point);

    Team newTeam1(&soldier1);
    Team newTeam2(&soldier2);

    for (int i = 0; i < 12; i++)
    {
        newTeam2.attack(&newTeam1);
    }
    CHECK_THROWS(soldier2.slash(&soldier1));
    CHECK_THROWS(soldier1.slash(&soldier3));
}
