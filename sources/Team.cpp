#include "Team.hpp"
using namespace ariel;

Team::Team(Character *leader)
{
    if (leader == nullptr)
    {
        throw invalid_argument("leader can't be nullptr");
    }
    if (leader->checkCharacterInTeam())
    {
        throw runtime_error("leader already exist in the team");
    }
    setLeader(leader);
    leader->setCharacterInTeam(true);
    _teamMembers.push_back(leader);
}

Team::~Team()
{
    for (size_t i = 0; i < _teamMembers.size(); i++)
    {
        delete _teamMembers.at(i);
    }
}

Character *Team::getCharacterToKill(Team *Enemyteam_character) const
{
    Character *character;
    ;
    double minDistance = DBL_MAX; // max double value
    for (size_t i = 0; i < Enemyteam_character->_teamMembers.size(); i++)
    {
        if (Enemyteam_character->_teamMembers.at(i)->isAlive() && Enemyteam_character->_teamMembers.at(i)->distance(this->getLeader()) < minDistance)
        {
            minDistance = Enemyteam_character->_teamMembers.at(i)->distance(this->getLeader());
            character = Enemyteam_character->_teamMembers.at(i);
        }
    }
    return character;
}

void Team::add(Character *charater)
{
    if (_teamMembers.size() >= 10)
    {
        throw runtime_error("team is full");
    }
    if (charater == nullptr)
    {
        throw invalid_argument("charater can't be nullptr");
    }
    if (charater->checkCharacterInTeam() == true)
    {
        throw runtime_error("charater already exist in the team");
    }
    _teamMembers.push_back(charater);
    charater->setCharacterInTeam(true);
}

void Team::setNewLeader()
{
    Character *character = nullptr;
    double minDistance = DBL_MAX; // max double value
    for (size_t i = 0; i < _teamMembers.size(); i++)
    {
        if (_teamMembers.at(i)->isAlive() && _teamMembers.at(i)->distance(_leader) < minDistance)
        {
            minDistance = _teamMembers.at(i)->distance(_leader);
            character = _teamMembers.at(i);
        }
    }
    setLeader(character); // set the closest alive character to be the leader
}

void Team::attack(Team *enemyTeam)
{
    if (enemyTeam == nullptr)
    {
        throw invalid_argument("enemyTeam can't be nullptr");
    }
    if (enemyTeam == this)
    {
        throw runtime_error("can't attack yourself");
    }
    if (enemyTeam->stillAlive() == 0)
    {
        throw runtime_error("enemyTeam is empty");
    }
    // if the leader is dead, we need to choose a new leader
    if (_leader->isAlive() == false)
    {
        setNewLeader();
    }
    Character *characterToKill = getCharacterToKill(enemyTeam); // get the closest alive character to the leader in the enemy team
    // start: cowboys shoot/reload after ninja slash/move
    // cowboy attack
    for (size_t i = 0; i < _teamMembers.size(); i++)
    {
        if (enemyTeam->stillAlive() == 0) // if the enemy team is empty(we killed all the enemy team)
        {
            return;
        }

        Cowboy *cowboy = dynamic_cast<Cowboy *>(_teamMembers.at(i));
        if (cowboy != nullptr && cowboy->isAlive())
        {
            if (characterToKill->isAlive() == false)
            {
                characterToKill = getCharacterToKill(enemyTeam);
            }
            if (cowboy->hasboolets() == false)
            {
                cowboy->reload();
            }
            else
            {
                cowboy->shoot(characterToKill);
            }
        }
    }

    // ninja attack
    for (size_t i = 0; i < _teamMembers.size(); i++)
    {
        if (enemyTeam->stillAlive() == 0) // if the enemy team is empty(we killed all the enemy team)
        {
            return;
        }
        Ninja *ninja = dynamic_cast<Ninja *>(_teamMembers.at(i));
        if (ninja != nullptr && ninja->isAlive())
        {
            if (characterToKill->isAlive() == false)
            {
                characterToKill = getCharacterToKill(enemyTeam);
            }
            if (ninja->distance(characterToKill) >= 1)
            {
                ninja->move(characterToKill);
            }
            else
            {
                ninja->slash(characterToKill);
            }
        }
    }
}

int Team::stillAlive() const
{
    int teamSIZE = _teamMembers.size();
    int countStillAlive = 0;
    for (size_t i = 0; i < teamSIZE; i++)
    {
        // check all members in the team if they alive
        if (_teamMembers.at(i)->isAlive())
        {
            countStillAlive++;
        }
    }
    return countStillAlive;
}

void Team::print() const
{
    cout << "\nTeam leader: " << _leader->print() << endl;
    for (size_t i = 0; i < _teamMembers.size(); i++)
    {
        Cowboy *cowboy = dynamic_cast<Cowboy *>(_teamMembers.at(i));
        if (cowboy != nullptr)
        {
            cout << _teamMembers.at(i)->print() << endl;
        }
    }
    for (size_t i = 0; i < _teamMembers.size(); i++)
    {
        Ninja *ninja = dynamic_cast<Ninja *>(_teamMembers.at(i));
        if (ninja != nullptr)
        {
            cout << _teamMembers.at(i)->print() << endl;
        }
    }
}

// Team2
Team2::Team2(Character *leader) : Team(leader) {} // same as Team

void Team2::attack(Team *enemyTeam)
{
    if (enemyTeam == nullptr)
    {
        throw invalid_argument("enemyTeam can't be nullptr");
    }
    if (enemyTeam == this)
    {
        throw runtime_error("can't attack yourself");
    }
    if (enemyTeam->stillAlive() == 0)
    {
        throw runtime_error("enemyTeam is empty");
    }
    // if the leader is dead, we need to choose a new leader
    if (getLeader()->isAlive() == false)
    {
        setNewLeader();
    }
    Character *characterToKill = getCharacterToKill(enemyTeam); // get the closest alive character to the leader in the enemy team
    // start: attack in order the members in the team
    for (size_t i = 0; i < getTeamMembers().size(); i++)
    {
        if (enemyTeam->stillAlive() == 0) // if the enemy team is empty(we killed all the enemy team)
        {
            return;
        }
        Cowboy *cowboy = dynamic_cast<Cowboy *>(getTeamMembers().at(i));
        Ninja *ninja = dynamic_cast<Ninja *>(getTeamMembers().at(i));

        if (characterToKill->isAlive() == false)
        {
            characterToKill = getCharacterToKill(enemyTeam);
        }

        if (cowboy != nullptr && cowboy->isAlive())
        {
            if (cowboy->hasboolets() == false)
            {
                cowboy->reload();
            }
            else
            {
                cowboy->shoot(characterToKill);
            }
        }

        if (ninja != nullptr && ninja->isAlive())
        {
            if (ninja->distance(characterToKill) >= 1)
            {
                ninja->move(characterToKill);
            }
            else
            {
                ninja->slash(characterToKill);
            }
        }
    }
}

void Team2::print() const
{
    cout << "\nTeam2 leader: " << getLeader()->print() << endl;
    for (size_t i = 0; i < getTeamMembers().size(); i++)
    {
        cout << getTeamMembers().at(i)->print() << endl;
    }
}

// smartTeam

SmartTeam::SmartTeam(Character *leader) : Team(leader) {} // same as Team

void SmartTeam::attack(Team *enemyTeam)
{
    if (enemyTeam == nullptr)
    {
        throw invalid_argument("enemyTeam can't be nullptr");
    }
    if (enemyTeam == this)
    {
        throw runtime_error("can't attack yourself");
    }
    if (enemyTeam->stillAlive() == 0)
    {
        throw runtime_error("enemyTeam is empty");
    }
    // if the leader is dead, we need to choose a new leader
    if (getLeader()->isAlive() == false)
    {
        setNewLeader();
    }
    Character *characterToKill = getCharacterToKill(enemyTeam); // get the closest alive character to the leader in the enemy team
    // start: attack in order the members in the team
    for (size_t i = 0; i < getTeamMembers().size(); i++)
    {
        if (enemyTeam->stillAlive() == 0) // if the enemy team is empty(we killed all the enemy team)
        {
            return;
        }
        Cowboy *cowboy = dynamic_cast<Cowboy *>(getTeamMembers().at(i));
        Ninja *ninja = dynamic_cast<Ninja *>(getTeamMembers().at(i));

        if (characterToKill->isAlive() == false)
        {
            characterToKill = getCharacterToKill(enemyTeam);
        }

        if (cowboy != nullptr && cowboy->isAlive())
        {
            if (cowboy->hasboolets() == false)
            {
                cowboy->reload();
            }
            else
            {
                cowboy->shoot(characterToKill);
            }
        }

        if (ninja != nullptr && ninja->isAlive())
        {
            if (ninja->distance(characterToKill) >= 1)
            {
                ninja->move(characterToKill);
            }
            else
            {
                ninja->slash(characterToKill);
            }
        }
    }
}
// now it will find character with the lowest health and the closest to the leader
Character *SmartTeam::getCharacterToKill(Team *enemyTeam) const
{
    if (enemyTeam == nullptr)
    {
        throw invalid_argument("enemyTeam can't be nullptr");
    }
    if (enemyTeam->stillAlive() == 0)
    {
        throw runtime_error("enemyTeam is empty");
    }
    Character *characterToKill = enemyTeam->getLeader();
    int minDistance = getLeader()->distance(characterToKill);
    int minHealth = 200; // max health cauld be 150
    for (size_t i = 0; i < enemyTeam->getTeamMembers().size(); i++)
    {
        if (enemyTeam->getTeamMembers().at(i)->isAlive())
        {
            int characterHealth = enemyTeam->getTeamMembers().at(i)->getHp();
            if (characterHealth < minHealth)
            {
                if (getLeader()->distance(enemyTeam->getTeamMembers().at(i)) < minDistance)
                {
                    minHealth = characterHealth;
                    minDistance = getLeader()->distance(enemyTeam->getTeamMembers().at(i));
                    characterToKill = enemyTeam->getTeamMembers().at(i);
                }
            }
        }
    }
    return characterToKill;
}
