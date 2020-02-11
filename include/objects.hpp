#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <algorithm>
#include "point3D.hpp"

#ifndef NO_HIT
#define NO_HIT  \
    {           \
        0, 0, 0 \
    }
#endif
enum texture
{
    PLAIN,
    TEXTURE2,
    TEXTURE3,
    TEXTURE4
};
enum geometry
{
    CUBE,
    TRIANGLE,
    RECTANGLE,
    SPHERE,
    PLAN
};

struct surface
{
    enum texture text; //Texture de la surface
    int colorR;
    int colorG;
    int colorB;
    float shininess;    //Brillance de la surface
    float reflexion;    //Coef de reflexion de la structureentre 0 et 1
    float transparency; //Coef de transp entre 0 et 1
};
typedef struct surface surface;

class Object
{
    // Un objet est défini par une surface et une géométrie
    // Variables
protected:
    surface self_surface;
    enum geometry self_geometry;

public:
    // En tete de fonctions et méthodes
    enum geometry getGeometry() { return self_geometry; };
    surface getSurfaceProperties() { return self_surface; };

    // Constructeur par défaut
    virtual Point3D hit(Point3D ray_origin, Point3D ray_direction)
    {

        std::cerr << "no hit available for base class" << std::endl;
        return (ray_origin - ray_direction) * 0;
    };
    virtual Point3D getNormale()
    {
        std::cerr << "no normal available for basic object" << std::endl;
        return NO_HIT;
    }
    virtual Point3D getNormale(Point3D pointIntersect)
    {
        std::cerr << "no normal available for basic object" << std::endl;
        return pointIntersect * 0;
    }
    Object()
    {
        self_surface.text = PLAIN;
        self_surface.reflexion = 0;
        self_surface.transparency = 0;
    };

    // Constructeur explicite
    explicit Object(surface new_surface)
    {
        self_surface = new_surface;
    };

    Object(geometry new_geometry)
    {
        self_geometry = new_geometry;
    }
    Object(surface new_surface, geometry new_geometry)
    {
        self_surface = new_surface;
        self_geometry = new_geometry;
    }

    // Recopie

    Object(const Object &other)
    {
        self_surface = other.self_surface;
    };

    // Destruction

    virtual ~Object(){};
};

class Sphere : public Object
{
private:
    float rayon;
    Point3D centre;

public:
    Sphere() : Object(SPHERE), rayon(1), centre{0, 0, 0} {}; // Pas très propre pour le moment
    Sphere(const Sphere &other) : Object(other.self_surface, SPHERE), rayon(other.rayon), centre(other.centre){};
    explicit Sphere(float r) : Object(SPHERE), rayon(r), centre{0, 0, 0} {};
    Sphere(float r, const Point3D &c) : Object(SPHERE), rayon(r), centre(c){};
    Sphere(surface surf, float r, const Point3D &c) : Object(surf, SPHERE), rayon(r), centre(c){};
    ~Sphere(){};

    float getRay() { return rayon; };
    Point3D getPosition() const
    {
        return centre;
    };

    Point3D getNormale(const Point3D &intersection) const
    {
        return intersection - centre;
    }

    Point3D hit(const Point3D &ray_origin, const Point3D &ray_direction) const
    {
        Point3D l = ray_origin - centre; // o - c

        float b = 2 * (l * ray_direction);
        float a = ray_direction * ray_direction;
        float c = l * l - rayon * rayon;

        float discr = b * b - 4 * a * c;

        if (discr < 0)
        {
            return Point3D(0, 0, 0);
        }
        if (discr == 0)
            return ray_origin - ray_direction * (b / (2 * a));
        else
            return (ray_origin - ray_direction * ((b + sqrt(discr)) / (2 * a))).min_dist(ray_origin - ray_direction * ((b - sqrt(discr)) / (2 * a)), ray_origin);
    };

    void operator=(const Sphere &anotherSphere)
    {
        rayon = anotherSphere.rayon;
        centre = anotherSphere.centre;
        self_surface = anotherSphere.self_surface;
    };
};

class Plan : public Object
{
private:
    const Point3D normale; // C'est un point 3D par simplicité mais  c'est en réalité pour une normale
    const Point3D p;

public:
    Plan() : Object(PLAN), normale{1, 1, 1}, p{0, 0, 0} {};
    Plan(const Plan &otherPlan) : Object(PLAN), normale(otherPlan.getNormale()), p(otherPlan.getPoint()){};
    Plan(const Point3D &n, const Point3D &o) : Object(PLAN), normale(n), p(o){};
    Plan(surface surf, Point3D n, const Point3D &o) : Object(surf, PLAN), normale(n), p(o){};
    Point3D getNormale() const
    {
        return normale;
    }
    Point3D getPoint() const
    {
        return p;
    }
    Point3D getNormale(const Point3D &intersection) override
    {
        return normale - intersection * 0;
    }

    Point3D hit(const Point3D &ray_origin, const Point3D &ray_direction)
    {
        float d = -normale.dotProduct(p); //Plane has equation ax+by+cz+d=0 where (a,b,c) is the normal vector and (x,y,z) a point in the plane

        float t = (float)-(ray_origin.dotProduct(normale) + d) / normale.dotProduct(ray_direction);
        return ray_origin + ray_direction * t;
    };

    ~Plan(){};
};
// class Cube : public Object
// {
// private:
//     float arete;
//     Point3D top_front_left_corner;

// public:
//     Cube() : arete(1), top_front_left_corner{0, 0, 0}, Object(CUBE){};
//     Cube(const Cube &other) : arete(other.arete), top_front_left_corner(other.top_front_left_corner), Object(other){};
//     explicit Cube(float a) : arete(a), top_front_left_corner{0, 0, 0}, Object(CUBE){};
//     Cube(float a, Point3D c) : arete(a), top_front_left_corner(c), Object(CUBE){};
//     // ~Cube() { std::cout << "Destruction du cube";};

//     float getArete() { return arete; };
//     Point3D getPosition() { return top_front_left_corner; };
// };

// class Rectangle : public Object
// {
// private:
//     const Point3D dimensions;
//     Point3D top_front_left_corner;

// public:
//     Rectangle() : dimensions{1, 2, 3}, top_front_left_corner{0, 0, 0}, Object(RECTANGLE){};
//     Rectangle(const Rectangle &other) : dimensions(other.dimensions), top_front_left_corner(other.top_front_left_corner), Object(other){};
//     explicit Rectangle(const Point3D dim) : dimensions(dim), top_front_left_corner{0, 0, 0}, Object(RECTANGLE){};
//     Rectangle(const Point3D dim, Point3D c) : dimensions(dim), top_front_left_corner(c), Object(RECTANGLE){};
//     // ~Rectangle() { std::cout << "Destruction du rectangle";};

//     const Point3D getDim() { return dimensions; };
//     Point3D getPosition() { return top_front_left_corner; };
// };

// class Triangle : public Object //Equilatéral
// {
// private:
//     float arete;
//     Point3D top;

// public:
//     Triangle() : arete(1), top{0, 0, 0}, Object(TRIANGLE){};
//     Triangle(const Triangle &other) : arete(other.arete), top(other.top), Object(other){};
//     explicit Triangle(float a) : arete(a), top{0, 0, 0}, Object(TRIANGLE){};
//     Triangle(float a, Point3D c) : arete(a), top(c), Object(TRIANGLE){};
//     // ~Triangle() { std::cout << "Destruction du triangle";};

//     float getArete() { return arete; };
//     Point3D getPosition() { return top; };
// };

#endif