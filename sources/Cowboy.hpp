#ifndef COWBOY_HPP
#define COWBOY_HPP
#include "Character.hpp"
namespace ariel
{
    class Cowboy : public Character
    {
    private:
        int _bulletsAmount;

    public:
        // constructor:
        Cowboy(string name, Point location);
        // functions
        void shoot(Character *enemy);
        bool hasboolets() const {return (_bulletsAmount > 0);}
        void reload();
        // getters
        int getBullets() const {return _bulletsAmount;}
        string print() const override;
    };

}
#endif