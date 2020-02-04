#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <algorithm>

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
    float reflexion;    //Coef de reflexion de la structure entre 0 et 1
    float transparency; //Coef de transp entre 0 et 1
};
typedef struct surface surface;

class Point3D
{
private:
    float p_X;
    float p_Y;
    float p_Z;

public:
    Point3D() : p_X(0), p_Y(0), p_Z(0){};
    Point3D(int x, int y, int z) : p_X(x), p_Y(y), p_Z(z){};
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
        p_X=anotherPoint.p_X;
        p_Y=anotherPoint.p_Y;
        p_Z=anotherPoint.p_Z;
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

// class Vector {
//     private :
//         Point3D origin;
//         Point3D tip;
//     public :
//         Vector() : origin(Point3D()), tip(Point3D()) {};
//         Vector(Point3D m_origin,Point3D m_tip) : origin(m_origin), tip(m_tip) {};
//         explicit Vector(Point3D m_tip) : origin(Point3D()), tip(m_tip) {};
//         Vector(const Vector& anotherVector) : origin(anotherVector.origin), tip(anotherVector.origin) {};

//         float norm() {
//             return sqrt((tip.getX()-origin.getX())*(tip.getX()-origin.getX())+(tip.getY()-origin.getY())*(tip.getY()-origin.getY())+(tip.getZ()-origin.getZ())*(tip.getZ()-origin.getZ()));
//         };

//         float dotproduct(const Vector& anotherVector) {
//             return (tip.getX()-origin.getX())*(anotherVector.tip.getX()-anotherVector.origin.getX())+(tip.getY()-origin.getY())*(anotherVector.tip.getY()-anotherVector.origin.getY())   +(tip.getZ()-origin.getZ())*(anotherVector.tip.getZ()-anotherVector.origin.getZ());
//         };
// };
class Object
{
    // Un objet est défini par une surface et une géométrie
    // Variables
protected:
    surface self_surface;
    // enum geometry self_geometry;

public:
    // En tete de fonctions et méthodes
    // enum geometry getGeometry() { return self_geometry; };
    surface getSurfaceProperties() { return self_surface; };

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
    }
    // explicit Object(geometry new_geometry)
    // {
    //     self_geometry = new_geometry;
    // }
    // Object(surface new_surface, enum geometry new_geometry) : self_surface(new_surface), self_geometry(new_geometry){};

    // Recopie

    Object(const Object &other)
    {
        self_surface = other.self_surface;
        // self_geometry = other.self_geometry;
    }

    // Destruction

    // ~Object() {
    //     std::cout << "Destruction de l'objet" << std::endl;
    // }
};

class Sphere : public Object
{
private:
    float rayon;
    Point3D centre;

public:
    Sphere() : Object(), rayon(1), centre{0, 0, 0} {};
    Sphere(const Sphere &other) : Object(), rayon(other.rayon), centre(other.centre){};
    explicit Sphere(float r) : Object(), rayon(r), centre{0, 0, 0} {};
    Sphere(float r, Point3D c) : Object(), rayon(r), centre(c){};
    // ~Sphere() { std::cout << "Destruction de la sphere";};

    float getRay() { return rayon; };
    Point3D getPosition() { return centre; };
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

class Plan : public Object
{
private:
    const Point3D normale; // C'est un point 3D par simplicité mais  c'est en réalité pour une normale
    const Point3D p;

public:
    Plan() : Object(), normale{1, 1, 1}, p{0, 0, 0} {};
    Plan(const Plan &otherPlan) : Object(), normale(otherPlan.getNormale()), p(otherPlan.getPoint()){};
    Plan(Point3D n, Point3D o) : Object(), normale(n), p(o){};
    Point3D getNormale() const
    {
        return normale;
    }
    Point3D getPoint() const
    {
        return p;
    }
    // ~Plan() { std::cout << "Destruction du plan";}
};

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

class Ray
{
private:
    const Point3D source_position;
    const Point3D direction; // C'est un vecteur
public:
    Ray() : source_position(0, 0, 0), direction(0, 0, 1){};
    Ray(const Point3D pos, const Point3D dir) : source_position(pos), direction(dir){};

    // Constructeur explicite (on pourrait en mettre d'autres)
    explicit Ray(const Point3D pos) : source_position(pos)
    {
        // On considère que l'oeil de l'observateur est situé au milieu de l'écran avec un peu de recul (initialement)

        /* Ici utiliser l'oeil et la position du rayon sur l'écran pour calculer la direction */
    }
    // Recopie
    Ray(const Ray &otherRay) : source_position(otherRay.getOrigin()), direction(otherRay.getDirection()){};

    // Destruction
    // ~Ray() {
    //     std::cout << "Destruction du rayon" << std::endl;
    // }

    Point3D getOrigin() const
    {
        return source_position;
    }
    Point3D getDirection() const
    {
        return direction;
    }
    Point3D positionAtT(float t) const
    {
        return source_position + direction * t;
    };

    Point3D hit(Object);
    Point3D hit(Sphere);

    // Intersections

    Point3D get_Closest_Intersection(Sphere *objects_vector) // Spheres atm
    {
        // Point3D oui(0, 0, 0);
        // return oui;
        /// Parcourir le vecteur, pour chaque objet on demande sa géométri pour savoir quelle équation vérifier, une fois qu'on a la géométrie, on peut récupérer la position de l'objet et ses caractéristiques pour résoudre l'équation et stocker dans l'array des intersections le(s) points d'intersection du rayon courant avec les formes.

        Point3D closest_intersection_point(0, 0, 0); // Le Résultat
        // int cpteur_inter = 0;
        // Sphere *object_ptr = objects_vector; //Sphere atm
        int cptr = 0;
        while (cptr < 2)
        {
            Point3D new_inter = hit(*objects_vector);

            if (new_inter != source_position) // Si on hit un truc interessant,
            {
                if (closest_intersection_point == source_position)
                { // Si le plus proche n'a pas encore été update (il est alors tjs égal à son état initial)

                    closest_intersection_point = new_inter;
                   
                }    // Alors c'est sur que c'est lui le plus proche
                else // Si on a déjà une valeur, on compare
                    closest_intersection_point = closest_intersection_point.min_dist(new_inter, source_position);
            }
            cptr++;
            objects_vector++;
        }
        return closest_intersection_point;
    }
    //Illuminations
    // Créer ensuite une fonction qui prend en paramètre le ( ou la liste des) point le plus proche calculé juste avant et calcule à partir de lui l'illumination du dit point (ie sa couleur), ces données devraient peut etre être envoyées dans une matrice des pixels de l'image à display et ca sera bon
};

#endif