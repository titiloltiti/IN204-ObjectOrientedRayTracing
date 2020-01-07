#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <SFML/Graphics.hpp>
#include "shapes.hpp"
#include <cstdlib>
#include <math.h>

/*
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // Calculations
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
*/

bool rayPlaneIntersection(Ray r, Plan p)
{
    float x = abs(p.getNormale().point3D::dotProduct(r.getDirection()));
    if (x > 1e-6)
    {
        point3D y = p.getPoint() - r.getOrigin();
        float t = y.dotProduct(p.getNormale()) / x;
        return (t <= 0);
    }
    else
        return false;
}
int i = 0;
bool rayIntersectSphere(Ray r, Sphere s)
{
    float discr = (2 * (r.getOrigin() - s.getPosition()) * r.getDirection() * 2 * (r.getOrigin() - s.getPosition()) * r.getDirection()) - 4 * (r.getDirection() * r.getDirection()) * ((r.getOrigin() - s.getPosition()) * (r.getOrigin() - s.getPosition()) - s.getRay() * s.getRay());
    // discr = sqrt(discr);

    if (discr < 0)
    {
        // std::cout << "pas intersec" << std::endl;
        return false;
    }
    else
    {
        std::cout << ++i << std::endl;
        return true;
    }
}

int main()
{
    // screen 100(x)*100(y) at z = -50
    // centered so x in [-50;50], y in [-50,50]
    // camera at (0,0,0)
    // all rays start at (0,0,0), their direction is given by the pixel they compute on the screen ( so (x,y,-50) )
    // routine that create all rays

    point3D origin(0, 0, 0);

    point3D normale(0, 0, 1);
    point3D originPlan(0, 0, -100);
    // Our background test
    Plan background(normale, originPlan);

    Sphere sphere(50, originPlan);
    std::cout << sphere.getPosition().getZ() << " " << sphere.getRay() << std::endl;
    for (int x = -50; x <= 50; x++)
    {
        for (int y = -50; y <= 50; y++)
        {
            point3D dir(x, y, -50);
            Ray r(origin, dir);
            // if (!rayPlaneIntersection(r, background))
            //     std::cout << x << " " << y << std::endl;
            rayIntersectSphere(r, sphere);
        }
    }
}