#include "CollisionCheck.h"

dm2::AxisProjectionData::AxisProjectionData()
    : isOverlaping(true) {}

dm2::CollisionData dm2::CollisionCheck::check(dm2::ConvexShape* a, dm2::ConvexShape* b)
{
    if (a->m_parent == b || b->m_parent == a) return CollisionData(false, a, b);

    std::vector<dm2::Vector>& AList = a->getVerticesList();
    std::vector<dm2::Vector>& BList = b->getVerticesList();
    unsigned ACount = AList.size();
    unsigned BCount = BList.size();

    float minOverlap = std::numeric_limits<float>::max();
    dm2::Vector cpA, cpB;
    dm2::Vector collisionNormal;

    for (int i = 0; i < ACount; i++)
    {
        dm2::Vector edge = a->localToWorld(AList[(i + 1) % ACount]) - a->localToWorld(AList[i]);
        dm2::Vector axis = dm2::Vector(edge.y, -edge.x).normalize();
        dm2::AxisProjectionData axisProjectionData = projectOnAxis(a, b, axis);
        if (!axisProjectionData.isOverlaping)
            return CollisionData(false, a, b);

        if (axisProjectionData.overlapVal < minOverlap)
        {
            minOverlap = axisProjectionData.overlapVal;
            collisionNormal = axisProjectionData.collisionNormal;
            cpB = axisProjectionData.closestSecPoint;
            cpA = cpB + collisionNormal * minOverlap;
        }
    }
    for (int i = 0; i < BCount; i++)
    {
        dm2::Vector edge = b->localToWorld(BList[(i + 1) % BCount]) - b->localToWorld(BList[i]);
        dm2::Vector axis = dm2::Vector(edge.y, -edge.x).normalize();
        dm2::AxisProjectionData axisProjectionData = projectOnAxis(b, a, axis);
        if (!axisProjectionData.isOverlaping)
            return CollisionData(false, a, b);

        if (axisProjectionData.overlapVal < minOverlap)
        {
            minOverlap = axisProjectionData.overlapVal;
            collisionNormal = axisProjectionData.collisionNormal;
            cpA = axisProjectionData.closestSecPoint;
            cpB = cpA + collisionNormal * minOverlap;
        }
    }

    //dm2::drawPoint(cpA, window);
    //dm2::drawPoint(cpB, window);
    //dm2::drawLine(cpA, cpB, window, sf::Color::Green);
    return CollisionData(true, a, b, cpA, cpB);
}

dm2::CollisionData dm2::CollisionCheck::check(dm2::ConvexShape* a, dm2::Circle* b)
{
    if (a->m_parent == b || b->m_parent == a) return CollisionData(false, a, b);

    std::vector<dm2::Vector>& AList = a->getVerticesList();
    unsigned ACount = AList.size();

    float minOverlap = std::numeric_limits<float>::max();
    dm2::Vector cpA, cpB;
    dm2::Vector collisionNormal;

    for (int i = 0; i < ACount; i++)
    {
        dm2::Vector edge = a->localToWorld(AList[(i + 1) % ACount]) - a->localToWorld(AList[i]);
        dm2::Vector axis = dm2::Vector(edge.y, -edge.x).normalize();
        dm2::AxisProjectionData axisProjectionData = projectOnAxis(a, b, axis);
        if (!axisProjectionData.isOverlaping)
            return CollisionData(false, a, b);

        if (axisProjectionData.overlapVal < minOverlap)
        {
            minOverlap = axisProjectionData.overlapVal;
            collisionNormal = axisProjectionData.collisionNormal;
            cpB = axisProjectionData.closestSecPoint;
            cpA = cpB + collisionNormal * minOverlap;
        }
    }

    return CollisionData(true, a, b, cpA, cpB);
}

dm2::CollisionData dm2::CollisionCheck::check(dm2::Circle* a, dm2::Circle* b)
{
    if (a->m_parent == b || b->m_parent == a) return CollisionData(false, a, b);

    dm2::Vector ab = a->getPosition() - b->getPosition();
    if (ab.length() > a->getRadius() + b->getRadius()) 
        return dm2::CollisionData(false, a, b);

    ab.normalize();
    dm2::Vector cpB = ab *  b->getRadius() + b->getPosition();
    dm2::Vector cpA = ab * -a->getRadius() + a->getPosition();

    return CollisionData(true, a, b, cpA, cpB);
}

dm2::AxisProjectionData dm2::CollisionCheck::projectOnAxis(dm2::ConvexShape* ref, dm2::ConvexShape* sec, const dm2::Vector& axis)
{
    dm2::AxisProjectionData projectionData;
    projectionData.collisionNormal = axis;

    float maxRefVal = -std::numeric_limits<float>::max();  //usun
    float minRefVal = std::numeric_limits<float>::max();   //usun
    for (dm2::Vector v : ref->getVerticesList())
    {
        float val = axis.dotProduct(ref->localToWorld(v));
        maxRefVal = std::max(val, maxRefVal);
        minRefVal = std::min(val, minRefVal);
    }
    float maxSecVal = -std::numeric_limits<float>::max();  //usun
    float minSecVal = std::numeric_limits<float>::max();   //usun
    dm2::Vector maxSecVector, minSecVector;
    for (dm2::Vector v : sec->getVerticesList())
    {
        dm2::Vector vltw = sec->localToWorld(v);
        float val = axis.dotProduct(vltw);
        if (val > maxSecVal)
        {
            maxSecVal = val;
            maxSecVector = vltw;
        }
        if (val < minSecVal)
        {
            minSecVal = val;
            minSecVector = vltw;
        }
    }
    /* Check if Collision occured */
    if (minSecVal > maxRefVal ||
        maxSecVal < minRefVal)
    {
        projectionData.isOverlaping = false;
        return projectionData;
    }
    /* Calculate overlapping value and Determine closest secondary Point to the referenc object */
    if (minSecVal > minRefVal)
    {
        projectionData.overlapVal = std::abs(maxRefVal - minSecVal);
        projectionData.closestSecPoint = minSecVector;
    }
    else
    {
        projectionData.overlapVal = std::abs(maxSecVal - minRefVal);
        projectionData.closestSecPoint = maxSecVector;
        projectionData.collisionNormal = projectionData.collisionNormal * (-1);
    }

    return projectionData;
}

dm2::AxisProjectionData dm2::CollisionCheck::projectOnAxis(dm2::ConvexShape* ref, dm2::Circle* sec, const dm2::Vector& axis)
{
    dm2::AxisProjectionData projectionData;
    projectionData.collisionNormal = axis;

    float maxRefVal = -std::numeric_limits<float>::max();  //usun
    float minRefVal = std::numeric_limits<float>::max();   //usun
    for (dm2::Vector v : ref->getVerticesList())
    {
        float val = axis.dotProduct(ref->localToWorld(v));
        maxRefVal = std::max(val, maxRefVal);
        minRefVal = std::min(val, minRefVal);
    }

    float maxSecVal, minSecVal;   
    dm2::Vector maxSecVector, minSecVector;
    dm2::Vector sec1 = sec->getPosition() + axis * sec->getRadius();
    dm2::Vector sec2 = sec->getPosition() - axis * sec->getRadius();
    float val1 = axis.dotProduct(sec1);
    float val2 = axis.dotProduct(sec2);

    if (val1 > val2)
    {
        maxSecVal = val1;
        minSecVal = val2;
        maxSecVector = sec1;
        minSecVector = sec2;
    }
    else
    {
        maxSecVal = val2;
        minSecVal = val1;
        maxSecVector = sec2;
        minSecVector = sec1;
    }

    /* Check if Collision occured */
    if (minSecVal > maxRefVal ||
        maxSecVal < minRefVal)
    {
        projectionData.isOverlaping = false;
        return projectionData;
    }
    /* Calculate overlapping value and Determine closest secondary Point to the referenc object */
    if (minSecVal > minRefVal)
    {
        projectionData.overlapVal = std::abs(maxRefVal - minSecVal);
        projectionData.closestSecPoint = minSecVector;
    }
    else
    {
        projectionData.overlapVal = std::abs(maxSecVal - minRefVal);
        projectionData.closestSecPoint = maxSecVector;
        projectionData.collisionNormal = projectionData.collisionNormal * (-1);
    }

    return projectionData;
}