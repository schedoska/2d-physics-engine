#include "Vector.h"
#include <cmath>

dm2::Vector::Vector(const float _x, const float _y)
	: x(_x), y(_y) {}

dm2::Vector dm2::Vector::operator+(const Vector& vector) const
{
	return Vector(x + vector.x, y + vector.y);
}

dm2::Vector& dm2::Vector::operator+=(const Vector& vector)
{
	x += vector.x;
	y += vector.y;
	return *this;
}

dm2::Vector dm2::Vector::operator-(const Vector& vector) const
{
	return Vector(x - vector.x, y - vector.y);
}

dm2::Vector& dm2::Vector::operator-=(const Vector& vector)
{
	x -= vector.x;
	y -= vector.y;
	return *this;
}

dm2::Vector dm2::Vector::operator*(const float scalar) const
{
	return Vector(x * scalar, y * scalar);
}

float dm2::Vector::length() const
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

float dm2::Vector::dotProduct(const Vector& vector) const
{
	return x * vector.x + y * vector.y;
}

dm2::Vector& dm2::Vector::normalize()
{
	float len = length();
	if (len == 0) return *this;
	x /= len;
	y /= len;
	return *this;
}

dm2::Vector& dm2::Vector::rotate(const float angle)
{
	x = x * cos(angle) - y * sin(angle);
	y = x * sin(angle) + y * cos(angle);
	return *this;
}

namespace dm2 
{
	std::ostream& operator<<(std::ostream& out, const dm2::Vector& vector)
	{
		return out << "[" << vector.x << "," << vector.y << "]";
	}

	sf::Vector2f ConvertToSfVector(const dm2::Vector& vector)
	{
		return sf::Vector2f(vector.x, vector.y);
	}

	float RadToDeg(const float radians)
	{
		return ((float)radians / M_PI) * 180.0;
	}
}
