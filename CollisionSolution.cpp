#include "CollisionSolution.h"
#include <cmath>

void dm2::CollisionSolution::solveCollision(dm2::CollisionData& collisionData)
{
    dm2::Object* a = collisionData.objectA;
    dm2::Object* b = collisionData.objectB;

    if (a->m_constrained) a = a->m_parent;
    if (b->m_constrained) b = b->m_parent;

    dm2::Vector massToCpA = collisionData.cpA - a->getPosition();
    float r = massToCpA.length();
    //dm2::drawLine(collisionData.cpA, collisionData.cpA + massToCpA, window, sf::Color::Blue);

    dm2::Vector perpToMassA = dm2::Vector(-massToCpA.y, massToCpA.x);
    //dm2::drawLine(collision.cpA, collision.cpA + perpToMassA, window, sf::Color::Blue);

    massToCpA.normalize();
    perpToMassA.normalize();

    //--------------------------------------------------------------------------------------

    dm2::Vector massToCpB = collisionData.cpB - b->getPosition();
    float rB = massToCpB.length();
    //dm2::drawLine(collision.cpB, collision.cpB + massToCpB, window, sf::Color::Blue);

    dm2::Vector perpToMassB = dm2::Vector(-massToCpB.y, massToCpB.x);
    //dm2::drawLine(collision.cpB, collision.cpB + perpToMassB, window, sf::Color::Blue);

    massToCpB.normalize();
    perpToMassB.normalize();

    //--------------------------------------------------------------------------------------

    float collisonSpeedA = a->getVelocity().dotProduct((collisionData.cpA - collisionData.cpB).normalize());
    float collisionSpeedAngA = perpToMassA.dotProduct((collisionData.cpA - collisionData.cpB).normalize())
        * a->getAngularVelocity() * r;

    float collisonSpeedB = b->getVelocity().dotProduct((collisionData.cpB - collisionData.cpA).normalize());
    float collisionSpeedAngB = perpToMassB.dotProduct((collisionData.cpB - collisionData.cpA).normalize())
        * b->getAngularVelocity() * rB;

    float collisionSpeed = (collisonSpeedA + collisonSpeedB + collisionSpeedAngA + collisionSpeedAngB) / 1.5;

    float AtMassCenter = (collisionData.cpA - collisionData.cpB).normalize().dotProduct(massToCpA) * collisionSpeed;
    float AtRotation = (collisionData.cpA - collisionData.cpB).normalize().dotProduct(perpToMassA) * collisionSpeed;

    float BtMassCenter = (collisionData.cpB - collisionData.cpA).normalize().dotProduct(massToCpB) * collisionSpeed;
    float BtRotation = (collisionData.cpB - collisionData.cpA).normalize().dotProduct(perpToMassB) * collisionSpeed;

    //--------------------------------------------------------------------------------------

    // friction prototype

    dm2::Vector AfircVec = collisionData.cpA - collisionData.cpB;
    AfircVec = dm2::Vector(AfircVec.y, -AfircVec.x);
    //dm2::drawLine(collision.cpA, collision.cpA + AfircVec, window, sf::Color(255, 174, 0));

    dm2::Vector BfircVec = collisionData.cpB - collisionData.cpA;
    BfircVec = dm2::Vector(BfircVec.y, -BfircVec.x);
    //dm2::drawLine(collision.cpB, collision.cpB + BfircVec, window, sf::Color(255, 174, 0));

    //---------------------------------------------------------------------------------------

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || true)
    {
        if (b->isMovable())
        {
            b->setPosition(b->getPosition() + (collisionData.cpA - collisionData.cpB) * 0.5);
            b->setVelocity(b->getVelocity() - massToCpB * BtMassCenter);
            if(b->isRotable())
                b->setAngularVelocity(b->getAngularVelocity() - BtRotation / rB);
        }
        if (a->isMovable())
        {

            a->setPosition(a->getPosition() - (collisionData.cpA - collisionData.cpB) * 0.5);
            a->setVelocity(a->getVelocity() - massToCpA * AtMassCenter);
            if (a->isRotable())
                a->setAngularVelocity(a->getAngularVelocity() - AtRotation / r);
        }
    }

    //dm2::Vector currentVel = (*a)->getVelocity();
    //(*a)->setVelocity((collision.contactPointB - collision.contactPointA).normalize() * currentVel.length());
    //auto currentVel = b->getVelocity();
    //b->setVelocity((collision.contactPointA - collision.contactPointB).normalize() * (velocity.length() / 2.0));
}
