#include "Point.hpp"
using namespace ariel;

double Point::distance(const Point &otherPoint) const
{
    double dist_x = _xPoint - otherPoint._xPoint;
    double dist_y = _yPoint - otherPoint._yPoint;
    return sqrt(dist_x * dist_x + dist_y * dist_y);
}

Point Point::moveTowards(const Point &originPoint, const Point &destPoint, double dist)
{
    if (dist < 0)
    {
        throw invalid_argument("distance can't be negative");
    }
    
    double dist_pointTOpoint = originPoint.distance(destPoint);
    if (dist_pointTOpoint <= dist)
        return destPoint;
    else
    {
        double ratio = dist / dist_pointTOpoint ;
        double dist_x = destPoint._xPoint - originPoint._xPoint;
        double dist_y = destPoint._yPoint - originPoint._yPoint;
        double dist_x2 = originPoint._xPoint + dist_x * ratio;
        double dist_y2 = originPoint._yPoint + dist_y * ratio;
        return Point(dist_x2, dist_y2);
    }
}
