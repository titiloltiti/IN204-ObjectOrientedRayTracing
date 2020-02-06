#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <SFML/Graphics.hpp>
#include "ray.hpp"
#include "point3D.hpp"
#include "objects.hpp"
#include "source.hpp"
#include <cstdlib>
#include <math.h>
#include <fstream>

bool rayPlaneIntersection(Ray r, Plan p)
{
    float x = abs(p.getNormale().Point3D::dotProduct(r.getDirection()));
    if (x > 1e-6)
    {
        Point3D y = p.getPoint() - r.getOrigin();
        float t = y.dotProduct(p.getNormale()) / x;
        return (t >= 0);
    }
    else
        return false;
}

bool rayIntersectSphere(Ray ray, Sphere s)
{
    Point3D l = ray.getOrigin() - s.getPosition();
    Point3D d = ray.getDirection();
    float r = s.getRay();

    float discr = 4 * ((l * d) * (l * d) - (d * d) * (l * l - (r * r)));

    return (discr > 0);
}

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
Point3D computeLight(Object object, Point3D normale, Source source)
{
    // Can add Ambient Lighting and Specular reflexion according to the Phong model
    float ir = (object.getSurfaceProperties().colorR) * (source.getIntensity() * source.getColor().getX()) * maxi(normale.dotProduct(source.getDirection()), 0.0) / 255.99;
    ir = checkColorBoundaries(ir);
    float ig = (object.getSurfaceProperties().colorG) * (source.getIntensity() * source.getColor().getY()) * maxi(normale.dotProduct(source.getDirection()), 0.0) / 255.99;
    ig = checkColorBoundaries(ig);
    float ib = (object.getSurfaceProperties().colorB) * (source.getIntensity() * source.getColor().getZ()) * maxi(normale.dotProduct(source.getDirection()), 0.0) / 255.99;
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
    Point3D normale(0, 0, 1);
    Point3D originPlan(0, 0, 500); // il s'appelle Origin plan mais c'est le background?

    // Source(s) de lumière
    Source main_source;

    // Plan de fond
    surface surface_plan = {PLAIN, 10, 10, 10, 0.03, 0.0};
    Plan background(surface_plan, normale, originPlan);

    //Objets de la scène
    surface surface_sphere = {PLAIN, 200, 0, 0, 1.0, 0.0};
    surface surface_sphere2 = {PLAIN, 0, 0, 200, 1.0, 0.0};
    Sphere sphere(surface_sphere, 300, originPlan);
    Sphere sphere2(surface_sphere2, 400, Point3D(700, 700, 1000));
    Sphere myObjs[2] = {sphere, sphere2};

    // TEST PART
    std::cout << "Scene propeties : \n"
              << "Sphere 1 : "
              << "Red : " << sphere.getSurfaceProperties().colorR << " Green : " << sphere.getSurfaceProperties().colorG << " Blue : " << sphere.getSurfaceProperties().colorB << "\n"
              << "Sphere 2 : "
              << "Red : " << sphere2.getSurfaceProperties().colorR << " Green : " << sphere2.getSurfaceProperties().colorG << " Blue : " << sphere2.getSurfaceProperties().colorB << std::endl;

    // Taille de la scène
    int cameraHeight = 721;
    int cameraWidth = 1281;

    std::ofstream myImage;
    myImage.open("image.ppm");

    myImage << "P3\n"
            << cameraWidth << " " << cameraHeight << "\n255";

    for (int x = cameraHeight / 2; x >= -cameraHeight / 2; x--)
    {
        myImage << "\n";
        for (int y = -cameraWidth / 2; y <= cameraWidth / 2; y++)
        {
            Point3D dir(x, y, 50);
            Ray ray(origin, dir);
            Point3D pointIntersect = ray.get_Closest_Intersection(myObjs);
            Point3D my_pixel(0, 0, 0);
            if (pointIntersect != origin)
            {
                // Ce test sert juste à distinguer les 2 sphères pour bien voir si on a la premiere devant et l'autre derriere mais il faut virer ca maintenant 
                if (pointIntersect.getZ() < 400)
                {
                    Point3D norm = (pointIntersect - sphere.getPosition());
                    norm.normalize();
                    my_pixel = computeLight(sphere, norm, main_source);
                    myImage
                        << my_pixel.getX() << " " << my_pixel.getY() << " " << my_pixel.getZ() << " ";
                }
                else
                {
                    Point3D norm = (pointIntersect - sphere2.getPosition());
                    norm.normalize();
                    my_pixel = computeLight(sphere2, norm, main_source);
                    myImage
                        << my_pixel.getX() << " " << my_pixel.getY() << " " << my_pixel.getZ() << " ";
                }
            }
            else if (rayPlaneIntersection(ray, background))
            {

                myImage << background.getSurfaceProperties().colorR << " " << background.getSurfaceProperties().colorG << " " << background.getSurfaceProperties().colorB << " ";
            }
        }
    }
    myImage.close();
    return 1;
}