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
#include <list>

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
    Point3D direction; // C'est un vecteur
public:
    Ray() : source_position(0, 0, 0), direction(0, 0, 1){};
    Ray(const Point3D &pos, Point3D &dir) : source_position(pos), direction(dir) { direction.normalize(); };

    explicit Ray(const Point3D &pos) : source_position(pos)
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

    // Point3D hit(Object *o)
    // {
    //     geometry geom = (*o).getGeometry();
    //     std::cout << o << std::endl;
    //     switch (geom)
    //     {
    //     case PLAN:
    //         return hit(dynamic_cast<Plan *>(o));
    //         break;
    //     case SPHERE:
    //         return hit(dynamic_cast<Sphere *>(o));
    //         break;
    //     default:
    //         return source_position;
    //         break;
    //      }
    //  };
    // Point3D hit(Plan p)
    // {
    //     std::cout << "Testing plan " << std::endl;
    //     Point3D res = source_position;
    //     float a = (p).getNormale().getX();
    //     float b = (p).getNormale().getY();
    //     float c = (p).getNormale().getZ();
    //     float d = a * (p).getPoint().getX() + b * (p).getPoint().getY() + c * (p).getPoint().getZ(); //Plane is ax+by+cz+d=0

    //     float t = (float)-(a * res.getX() + b * res.getY() + c * res.getZ() + d) / (p).getNormale().dotProduct(direction);
    //     res = res + direction * t;

    //     return res;
    // };

    Point3D get_Closest_Intersection(std::list<Object *> objects_vector, Object *sphere_hit, Point3D *norm_at_hitpoint
                                     /* , int item size, creer une variable globale qui est incrémentée à la construcction 
                                     (comme en java) si possible */
                                     ) const // Spheres atm voir pour faire un template
    {
        /// Parcourir le vecteur, pour chaque objet on demande sa géométrie pour savoir quelle équation vérifier, une fois qu'on a la géométrie, on peut récupérer la position de l'objet et ses caractéristiques pour résoudre l'équation et stocker dans l'array des intersections le(s) points d'intersection du rayon courant avec les formes.
        Point3D closest_intersection_point = source_position;
        std::list<Object *>::iterator it = objects_vector.begin();
        while (it != objects_vector.end())
        {
            Point3D new_inter = (*it)->hit(source_position, direction);
            if (new_inter != source_position) // Si on hit un truc interessant,
            {
                if ((new_inter.norm() > 0.5) && (closest_intersection_point == source_position))
                { // Si le plus proche n'a pas encore été update (il est alors tjs égal à son état initial)
                    *sphere_hit = *(*it);
                    *norm_at_hitpoint = (*it)->getNormale(new_inter);
                    closest_intersection_point = new_inter;

                } // Alors c'est sur que c'est lui le plus proche
                else if (new_inter.norm() > 0.5)
                { // Si on a déjà une valeur, on compare
                    Point3D temp = closest_intersection_point.min_dist(new_inter, source_position);
                    if (temp != closest_intersection_point)
                    {
                        *sphere_hit = *(*it);
                        *norm_at_hitpoint = (*it)->getNormale(temp);
                        closest_intersection_point = temp;
                    }
                }
            }
            std::advance(it, 1);
        }
        return closest_intersection_point;
    }
    //Illuminations
    // Créer ensuite une fonction qui prend en paramètre le ( ou la liste des) point le plus proche calculé juste avant et calcule à partir de lui l'illumination du dit point (ie sa couleur), ces données devraient peut etre être envoyées dans une matrice des pixels de l'image à display et ca sera bon
};

#endif