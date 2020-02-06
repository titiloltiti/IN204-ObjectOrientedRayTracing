#ifndef RAY_HPP
#define RAY_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <algorithm>
#include "point3D.hpp"
#include "objects.hpp"
#include "source.hpp"

#ifndef NO_HIT
#define NO_HIT  \
    {           \
        0, 0, 0 \
    }
#endif

class Ray
{
private:
    const Point3D source_position;
    const Point3D direction; // C'est un vecteur
public:
    Ray() : source_position(0, 0, 0), direction(0, 0, 1){};
    Ray(const Point3D pos, const Point3D dir) : source_position(pos), direction(dir){};

    explicit Ray(const Point3D pos) : source_position(pos)
    {
        // On considère que l'oeil de l'observateur est situé au milieu de l'écran avec un peu de recul (initialement)
        /* Ici utiliser l'oeil et la position du rayon sur l'écran pour calculer la direction */
    }

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
    Point3D hit(Sphere s)
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
    };

    Point3D get_Closest_Intersection(Sphere *objects_vector,Sphere *sphere_hit) // Spheres atm voir pour faire un template
    {
        /// Parcourir le vecteur, pour chaque objet on demande sa géométrie pour savoir quelle équation vérifier, une fois qu'on a la géométrie, on peut récupérer la position de l'objet et ses caractéristiques pour résoudre l'équation et stocker dans l'array des intersections le(s) points d'intersection du rayon courant avec les formes.

        Point3D closest_intersection_point(0, 0, 0);
        int cptr = 0;
        while (cptr < 2) //2 Spheres atm
        {
            Point3D new_inter = hit(*objects_vector);

            if (new_inter != source_position) // Si on hit un truc interessant,
            {
                if (closest_intersection_point == source_position)
                { // Si le plus proche n'a pas encore été update (il est alors tjs égal à son état initial)
                    *sphere_hit=*objects_vector;
                    closest_intersection_point = new_inter;

                }    // Alors c'est sur que c'est lui le plus proche
                else {// Si on a déjà une valeur, on compare
                    Point3D temp = closest_intersection_point.min_dist(new_inter, source_position);
                    if (temp!= closest_intersection_point) {
                        *sphere_hit=*objects_vector;
                        closest_intersection_point=temp;
                    }
                }       
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