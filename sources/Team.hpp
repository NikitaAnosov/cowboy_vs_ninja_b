#ifndef TEAM_HPP
#define TEAM_HPP
#include "Ninja.hpp"
#include "Cowboy.hpp"
#include <vector>
#include <float.h>
using std::vector;
namespace ariel
{
    class Team
    {
    private:
        vector<Character *> _teamMembers;
        Character *_leader;
    public:
        // constructor:
        Team(Character *leader);
        virtual ~Team(); // destructor
        //__for tidy test __
        Team(const Team &other) = delete;            // Deleted copy constructor
        Team &operator=(const Team &other) = delete; // Deleted copy assignment operator
        Team(Team &&other) = delete;                 // Deleted move constructor
        Team &operator=(Team &&other) = delete;      // Deleted move assignment operator
        // -----------------
        // getters
        Character* getLeader() const { return _leader; }//get the leader
        virtual Character* getCharacterToKill(Team *Enemyteam_character) const;//get the closest alive character to the leader
        vector<Character *> getTeamMembers() const { return _teamMembers; }//get the team members
        // setters
        void setNewLeader();// if leader is dead, set new leader
        void setLeader(Character *leader){ _leader = leader;}
        // functions
        void add(Character *charater);
        virtual void attack(Team *enemyTeam);
        int stillAlive() const;
        virtual void print() const;
    };

    class Team2 : public Team
    {
    public:
        Team2(Character *leader);
        void attack(Team *enemyTeam) override;
        void print() const override;
    };

    class SmartTeam : public Team
    {
    public:
        SmartTeam(Character *leader);
        Character* getCharacterToKill(Team *Enemyteam_character) const override;
        void attack(Team *enemyTeam) override;
        // void print() const override;
    };
}
#endif