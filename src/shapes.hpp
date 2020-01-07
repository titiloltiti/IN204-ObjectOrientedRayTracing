#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>

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

class point3D
{
private:
    float p_X;
    float p_Y;
    float p_Z;

public:
    point3D() : p_X(0), p_Y(0), p_Z(0){};
    point3D(int x, int y, int z) : p_X(x), p_Y(y), p_Z(z){};
    point3D(const point3D &point) : p_X(point.getX()), p_Y(point.getX()), p_Z(point.getZ()){};

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

    point3D operator=(const point3D &anotherPoint) const
    {
        point3D result(anotherPoint); //Constructeur de recopie par défaut?
        return result;
    };
    point3D operator*(float t) const;
    friend point3D operator*(float t, const point3D point);
    float operator*(const point3D &anotherPoint) const
    {
        return (p_X * anotherPoint.getX() + p_Y * anotherPoint.getY() + p_Z * anotherPoint.getZ());
    }
    point3D operator+(const point3D &point) const
    {
        return point3D(p_X + point.getX(), p_Y + point.getY(), p_Z + point.getZ());
    }
    point3D operator-(const point3D &point) const
    {
        return point3D(p_X - point.getX(), p_Y - point.getY(), p_Z - point.getZ());
    }
    float dotProduct(const point3D anotherPoint) const
    {
        return (p_X * anotherPoint.getX() + p_Y * anotherPoint.getY() + p_Z * anotherPoint.getZ());
    }
};
point3D point3D::operator*(float t) const
{
    return point3D(p_X * t, p_Y * t, p_Z * t);
};
point3D operator*(float t, const point3D point)
{
    return point3D(point.getX() * t, point.getY() * t, point.getZ() * t);
}

// class Vector {
//     private :
//         point3D origin;
//         point3D tip;
//     public :
//         Vector() : origin(point3D()), tip(point3D()) {};
//         Vector(point3D m_origin,point3D m_tip) : origin(m_origin), tip(m_tip) {};
//         explicit Vector(point3D m_tip) : origin(point3D()), tip(m_tip) {};
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
    enum geometry self_geometry;

public:
    // En tete de fonctions et méthodes
    enum geometry getGeometry() { return self_geometry; };
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
    explicit Object(geometry new_geometry)
    {
        self_geometry = new_geometry;
    }
    Object(surface new_surface, enum geometry new_geometry) : self_surface(new_surface), self_geometry(new_geometry){};

    // Recopie

    Object(const Object &other)
    {
        self_surface = other.self_surface;
        self_geometry = other.self_geometry;
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
    point3D centre;

public:
    Sphere() : rayon(1), centre{0, 0, 0}, Object(SPHERE){};
    Sphere(const Sphere &other) : rayon(other.rayon), centre(other.centre), Object(other){};
    explicit Sphere(float r) : rayon(r), centre{0, 0, 0}, Object(SPHERE){};
    Sphere(float r, point3D c) : rayon(r), centre(c){};
    // ~Sphere() { std::cout << "Destruction de la sphere";};

    float getRay() { return rayon; };
    point3D getPosition() { return centre; };
};

class Cube : public Object
{
private:
    float arete;
    point3D top_front_left_corner;

public:
    Cube() : arete(1), top_front_left_corner{0, 0, 0}, Object(CUBE){};
    Cube(const Cube &other) : arete(other.arete), top_front_left_corner(other.top_front_left_corner), Object(other){};
    explicit Cube(float a) : arete(a), top_front_left_corner{0, 0, 0}, Object(CUBE){};
    Cube(float a, point3D c) : arete(a), top_front_left_corner(c), Object(CUBE){};
    // ~Cube() { std::cout << "Destruction du cube";};

    float getArete() { return arete; };
    point3D getPosition() { return top_front_left_corner; };
};

class Rectangle : public Object
{
private:
    const point3D dimensions;
    point3D top_front_left_corner;

public:
    Rectangle() : dimensions{1, 2, 3}, top_front_left_corner{0, 0, 0}, Object(RECTANGLE){};
    Rectangle(const Rectangle &other) : dimensions(other.dimensions), top_front_left_corner(other.top_front_left_corner), Object(other){};
    explicit Rectangle(const point3D dim) : dimensions(dim), top_front_left_corner{0, 0, 0}, Object(RECTANGLE){};
    Rectangle(const point3D dim, point3D c) : dimensions(dim), top_front_left_corner(c), Object(RECTANGLE){};
    // ~Rectangle() { std::cout << "Destruction du rectangle";};

    const point3D getDim() { return dimensions; };
    point3D getPosition() { return top_front_left_corner; };
};

class Triangle : public Object //Equilatéral
{
private:
    float arete;
    point3D top;

public:
    Triangle() : arete(1), top{0, 0, 0}, Object(TRIANGLE){};
    Triangle(const Triangle &other) : arete(other.arete), top(other.top), Object(other){};
    explicit Triangle(float a) : arete(a), top{0, 0, 0}, Object(TRIANGLE){};
    Triangle(float a, point3D c) : arete(a), top(c), Object(TRIANGLE){};
    // ~Triangle() { std::cout << "Destruction du triangle";};

    float getArete() { return arete; };
    point3D getPosition() { return top; };
};

class Plan : public Object
{
private:
    const point3D normale; // C'est un point 3D par simplicité mais  c'est en réalité pour une normale
    const point3D p;

public:
    Plan() : normale{1, 1, 1}, p{0, 0, 0} {};
    Plan(const Plan &otherPlan) : normale(otherPlan.getNormale()), p(otherPlan.getPoint()){};
    Plan(point3D n, point3D o) : normale(n), p(o){};
    point3D getNormale() const
    {
        return normale;
    }
    point3D getPoint() const
    {
        return p;
    }
    // ~Plan() { std::cout << "Destruction du plan";}
};

class Source
{ //Pour l'instant la source sera omnidirectionnelle
private:
    point3D position;
    int colorR;
    int colorG;
    int colorB;
    float intensity; //entre 0 et 1
public:
    Source() : position{10, 10, -10}, colorR(255), colorG(255), colorB(255), intensity(1){};

    // Constructeur explicite (on pourrait en mettre d'autres)
    explicit Source(point3D pos) : position(pos), colorR(255), colorG(255), colorB(255), intensity(1){};

    // Recopie

    Source(const Source &other)
    {
        position = other.position;
        colorR = other.colorR;
        colorG = other.colorG;
        colorB = other.colorB;
        intensity = other.intensity;
    }

    // Destruction

    ~Source()
    {
        std::cout << "Destruction de la source" << std::endl;
    }

    int *getColor()
    {
        int color[3] = {colorR, colorG, colorB};
        return color;
    };
    point3D getPosition() { return position; };
    float getIntensity() { return intensity; };
};

class Ray
{
private:
    const point3D source_position;
    const point3D direction; // C'est un vecteur
public:
    Ray() : source_position(), direction(){};
    Ray(const point3D pos, const point3D dir) : source_position(pos), direction(dir){};

    // Constructeur explicite (on pourrait en mettre d'autres)
    explicit Ray(const point3D pos) : source_position(pos)
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

    point3D getOrigin() const
    {
        return source_position;
    }
    point3D getDirection() const
    {
        return direction;
    }
    point3D positionAtT(float t) const
    {
        return source_position + direction * t;
    };

    // Intersections
    // point3D* getIntersections(const Object * objects_vectors) {
    //      /// Parcourir le vecteur, pour chaque objet on demande sa géométri pour savoir quelle équation vérifier, une fois qu'on a la géométrie, on peut récupérer la position de l'objet et ses caractéristiques pour résoudre l'équation et stocker dans l'array des intersections le(s) points d'intersection du rayon courant avec les formes.
    //}
    // point3D getClosest(point3D* intersections_array) Cette fonction va simplement calculer, a partir de la liste des points d'intersection obtenue avec la question précédente le poin d'intersection le plus proche de l'écran

    //Illuminations
    // Créer ensuite une fonction qui prend en paramètre le ( ou la liste des) point le plus proche calculé juste avant et calcule à partir de lui l'illumination du dit point (ie sa couleur), ces données devraient peut etre être envoyées dans une matrice des pixels de l'image à display et ca sera bon
};