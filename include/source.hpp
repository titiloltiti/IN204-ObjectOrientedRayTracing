#ifndef SOURCE_HPP
#define SOURCE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <algorithm>
#include "point3D.hpp"

class Source
{ //Pour l'instant la source sera unidirectionnelle (comme le soleil)
private:
    Point3D direction;
    Point3D color;
    float intensity; //entre 0 et 1
public:
    Source() : direction{-500, -500, 0}, color{255, 255, 255}, intensity(1) { direction.normalize(); }; // The default direction is a bit random yet

    // Constructeur explicite (on pourrait en mettre d'autres)
    explicit Source(const Point3D &dir) : direction(dir), color{255, 255, 255}, intensity(1){};

    // Recopie

    Source(const Source &other)
    {
        direction = other.direction;
        color = other.color;
        intensity = other.intensity;
    }

    // Destruction

    ~Source()
    {
        // std::cout << "Destruction de la source" << std::endl;
    }

    Point3D getColor() const
    {
        return color;
    };
    Point3D getDirection() const
    {
        return direction;
    };
    float getIntensity() const
    {
        return intensity;
    };
};

#endif