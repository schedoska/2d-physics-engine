#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vector.h"
#include "World.h"
#include "Object.h"
#include <cstdlib>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "My window");
    window.setFramerateLimit(30);

    dm2::World world;
    sf::Clock clock;

    for (int h = 0; h < 2; h++)
    for (int i = 0; i < 10; i++)
    {
        dm2::Circle* obj = new dm2::Circle(dm2::Vector(i * 25 + 200, 100 + h * 25));
        obj->setRadius(10);
        obj->updateDrawableShape();
        world.addObject(obj);
        obj->setVelocity(dm2::Vector(-50 + rand() % 100, -50 + rand() % 100));
    }

    dm2::ConvexShape shape(dm2::Vector(70, 550));
    shape.addVertex(dm2::Vector(0, 0));
    shape.addVertex(dm2::Vector(50, 30));
    shape.addVertex(dm2::Vector(0, 30));
    shape.scaleShape(2);
    shape.changeOriginPoint(dm2::Vector(40, 60));
    shape.updateDrawableShape();
    //shape.setMovable(false);
    world.addObject(&shape);
    shape.setRotation(-0.3);
    shape.setVelocity(dm2::Vector(40, -30));
    shape.setAngularVelocity(0.3);

    dm2::ConvexShape shape2(dm2::Vector(70, 550));
    shape2.addVertex(dm2::Vector(0, 0));
    shape2.addVertex(dm2::Vector(80, 0));
    shape2.addVertex(dm2::Vector(80, 30));
    shape2.addVertex(dm2::Vector(0, 30));
    shape2.scaleShape(2);
    shape2.changeOriginPoint(dm2::Vector(40, 0));
    shape2.updateDrawableShape();
    shape2.setVelocity(dm2::Vector(30, 40));

    shape2.m_parent = &shape;
    shape2.m_constrained = true;

    //shape2.setMovable(false);


    world.addObject(&shape2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                /*
                if (event.key.code == sf::Keyboard::Up) obj2.setPosition(obj2.getPosition() + dm2::Vector(0, -9));
                if (event.key.code == sf::Keyboard::Down) obj2.setPosition(obj2.getPosition() + dm2::Vector(0, 9));
                if (event.key.code == sf::Keyboard::Right) obj2.setPosition(obj2.getPosition() + dm2::Vector(9, 0));
                if (event.key.code == sf::Keyboard::Left) obj2.setPosition(obj2.getPosition() + dm2::Vector(-9, 0));
                if (event.key.code == sf::Keyboard::R) obj2.setRotation(obj2.getRotation() + 0.2);
                */
            }
        }

        float dt = clock.restart().asSeconds();
        std::cout << 1.0 / dt << "\n";
        window.clear(sf::Color::White);

        world.updateAll(dt);
        world.drawAll(window);
        world.resolveCollisions(window);

        window.display();
    }

    return 0;
}