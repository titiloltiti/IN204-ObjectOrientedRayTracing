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
{ //Pour l'instant la source sera omnidirectionnelle
private:
    Point3D position;
    Point3D color;
    float intensity; //entre 0 et 1
public:
    Source() : position{10, 10, -10}, color{255, 255, 255}, intensity(1){};

    // Constructeur explicite (on pourrait en mettre d'autres)
    explicit Source(Point3D pos) : position(pos), color{255, 255, 255}, intensity(1){};

    // Recopie

    Source(const Source &other)
    {
        position = other.position;
        color = other.color;
        intensity = other.intensity;
    }

    // Destruction

    ~Source()
    {
        // std::cout << "Destruction de la source" << std::endl;
    }

    Point3D getColor()
    {
        return color;
    };
    Point3D getPosition() { return position; };
    float getIntensity() { return intensity; };
};

#endif