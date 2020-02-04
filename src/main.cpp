#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <SFML/Graphics.hpp>
#include "shapes.cpp"
#include <cstdlib>
#include <math.h>
#include <fstream>

// int main()
// {
//     sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//     sf::CircleShape shape(100.f);
//     shape.setFillColor(sf::Color::Green);

//     // Calculations

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         window.clear();
//         window.draw(shape);
//         window.display();
//     }

//     return 0;
// }

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

int main()
{
    // screen 100(x)*100(y) at z = -50
    // centered so x in [-50;50], y in [-50,50]
    // camera at (0,0,0)
    // all rays start at (0,0,0), their direction is given by the pixel they compute on the screen ( so (x,y,-50) )
    // routine that create all rays

    Point3D origin(0, 0, 0);

    Point3D normale(0, 0, 1);
    Point3D originPlan(0, 0, 500);

    // Our background test
    Plan background(normale, originPlan);

    Sphere sphere(300, originPlan);
    Sphere sphere2(100, Point3D(80, 400, 500));
    // Sphere myObjs[2] = {sphere, sphere2};

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
            // if (rayIntersectSphere(ray, sphere))
            // if (ray.get_Closest_Intersection(myObjs) != origin)
            if (ray.hit(sphere) != origin || ray.hit(sphere2) != origin)

            {
                int ir = 255.99;
                myImage << ir << " " << 0 << " " << 0 << " ";
                // std::cout << ray.getDirection().getX() << " " << ray.getDirection().getY() << " ";
                // std::cout << x << " " << y << " ";
            }
            else if (rayPlaneIntersection(ray, background))
            {
                // float r = float(x) / float(100);
                // float g = float(y) / float(100);
                // float b = 0.2;
                // int ir = int(255.99 * r);
                // int ig = int(255.99 * g);
                // int ib = int(255.99 * b);
                int ib = 255.99;
                myImage << 0 << " " << 0 << " " << ib << " ";
            }
        }
    }
    myImage.close();
    return 1;
}