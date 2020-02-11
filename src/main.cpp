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

Point3D computeLight(Object object, Point3D normale, Point3D reflected, Point3D viewer, Source source)
{
    // Can add Ambient Lighting and Specular reflexion according to the Phong model
    float ir = ((object.getSurfaceProperties().colorR) * (source.getIntensity() * source.getColor().getX()) * maxi(-normale.dotProduct(source.getDirection()), 0.0) + 255 * source.getColor().getX() * pow(maxi(-reflected.dotProduct(viewer), 0.0), object.getSurfaceProperties().shininess)) / 255.99;
    ir = checkColorBoundaries(ir);
    float ig = ((object.getSurfaceProperties().colorG) * (source.getIntensity() * source.getColor().getY()) * maxi(-normale.dotProduct(source.getDirection()), 0.0) + 255 * source.getColor().getY() * pow(maxi(-reflected.dotProduct(viewer), 0.0), object.getSurfaceProperties().shininess)) / 255.99;
    ig = checkColorBoundaries(ig);
    float ib = ((object.getSurfaceProperties().colorB) * (source.getIntensity() * source.getColor().getZ()) * maxi(-normale.dotProduct(source.getDirection()), 0.0) + 255 * source.getColor().getZ() * pow(maxi(-reflected.dotProduct(viewer), 0.0), object.getSurfaceProperties().shininess)) / 255.99;
    ib = checkColorBoundaries(ib);
    return Point3D((int)ir, (int)ig, (int)ib);
} // Toujours des sphères pour le moment mais peut etre qu'on peut simplement remplacer sphere et objet

int main()
{
    // screen 100(x)*100(y) at z = 50
    // centered so x in [-50;50], y in [-50,50]
    // camera at (0,0,0)
    // all rays start at (0,0,0), their direction is given by the pixel they compute on the screen ( so (x,y,50) )
    // routine that create all rays

    Point3D origin(0, 0, 0);
    Point3D normale(0, 0, -1);
    Point3D originPlan(0, 0, 500);

    // Source(s) de lumière
    Source main_source;

    // Plan de fond
    surface surface_plan = {PLAIN, 10, 30, 10, 1000, 0.03, 0.0};
    Point3D backgroundPoint(0, 0, 3000);
    Plan background(surface_plan, normale, backgroundPoint);

    //Objets de la scène
    surface surface_sphere = {PLAIN, 200, 0, 0, 20.0, 1.0, 0.0};
    surface surface_sphere2 = {PLAIN, 0, 0, 200, 20.0, 1.0, 0.0};
    Sphere sphere(surface_sphere, 300, originPlan);
    Sphere sphere2(surface_sphere2, 400, Point3D(-100, -100, 700));

    std::list<Object *> myObjs;
    myObjs.push_back(&sphere);
    myObjs.push_back(&sphere2);
    myObjs.push_back(&background);

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
            Point3D dir(x, y, 50);
            Ray ray(origin, dir);
            Object sphere_hit; //It's an object
            Point3D norm_at_hitpoint;
            Point3D pointIntersect = ray.get_Closest_Intersection(myObjs, &sphere_hit, &norm_at_hitpoint);
            Point3D my_pixel(0, 0, 0);
            norm_at_hitpoint.normalize();
            Point3D viewer = (pointIntersect - origin);
            viewer.normalize();
            Point3D reflected = main_source.getDirection() - norm_at_hitpoint * 2.0 * (main_source.getDirection().dotProduct(norm_at_hitpoint));
            reflected.normalize();

            my_pixel = computeLight(sphere_hit, norm_at_hitpoint, reflected, viewer, main_source);
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