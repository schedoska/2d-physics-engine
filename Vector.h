#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES

#include <math.h>

namespace dm2
{
	class Vector
	{
	public:
		float x, y;

		Vector(const float _x = 0, const float _y = 0);

		Vector operator+(const Vector& vector) const;
		Vector& operator+=(const Vector &vector);
		Vector operator-(const Vector& vector) const;
		Vector& operator-=(const Vector& vector);
		Vector operator*(const float scalar) const;

		Vector& normalize();
		Vector& rotate(const float angle);
		float length() const;
		float dotProduct(const Vector& vector) const;

		friend std::ostream& operator <<(std::ostream& out, const Vector& vector);
	};

	sf::Vector2f ConvertToSfVector(const dm2::Vector& vector);
	float RadToDeg(const float radians);
}

