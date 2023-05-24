#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>
#include <string>
#include <cmath>
using std::string;
using std::to_string;
using std::invalid_argument;
namespace ariel
{
    class Point
    {
    private:
        double _xPoint, _yPoint;

    public:
        // constructors:
        Point() : _xPoint(0), _yPoint(0) {}
        Point(double xPoint, double yPoint) : _xPoint(xPoint), _yPoint(yPoint) {}  // default
        
        // gettes
        double getX() const { return _xPoint; }//inline
        double getY() const { return _yPoint; } //inline
        // functions
        double distance(const Point &otherPoint) const;
        string print() const{ return "(" + to_string(getX())+ ", " + to_string(getY()) + ")" ;}
        static Point moveTowards(const Point &originPoint, const Point &destPoint, double dist);
    };
}
#endif