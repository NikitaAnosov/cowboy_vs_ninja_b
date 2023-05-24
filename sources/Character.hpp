#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "Point.hpp"
using std::cout;
using std::endl;
using std::runtime_error;
namespace ariel
{
    class Character
    {
    private:
        string _name;
        Point _location;
        int _hp;
        bool characterInTeam = false;

    public:
        // constructor:
        Character(); // default
        Character(string name, Point location, int HealthPoints);
        //__for tidy test __
        virtual ~Character() = default;                        // destructor
        Character(const Character &other) = delete;            // Deleted copy constructor
        Character &operator=(const Character &other) = delete; // Deleted copy assignment operator
        Character(Character &&other) = delete;                 // Deleted move constructor
        Character &operator=(Character &&other) = delete;      // Deleted move assignment operator
        // -----------------
        // gettes
        string getName() const { return _name; }        // inline
        Point getLocation() const { return _location; } // inline
        int getHp() const { return _hp; }               // inline
        // boolians
        bool isAlive() const { return (_hp > 0); } // inline
        bool checkCharacterInTeam() const { return characterInTeam; }
        // settes for Ninja class (move func)
        void setCharacterInTeam(bool charcter) { characterInTeam = charcter; }
        void setLocation(Point location) { _location = location; }
        // functions
        double distance(Character *destCharacter) const;
        void hit(int hitPoints);
        virtual string print() const;
    };
}
#endif
