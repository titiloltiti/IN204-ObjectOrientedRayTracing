#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>

enum texture {PLAIN,TEXTURE2,TEXTURE3,TEXTURE4};
enum geometry {CUBE,TRIANGLE,RECTANGLE,SPHERE,PLAN};

struct surface {
    enum texture text; //Texture de la surface
    int colorR;
    int colorG;
    int colorB;
    float reflexion; //Coef de reflexion de la structure entre 0 et 1
    float transparency; //Coef de transp entre 0 et 1
};

struct point3D {
    float p_X;
    float p_Y;
    float p_Z;
};



class Object {
    // Un objet est défini par une surface et une géométrie 
    // Variables
    protected :
        struct surface self_surface;
        enum geometry self_geometry;

    public :
    // En tete de fonctions et méthodes
    enum geometry getGeometry() { return self_geometry;};
    struct surface getSurfaceProperties() {return self_surface;};

    // Constructeur par défaut
    Object() {
        self_surface.text = PLAIN;
        self_surface.reflexion=0;
        self_surface.transparency=0;
    };

    // Constructeur explicite
    explicit Object(struct surface new_surface) {
        self_surface = new_surface;
    }
    explicit Object(geometry new_geometry) {
        self_geometry=new_geometry;
    }
    Object(struct surface new_surface, enum geometry new_geometry) : self_surface(new_surface),self_geometry(new_geometry) {};

    // Recopie

    Object(const Object &other) {
        self_surface = other.self_surface;
        self_geometry = other.self_geometry;
    }

    // Destruction

    ~Object() {
        std::cout << "Destruction de l'objet" << std::endl;
    }
    
};

class Sphere : public Object
{
    private :
        float rayon;
        struct point3D centre;
    public :
        Sphere() : rayon(1),centre{0,0,0},Object(SPHERE) {};
        Sphere(const Sphere &other) : rayon(other.rayon), centre(other.centre), Object(other) {};
        explicit Sphere(float r) : rayon(r),centre{0,0,0},Object(SPHERE) {};
        Sphere(float r, struct point3D c) : rayon(r), centre(c), Object(SPHERE) {};
        ~Sphere() { std::cout << "Destruction de la sphere";};

        float getRay() {return rayon;};
        struct point3D getPosition() {return centre;};
};

class Cube : public Object
{
    private :
        float arete;
        struct point3D top_front_left_corner;
    public :
        Cube() : arete(1),top_front_left_corner{0,0,0},Object(CUBE) {};
        Cube(const Cube &other) : arete(other.arete), top_front_left_corner(other.top_front_left_corner), Object(other) {};
        explicit Cube(float a) : arete(a),top_front_left_corner{0,0,0},Object(CUBE) {};
        Cube(float a, struct point3D c) : arete(a), top_front_left_corner(c), Object(CUBE) {};
        ~Cube() { std::cout << "Destruction du cube";};

        float getArete() {return arete;};
        struct point3D getPosition() {return top_front_left_corner;};
};

class Rectangle : public Object
{
    private :
        const struct point3D dimensions;
        struct point3D top_front_left_corner;
    public :
        Rectangle() : dimensions{1,2,3},top_front_left_corner{0,0,0},Object(RECTANGLE) {};
        Rectangle(const Rectangle &other) : dimensions(other.dimensions), top_front_left_corner(other.top_front_left_corner), Object(other) {};
        explicit Rectangle(const struct point3D dim) : dimensions(dim),top_front_left_corner{0,0,0},Object(RECTANGLE) {};
        Rectangle(const struct point3D dim, struct point3D c) : dimensions(dim), top_front_left_corner(c), Object(RECTANGLE) {};
        ~Rectangle() { std::cout << "Destruction du rectangle";};

        const struct point3D getDim() {return dimensions;};
        struct point3D getPosition() {return top_front_left_corner;};
};

class Triangle : public Object //Equilatéral
{
    private :
        float arete;
        struct point3D top;
    public :
        Triangle() : arete(1),top{0,0,0},Object(TRIANGLE) {};
        Triangle(const Triangle &other) : arete(other.arete), top(other.top), Object(other) {};
        explicit Triangle(float a) : arete(a),top{0,0,0},Object(TRIANGLE) {};
        Triangle(float a, struct point3D c) : arete(a), top(c), Object(TRIANGLE) {};
        ~Triangle() { std::cout << "Destruction du triangle";};
    
    float getArete() {return arete;};
    struct point3D getPosition() {return top;};
};

// class Plan : public Object 
// {
//     private :
//         const struct point3D normale; // C'est un point 3D par simplicité mais  c'est en réalité pour une normale 
//         struct point3D p;
//     public :
//         Plan() : arete(1),top{0,0,0},Object(Plan) {};
//         Plan(const Sphere &other) : arete(other.arete), top(other.top), Object(Plan) {};
//         explicit Plan(float a) : arete(a),top{0,0,0},Object(Plan) {};
//         Plan(float a, struct point3D c) : arete(a), top(c), Object(Plan) {};
//         ~Plan() { std::cout << "Destruction de la sphere"};
// }


class Source { //Pour l'instant la source sera omnidirectionnelle
    private :
        struct point3D position;
        int colorR;
        int colorG;
        int colorB;
        float intensity; //entre 0 et 1
    public:
        Source() : position{10,10,-10},colorR(255),colorG(255),colorB(255),intensity(1) {};

    // Constructeur explicite (on pourrait en mettre d'autres)
    explicit Source(struct point3D pos) : position(pos),colorR(255),colorG(255),colorB(255),intensity(1) {};


    // Recopie

    Source(const Source &other) {
        position = other.position;
        colorR = other.colorR;
        colorG = other.colorG;
        colorB = other.colorB;
        intensity = other.intensity;
    }

    // Destruction

    ~Source() {
        std::cout << "Destruction de la source" << std::endl;
    }

    int* getColor() {int color[3]={colorR,colorG,colorB}; return color;};
    struct point3D getPosition() {return position;};
    float getIntensity() {return intensity;};
};

class Ray {
    private : 
        const struct point3D source_position; //C'est un point 2D sur l'écran (z=0)
        const struct point3D direction; // C'est un vecteur
    public : 
        Ray() : source_position{0,0,0},direction{1,1,1} {};

    // Constructeur explicite (on pourrait en mettre d'autres)
    explicit Ray(struct point3D pos) {
        source_position = pos;
        // On considère que l'oeil de l'observateur est situé au milieu de l'écran avec un peu de recul (initialement)

        /* Ici utiliser l'oeil et la position du rayon sur l'écran pour calculer la direction */
        
    }


    // Recopie

    Ray(const Ray &other) {
        source_position = other.source_position;
        direction = other.direction;
    }

    // Destruction

    ~Ray() {
        std::cout << "Destruction du rayon" << std::endl;
    }

    struct point3D hitPoint(); //Renvoie le point de contact entre le rayon et le prmier obstacle rencontré, renvoie ??? si aucun objet n'a été rencontré

};