#include "Character.hpp"
using namespace ariel;

Character::Character() : _name(""), _location(Point()), _hp(0) {}
Character::Character(string name, Point location, int HealthPoints) : _name(name), _location(location), _hp(HealthPoints) {}

double Character::distance(Character *destCharacter) const
{
    return _location.distance(destCharacter->getLocation());
}
void Character::hit(int hitPoints)
{
    if (hitPoints < 0)
    {
            throw invalid_argument("hitPoints can't be negative");
    }
    _hp -= hitPoints;
}
string Character::print() const
{
    string print = "";
    print += "name: " + _name + ", hp: " + to_string(getHp()) + ", location: " + _location.print();
    return print;
}

