#ifndef POINT3D_HPP
#define POINT3D_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <algorithm>

class Point3D
{
private:
    float p_X;
    float p_Y;
    float p_Z;

public:
    Point3D() : p_X(0), p_Y(0), p_Z(0){};
    Point3D(int x, int y, int z) : p_X(x), p_Y(y), p_Z(z){};
    Point3D(float x, float y, float z) : p_X(x), p_Y(y), p_Z(z){};
    Point3D(const Point3D &point) : p_X(point.getX()), p_Y(point.getY()), p_Z(point.getZ()){};

    float getX() const
    {
        return p_X;
    }
    float getY() const
    {
        return p_Y;
    }
    float getZ() const
    {
        return p_Z;
    }

    void operator=(const Point3D &anotherPoint)
    {
        p_X = anotherPoint.p_X;
        p_Y = anotherPoint.p_Y;
        p_Z = anotherPoint.p_Z;
    };

    bool operator!=(const Point3D &anotherPoint) const
    {
        return (p_X != anotherPoint.getX() || p_Y != anotherPoint.getY() || p_Z != anotherPoint.getZ());
    }
    bool operator==(const Point3D &anotherPoint) const
    {
        return (p_X == anotherPoint.getX() && p_Y == anotherPoint.getY() && p_Z == anotherPoint.getZ());
    }
    Point3D operator*(float t) const;
    friend Point3D operator*(float t, const Point3D point);
    float operator*(const Point3D &anotherPoint) const
    {
        return (p_X * anotherPoint.getX() + p_Y * anotherPoint.getY() + p_Z * anotherPoint.getZ());
    }
    Point3D operator+(const Point3D &point) const
    {
        return Point3D(p_X + point.getX(), p_Y + point.getY(), p_Z + point.getZ());
    }
    Point3D operator-(const Point3D &point) const
    {
        return Point3D(p_X - point.getX(), p_Y - point.getY(), p_Z - point.getZ());
    }
    float dotProduct(const Point3D anotherPoint) const
    {
        return (p_X * anotherPoint.getX() + p_Y * anotherPoint.getY() + p_Z * anotherPoint.getZ());
    }
    void normalize() {
        float norm = sqrt(p_X*p_X+p_Y*p_Y+p_Z*p_Z);
        p_X/=norm;
        p_Y/=norm;
        p_Z/=norm;
    }
    // calcul de distance à l'origine (pour trouver le plus près plus tard) (pour le mmoment l'origine est en (0,0,0) et on considère cela connu.)
    Point3D min_dist(const Point3D &anotherPoint, const Point3D &origin)
    {
        float a = (*this - origin).dotProduct(*this - origin);
        float b = (anotherPoint - origin).dotProduct(anotherPoint - origin);
        if (a < b)
            return *this;
        else
            return anotherPoint;
    }
};
Point3D Point3D::operator*(float t) const
{
    return Point3D(p_X * t, p_Y * t, p_Z * t);
}
Point3D operator*(float t, const Point3D point)
{
    return Point3D(point.getX() * t, point.getY() * t, point.getZ() * t);
}

#endif