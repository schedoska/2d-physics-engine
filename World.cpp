#include "World.h"
#include "Utils.h"
#include "CollisionCheck.h"
#include "CollisionSolution.h"
#include <iostream>
#include <limits>

dm2::World::World()
{
}

void dm2::World::addObject(dm2::ConvexShape* object)
{
    m_convexShapeList.push_back(object);
    m_objectList.push_back(object);
}

void dm2::World::addObject(dm2::Circle* object)
{
    m_circleList.push_back(object);
    m_objectList.push_back(object);
}

void dm2::World::updateAll(float dt)
{
    for (auto obj : m_objectList) obj->updateMotion(dt);
}

void dm2::World::drawAll(sf::RenderWindow& window)
{
    for (auto obj : m_objectList) obj->draw(window);
}

void dm2::World::resolveCollisions(sf::RenderWindow& window)
{
    for (auto obj : m_objectList)
    {
        dm2::Vector pos = obj->getPosition();
        if (pos.x < 15 || pos.x > 600)
        {
            obj->setVelocity(dm2::Vector(-obj->getVelocity().x, obj->getVelocity().y));
            if (pos.x < 15) obj->setPosition(dm2::Vector(16, obj->getPosition().y));
            else obj->setPosition(dm2::Vector(599, obj->getPosition().y));
        }
        if (pos.y < 15 || pos.y > 800)
        {
            obj->setVelocity(dm2::Vector(obj->getVelocity().x, -obj->getVelocity().y));
            if (pos.y < 15) obj->setPosition(dm2::Vector(obj->getPosition().x, 16));
            else obj->setPosition(dm2::Vector(obj->getPosition().x, 799));
        }

        /* draw mass centers */
        dm2::drawPoint(obj->getPosition(), window);
        /*speed vectors*/
        dm2::drawLine(obj->getPosition(), obj->getPosition() + obj->getVelocity(), window, sf::Color(129, 201, 185));
    }

    for (auto a_it = m_circleList.begin(); a_it != m_circleList.end(); ++a_it) {
        for (auto b_it = a_it + 1; b_it != m_circleList.end(); ++b_it) {
            dm2::Circle* a = *a_it;
            dm2::Circle* b = *b_it;

            dm2::CollisionData collisionData = CollisionCheck::check(a, b);
            if (collisionData.collides == false) continue;

            CollisionSolution::solveCollision(collisionData);
        }
    }
    for (auto a_it = m_convexShapeList.begin(); a_it != m_convexShapeList.end(); ++a_it) {
        for (auto b_it = a_it + 1; b_it != m_convexShapeList.end(); ++b_it) {

            dm2::ConvexShape* a = *a_it;
            dm2::ConvexShape* b = *b_it;

            dm2::CollisionData collision = CollisionCheck::check(a, b);
            if (collision.collides == false) continue;
            CollisionSolution::solveCollision(collision);            
        }
    }

    for (dm2::Circle* cirObj : m_circleList)
    {
        for (dm2::ConvexShape* convObj : m_convexShapeList)
        {
            dm2::CollisionData collisionData = CollisionCheck::check(convObj, cirObj);
            if (collisionData.collides == false) continue;
            CollisionSolution::solveCollision(collisionData);
        }
    }
}

