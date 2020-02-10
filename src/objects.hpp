#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <algorithm>
#include "point3D.hpp"

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
    // virtual Point3D getNormale();
    // virtual Point3D hit(Ray ray);
    // Constructeur par défaut
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

    // Recopie

    Object(const Object &other)
    {
        self_surface = other.self_surface;
    };

    // Destruction

    ~Object(){};
};

class Sphere : public Object
{
private:
    float rayon;
    Point3D centre;

public:
    Sphere() : Object(), rayon(1), centre{0, 0, 0} { self_geometry = SPHERE; }; // Pas très propre pour le moment
    Sphere(const Sphere &other) : Object(other.self_surface), rayon(other.rayon), centre(other.centre) { self_geometry = SPHERE; };
    explicit Sphere(float r) : Object(), rayon(r), centre{0, 0, 0} { self_geometry = SPHERE; };
    Sphere(float r, Point3D c) : Object(), rayon(r), centre(c) { self_geometry = SPHERE; };
    Sphere(surface surf, float r, Point3D c) : Object(surf), rayon(r), centre(c){};
    ~Sphere(){};

    float getRay() { return rayon; };
    Point3D getPosition() { return centre; };

    Point3D getNormale(Point3D intersection)
    {
        return intersection - centre;
    }

    // Point3D hit(Ray r);
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
    Plan() : Object(), normale{1, 1, 1}, p{0, 0, 0} { self_geometry = PLAN; };
    Plan(const Plan &otherPlan) : Object(), normale(otherPlan.getNormale()), p(otherPlan.getPoint()) { self_geometry = PLAN; };
    Plan(Point3D n, Point3D o) : Object(), normale(n), p(o) { self_geometry = PLAN; };
    Plan(surface surf, Point3D n, Point3D o) : Object(surf), normale(n), p(o){};
    Point3D getNormale() const
    {
        return normale;
    }
    Point3D getPoint() const
    {
        return p;
    }
    Point3D getNormale(Point3D intersection)
    {
        return normale;
    }
    // Point3D hit(Ray r);

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