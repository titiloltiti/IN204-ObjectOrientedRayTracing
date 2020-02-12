#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <SFML/Graphics.hpp>
#include "../include/ray.hpp"
#include "../include/point3D.hpp"
#include "../include/objects.hpp"
#include "../include/source.hpp"
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <list>

int Object::nbObj = 0;

// Plan de fond
Point3D normale(0, 0, -1);
surface surface_plan = {PLAIN, 0, 0, 0, 1000, 0.03, 0.0};
Point3D backgroundPoint(0, 0, 10000);
Plan background(surface_plan, normale, backgroundPoint);

Point3D global_ambient_intensity(10, 10, 10);

Point3D origin(0, 0, 0); //oeil

// Source(s) de lumière
Source main_source;

// bool rayPlaneIntersection(Ray r, Plan p)
// {
//     return (r.getDirection().dotProduct(p.getNormale()) != 0);
// }

// bool rayIntersectSphere(Ray ray, Sphere s)
// {
//     Point3D l = ray.getOrigin() - s.getPosition();
//     Point3D d = ray.getDirection();
//     float r = s.getRay();

//     float discr = 4 * ((l * d) * (l * d) - (d * d) * (l * l - (r * r)));

//     return (discr > 0);
// }

float maxi(float a, float b)
{
    if (a < b)
        return b;
    return a;
}

float checkColorBoundaries(float color)
{
    if (color > 255)
        return 255;
    else if (color < 0)
        return 0;
    return color;
}

Point3D computeLight(Object object, Point3D norm, Point3D reflected, Point3D viewer, Source source)
{
    // Can add Ambient Lighting and Specular reflexion according to the Phong model
    float ir = ((object.getSurfaceProperties().colorR) * (source.getIntensity() * source.getColor().getX()) * maxi(-norm.dotProduct(source.getDirection()), 0.0) + 255 * source.getColor().getX() * pow(maxi(-reflected.dotProduct(viewer), 0.0), object.getSurfaceProperties().shininess)) / 255.99;
    ir = checkColorBoundaries(ir);
    float ig = ((object.getSurfaceProperties().colorG) * (source.getIntensity() * source.getColor().getY()) * maxi(-norm.dotProduct(source.getDirection()), 0.0) + 255 * source.getColor().getY() * pow(maxi(-reflected.dotProduct(viewer), 0.0), object.getSurfaceProperties().shininess)) / 255.99;
    ig = checkColorBoundaries(ig);
    float ib = ((object.getSurfaceProperties().colorB) * (source.getIntensity() * source.getColor().getZ()) * maxi(-norm.dotProduct(source.getDirection()), 0.0) + 255 * source.getColor().getZ() * pow(maxi(-reflected.dotProduct(viewer), 0.0), object.getSurfaceProperties().shininess)) / 255.99;
    ib = checkColorBoundaries(ib);
    return Point3D((int)ir, (int)ig, (int)ib);
} // Toujours des sphères pour le moment mais peut etre qu'on peut simplement remplacer sphere et objet
Point3D recursiveCompute(Ray ray, std::list<Object *> objects_vector, int counter)
{
    switch (counter)
    {
<<<<<<< HEAD
    case 3: //Ray Depth of 3 
=======
    case 3: //Ray Depth of 3
    default:
        Object sphere_hit; // It's actually an object
        Point3D norm_at_hitpoint;
        Point3D pointIntersect = ray.get_Closest_Intersection(objects_vector, &sphere_hit, &norm_at_hitpoint);

        if (pointIntersect == ray.getOrigin()) //If we don't hit anything, we hit the background
            return Point3D(background.getSurfaceProperties().colorR, background.getSurfaceProperties().colorG, background.getSurfaceProperties().colorB);

        norm_at_hitpoint.normalize();
        Point3D viewer = (pointIntersect - origin);
        viewer.normalize();
        Point3D reflected_light = main_source.getDirection() - norm_at_hitpoint * 2.0 * (main_source.getDirection().dotProduct(norm_at_hitpoint)); //Reflected from light source, not from viewer
        reflected_light.normalize();
        Point3D c = computeLight(sphere_hit, norm_at_hitpoint, reflected_light, viewer, main_source);

        //Shadow_ray calculation
        Point3D shadow_ray_dir;
        shadow_ray_dir = main_source.getDirection() * (-1); //*(-1)? je ne pense pas
        Ray shadow_ray(pointIntersect + shadow_ray_dir * 0.05, shadow_ray_dir);
        Object sphere_hit2;
        Point3D norm_at_hitpoint2;
        Point3D shadow_ray_intersection = shadow_ray.get_Closest_Intersection(objects_vector, &sphere_hit2, &norm_at_hitpoint2);
<<<<<<< HEAD
        if (shadow_ray_intersection != shadow_ray.getOrigin())
        {
            return Point3D(sphere_hit.getSurfaceProperties().colorR/5,sphere_hit.getSurfaceProperties().colorG/5,sphere_hit.getSurfaceProperties().colorB/5);
        }

        //Reflected_ray calculation
        if (sphere_hit.getSurfaceProperties().reflexion == 1.0)
        {
            Point3D reflected_ray_dir = ray.getDirection() - norm_at_hitpoint * 2.0 * (ray.getDirection().dotProduct(norm_at_hitpoint));
            Ray reflected_ray = Ray(shadow_ray_intersection + reflected_ray_dir * 0.05, reflected_ray_dir);
            Point3D res = c * 0.2 + recursiveCompute(reflected_ray, objects_vector, counter + 1) * 0.8;
            return Point3D((int)checkColorBoundaries(res.getX()), (int)checkColorBoundaries(res.getY()), (int)checkColorBoundaries(res.getZ()));
        }

=======
        if ((shadow_ray_intersection != shadow_ray.getOrigin()) && (sphere_hit != sphere_hit2))
            return Point3D(sphere_hit.getSurfaceProperties().colorR / 5, sphere_hit.getSurfaceProperties().colorG / 5, sphere_hit.getSurfaceProperties().colorB / 5);

        //Reflected_ray calculation
        if (sphere_hit.getSurfaceProperties().reflexion > 0.0)
        {
            Point3D reflected_ray_dir = ray.getDirection() - norm_at_hitpoint * 2.0 * (ray.getDirection().dotProduct(norm_at_hitpoint));
            Ray reflected_ray = Ray(pointIntersect + reflected_ray_dir * 0.05, reflected_ray_dir);
            Point3D res = c * (1 - sphere_hit.getSurfaceProperties().reflexion) + recursiveCompute(reflected_ray, objects_vector, counter + 1) * sphere_hit.getSurfaceProperties().reflexion;
            return Point3D((int)checkColorBoundaries(res.getX()), (int)checkColorBoundaries(res.getY()), (int)checkColorBoundaries(res.getZ()));
        }

>>>>>>> scene
        return Point3D((int)checkColorBoundaries(c.getX()), (int)checkColorBoundaries(c.getY()), (int)checkColorBoundaries(c.getZ()));
        break;
    }
}
// Point3D recursiveCompute(Ray ray, std::list<Object *> objects_vector)
// {

//     Object sphere_hit; //It's an object
//     Point3D norm_at_hitpoint;
//     Point3D pointIntersect = ray.get_Closest_Intersection(objects_vector, &sphere_hit, &norm_at_hitpoint);

//     if (pointIntersect == ray.getOrigin())
//         return Point3D(background.getSurfaceProperties().colorR, background.getSurfaceProperties().colorG, background.getSurfaceProperties().colorB);

//     Point3D shadow_ray_dir;
//     shadow_ray_dir = main_source.getDirection() * (-1); //*(-1)? je ne pense pas
//     Ray shadow_ray(pointIntersect + shadow_ray_dir * 0.05, shadow_ray_dir);
//     Object sphere_hit2;
//     Point3D norm_at_hitpoint2;
//     Point3D shadow_ray_intersection = shadow_ray.get_Closest_Intersection(objects_vector, &sphere_hit2, &norm_at_hitpoint2);
//     if ((shadow_ray_intersection != shadow_ray.getOrigin()) && (sphere_hit != sphere_hit2))
//         return Point3D(sphere_hit.getSurfaceProperties().colorR / 5, sphere_hit.getSurfaceProperties().colorG / 5, sphere_hit.getSurfaceProperties().colorB / 5);
//     // return Point3D((int)(sphere_hit.getSurfaceProperties().colorR+global_ambient_intensity.getX())/2,(int)(sphere_hit.getSurfaceProperties().colorG+global_ambient_intensity.getY())/2,(int)(sphere_hit.getSurfaceProperties().colorB+global_ambient_intensity.getZ())/2);
//     norm_at_hitpoint.normalize();
//     Point3D viewer = (pointIntersect - origin);
//     viewer.normalize();
//     Point3D reflected_light = main_source.getDirection() - norm_at_hitpoint * 2.0 * (main_source.getDirection().dotProduct(norm_at_hitpoint)); //Reflected from light source, not from viewer
//     reflected_light.normalize();
//     Point3D c = computeLight(sphere_hit, norm_at_hitpoint, reflected_light, viewer, main_source);
//     return Point3D((int)checkColorBoundaries(c.getX()), (int)checkColorBoundaries(c.getY()), (int)checkColorBoundaries(c.getZ()));
// }
// Point3D recursiveCompute(Ray ray, std::list<Object *> objects_vector, int counter)
// {
//     switch (counter)
//     {
//     case 3: // Cas d'arrêt, 3 réflexions max
//         return global_ambient_intensity;
//         break;
//     default:
//         Object sphere_hit; //It's an object
//         Point3D norm_at_hitpoint;
//         Object check;
//         Point3D pointIntersect = ray.get_Closest_Intersection(objects_vector, &sphere_hit, &norm_at_hitpoint);

//         if (pointIntersect == ray.getOrigin())
//             return Point3D(background.getSurfaceProperties().colorR, background.getSurfaceProperties().colorG, background.getSurfaceProperties().colorB);

//         norm_at_hitpoint.normalize();
//         Point3D viewer = (pointIntersect - origin);
//         viewer.normalize();
//         Point3D reflected_light = main_source.getDirection() - norm_at_hitpoint * 2.0 * (main_source.getDirection().dotProduct(norm_at_hitpoint)); //Reflected from light source, not from viewer
//         reflected_light.normalize();
//         Point3D c = computeLight(sphere_hit, norm_at_hitpoint, reflected_light, viewer, main_source);

//         Point3D shadow_ray_dir;
//         shadow_ray_dir =main_source.getDirection()*(-1) ; //*(-1)? je ne pense pas
//         Ray shadow_ray(pointIntersect,shadow_ray_dir);
//         c=c*0.8+recursiveCompute(shadow_ray,objects_vector,counter+1)*(0.20);
//         return Point3D((int) checkColorBoundaries(c.getX()),(int)checkColorBoundaries(c.getY()),(int)checkColorBoundaries(c.getZ()));
//         break;
//     }
// }

int main()
{
    // screen 100(x)*100(y) at z = 50
    // centered so x in [-50;50], y in [-50,50]
    // camera at (0,0,0)
    // all rays start at (0,0,0), their direction is given by the pixel they compute on the screen ( so (x,y,50) )
    // routine that create all rays

    // Point3D origin(0, 0, 0);
    // Point3D normale(0, 0, -1);
    // Point3D originPlan(0, 0, 1000);

    // // Source(s) de lumière
    // Source main_source;

    // // Plan de fond
    // surface surface_plan = {PLAIN, 20, 20, 20, 1000, 0.03, 0.0};
    // Point3D backgroundPoint(0, 0, 10000);
    // Plan background(surface_plan, normale, backgroundPoint);

    // //Objets de la scène
    // surface surface_sphere = {PLAIN, 200, 0, 0, 20.0, 1.0, 0.0};
    // Sphere sphere(surface_sphere, 50, originPlan + Point3D(-100, 0, 0));
    // surface surface_sphere2 = {PLAIN, 0, 0, 200, 20.0, 1.0, 0.0};
    // Sphere sphere2(surface_sphere2, 200, Point3D(150, 200, 1000) + Point3D(-100, 0, 0));
    // surface surface_plan2 = {PLAIN, 200, 150, 150, 1000, 0.03, 0.0};
    // Plan plan2(surface_plan2, Point3D(1, 0, 0), Point3D(-100, 0, 0));

    // std::list<Object *> myObjs;
    // myObjs.push_back(&sphere);
    // myObjs.push_back(&sphere2);

    Point3D originPlan(0, 0, 500);

    //Objets de la scène
<<<<<<< HEAD
    surface surface_sphere = {PLAIN, 200, 0, 0, 1000.0, 0.0, 0.0};
    surface surface_sphere2 = {PLAIN, 125, 125, 125, 1000.0, 0.0, 0.0}; //typical reflective ball
    Sphere sphere(surface_sphere, 30, originPlan + Point3D(150, 150, -30));
    Sphere sphere2(surface_sphere2, 100, originPlan + Point3D(100, 50, 100));
=======
    surface surface_sphere = {PLAIN, 255, 0, 0, 1000.0, 0.33, 0.0};
    surface surface_sphere2 = {PLAIN, 0, 0, 255, 1000.0, 0.33, 0.0};
    surface surface_sphere3 = {PLAIN, 0, 255, 0, 1000.0, 0.33, 0.0};

    Sphere sphere(surface_sphere, 100, originPlan);
    Sphere sphere2(surface_sphere2, 450, originPlan + Point3D(150, -150, 800));
    Sphere sphere3(surface_sphere3, 250, originPlan + Point3D(200, 500, 200));
>>>>>>> scene

    surface surface_plan_ground = {PLAIN, 255, 255, 255, 1000, 1.0, 0.0};
    Point3D groundPoint(-100, 0, 0);
    Point3D normale_ground(1, 0, 0);
    Plan ground(surface_plan_ground, normale_ground, groundPoint);

    std::list<Object *> myObjs;
    myObjs.push_back(&sphere);
    myObjs.push_back(&sphere2);
    myObjs.push_back(&sphere3);
    myObjs.push_back(&ground);

    // TEST PART
    std::cout << "Scene propeties : \n"
              << "Sphere 1 : "
              << "Red : " << sphere.getSurfaceProperties().colorR << " Green : " << sphere.getSurfaceProperties().colorG << " Blue : " << sphere.getSurfaceProperties().colorB << "\n"
              << "Sphere 2 : "
              << "Red : " << sphere2.getSurfaceProperties().colorR << " Green : " << sphere2.getSurfaceProperties().colorG << " Blue : " << sphere2.getSurfaceProperties().colorB << "\n"
              << "Background : "
              << "Red : " << background.getSurfaceProperties().colorR << " Green : " << background.getSurfaceProperties().colorG << " Blue : " << background.getSurfaceProperties().colorB << std::endl;

    // Taille de la scène
    int cameraHeight = 721;
    int cameraWidth = 1281;

    std::ofstream myImage;
    myImage.open("result/image.ppm");

    myImage << "P3\n"
            << cameraWidth << " " << cameraHeight << "\n255";

    for (int x = cameraHeight / 2; x >= -cameraHeight / 2; x--)
    {
        myImage << "\n";
        for (int y = -cameraWidth / 2; y <= cameraWidth / 2; y++)
        {
            Point3D dir(x, y, (int)originPlan.getZ());
            Ray ray(origin, dir);
            Point3D my_pixel(0, 0, 0);
            // Object sphere_hit; //It's an object
            // Point3D norm_at_hitpoint;
            // Point3D pointIntersect = ray.get_Closest_Intersection(myObjs, &sphere_hit, &norm_at_hitpoint);
            // norm_at_hitpoint.normalize();
            // Point3D viewer = (pointIntersect - origin);
            // viewer.normalize();
            // Point3D reflected = main_source.getDirection() - norm_at_hitpoint * 2.0 * (main_source.getDirection().dotProduct(norm_at_hitpoint));
            // reflected.normalize();

            // my_pixel = computeLight(sphere_hit, norm_at_hitpoint, reflected, viewer, main_source);
            my_pixel = recursiveCompute(ray, myObjs, 0);
            myImage
                << my_pixel.getX() << " " << my_pixel.getY() << " " << my_pixel.getZ() << " ";

            // else if (rayPlaneIntersection(ray, background))
            // {
            //     Point3D viewer = Point3D(0, 0, 1); //Pas de brillance sur le background pour le moment
            //     viewer.normalize();
            //     Point3D reflected = Point3D(0, 1, 0); // Nop
            //     reflected.normalize();
            //     // my_pixel = computeLight(background, normale, reflected, viewer, main_source);
            //     myImage << background.getSurfaceProperties().colorR << " " << background.getSurfaceProperties().colorG << " " << background.getSurfaceProperties().colorB << " "; //WARNING: On n'affiche pas les bonnes couleurs ici je pense
            // }
        }
    }
    myImage.close();
    return 0;
}
