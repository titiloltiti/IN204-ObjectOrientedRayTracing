#include "shapes.hpp"
#include <math.h>
// Point3D Ray::hit(Object obj)
// {
// }

Point3D Ray::hit(Sphere s)
{
    Point3D l = source_position - s.getPosition(); // o - c
    Point3D d = direction;
    float r = s.getRay();

    float b = 2 * (l * d);
    float a = d * d;
    float c = l * l - r * r;

    float discr = b * b - 4 * a * c;

    if (discr < 0)
    {
        return Point3D(0, 0, 0);
    }
    if (discr == 0)
        return source_position - d * (b / (2 * a));
    else
        return (source_position - d * ((b + sqrt(discr)) / (2 * a))).min_dist(source_position - d * ((b - sqrt(discr)) / (2 * a)), source_position);
}