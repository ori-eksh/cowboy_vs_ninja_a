#pragma once
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include <vector>
namespace ariel
{
    class Team
    {
    private:
        Character *chief;
        std::vector<Character *> members;

    public:
        Team(Character *chief) : chief(chief)
        {
        }
        void add(Character *toAdd);
        virtual void attack(Team *otherTeam);
        int stillAlive();
        virtual void print();

        virtual ~Team()
        {
            delete chief;
            chief = nullptr;
            for (auto *member : members)
            {
                delete member;
            }
            members.clear();
        }
        // Because we wrote Distractor We need to add:
        // Copy constructor, shift constructor, copy operator, shift operator
        Team(const Team &other) : chief(other.chief)
        {
            for (auto *member : other.members)
            {
                members.push_back(member);
            }
        }

        Team &operator=(const Team &other)
        {
            if (this != &other)
            {
                delete chief;
                chief = (other.chief);
                for (auto *member : members)
                {
                    delete member;
                }
                members.clear();
                for (auto *member : other.members)
                {
                    members.push_back(member);
                }
            }
            return *this;
        }

        Team(Team &&other) noexcept : chief(other.chief), members(std::move(other.members))
        {
            other.chief = nullptr;
            other.members.clear();
        }

        Team &operator=(Team &&other) noexcept
        {
            if (this != &other)
            {
                delete chief;
                chief = other.chief;
                other.chief = nullptr;

                for (auto *member : members)
                {
                    delete member;
                }
                members = std::move(other.members);
            }
            return *this;
        }
    };

    class Team2 : public Team
    {
    public:
        Team2(Character *chief) : Team(chief) {}
        void attack(Team *otherTeam) override;
        void print() override;
    };

    class SmartTeam : public Team
    {
    public:
        SmartTeam(Character *chief) : Team(chief) {}
        void attack(Team *otherTeam) override;
        void print() override;
    };
};
