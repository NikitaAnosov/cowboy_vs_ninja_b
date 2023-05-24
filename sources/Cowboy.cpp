#include "Cowboy.hpp"
using namespace ariel;

Cowboy::Cowboy(string name, Point location) : Character(name, location, 110), _bulletsAmount(6){}

void Cowboy::shoot(Character *enemy) 
{
    if (this == enemy)
    {
        throw runtime_error("can't shoot yourself");
    }
    if (this->isAlive() == false)
    {
        throw runtime_error("can't shoot while dead");
    }
    if (enemy->isAlive() == false)
    {
        throw runtime_error("can't shoot a dead enemy");
    }
    
    if (hasboolets() && isAlive())
    {
        enemy->hit(10);
        --_bulletsAmount;// --i for better performance
    }
    
}
void Cowboy::reload() 
{
    if (isAlive() == false)
    {
        throw runtime_error("can't reload while dead");
    }
    
    _bulletsAmount = 6 ;
}

string Cowboy::print() const
{
    string print = "";
    print += "Cowboy: " + Character::print();
    return print;
}