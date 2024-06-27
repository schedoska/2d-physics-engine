#include "Utils.h"

#define _USE_MATH_DEFINES
#include <math.h>



namespace dm2
{
    sf::Vector2f dm2::ConvertToVector2F(const dm2::Vector& vector)
    {
        return sf::Vector2f(vector.x, vector.y);
    }

    float RadToDegrees(const float radians)
    {
        return (radians * 180.0) / M_PI;
    }

    void drawLine(dm2::Vector start, dm2::Vector end, sf::RenderWindow& window, sf::Color color)
    {
        static sf::RectangleShape line;
        line.setPosition(dm2::ConvertToSfVector(start));
        dm2::Vector delta = start - end;

        line.setSize(sf::Vector2f(delta.length(), 2));
        float angle = dm2::RadToDeg(atan(delta.y / delta.x));
        if (end.x <= start.x) angle -= 180;
        line.setRotation(angle);

        line.setFillColor(color);
        window.draw(line);
    }

    void drawPoint(dm2::Vector point, sf::RenderWindow& window)
    {
        static sf::CircleShape pointDrawable;
        pointDrawable.setOrigin(2, 2);
        pointDrawable.setPosition(dm2::ConvertToSfVector(point));
        pointDrawable.setRadius(4);
        pointDrawable.setFillColor(sf::Color::Black);

        window.draw(pointDrawable);
    }
}
