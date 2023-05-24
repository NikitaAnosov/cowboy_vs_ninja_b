#include "Ninja.hpp"
using namespace ariel;

Ninja::Ninja() : Character(), _speed(0) {}
Ninja::Ninja(string name, Point location, int HealthPoints, int speed) : Character(name, location, HealthPoints), _speed(speed) {}

void Ninja::move(Character *enemy)
{
    if (isAlive() == false)
    {
        throw runtime_error("can't move while dead");
    }
    Point dest = getLocation().moveTowards(this->getLocation(), enemy->getLocation(), _speed);
    setLocation(dest);
}

void Ninja::slash(Character *enemy)
{
    if (enemy->isAlive() == false)
    {
        throw runtime_error("can't slash a dead enemy");
    }
    if (isAlive() == false)
    {
        throw runtime_error("can't slash while dead");
    }

    if (this == enemy)
    {
        throw runtime_error("can't slash yourself");
    }

    if (distance(enemy) < 1 && isAlive() == true) // min 1 meter from the enemy
    {
        enemy->hit(40); // 20 damage
    }
}

string Ninja::print() const
{
    string print = "";
    print += "Ninja: " + Character::print();
    return print;
}

// charaters
YoungNinja::YoungNinja(string name, Point location) : Ninja(name, location, 100, 14) {}
TrainedNinja::TrainedNinja(string name, Point location) : Ninja(name, location, 120, 12) {}
OldNinja::OldNinja(string name, Point location) : Ninja(name, location, 150, 8) {}
