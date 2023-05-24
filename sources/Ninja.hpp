#ifndef NINJA_HPP
#define NINJA_HPP
#include "Character.hpp"
namespace ariel
{
    class Ninja: public Character
    {
    private:
        int _speed;

    public:
        // constructor:
        Ninja(); // default
        Ninja(string name, Point location, int HealthPoints, int speed);
        // functions
        virtual void move(Character *enemy);
        virtual void slash(Character *enemy);
        string print() const override;
        // gettes
        int getSpeed() const {return _speed; }
    };

    class YoungNinja: public Ninja
    {
    public:
        YoungNinja(string name, Point location);
    };

    class TrainedNinja: public Ninja
    {
    public:
        TrainedNinja(string name, Point location);
    };
    class OldNinja: public Ninja
    {
    public:
        OldNinja(string name, Point location);
    };
}
#endif