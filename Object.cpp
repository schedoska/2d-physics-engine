#include "Object.h"

dm2::Object::Object(const dm2::Vector& position)
{
	m_position = position;
	m_mass = 1;
	m_rotation = 0;
	m_angularVelocity = 0;
	m_torque = 0;
	m_rotable = true;
	m_movable = true;
}

void dm2::Object::setPosition(const dm2::Vector& position)
{
	m_position = position;
}

void dm2::Object::setVelocity(const dm2::Vector& velocity)
{
	m_velocity = velocity;
}

void dm2::Object::setForce(const dm2::Vector& force)
{
	m_force = force;
}

void dm2::Object::setMass(const float mass)
{
	m_mass = mass;
}

void dm2::Object::setRotation(const float angle)
{
	m_rotation = angle;
}

void dm2::Object::setAngularVelocity(const float angluarVelocity)
{
	m_angularVelocity = angluarVelocity;
}

void dm2::Object::setTorque(const float torque)
{
	m_torque = torque;
}

void dm2::Object::move(const dm2::Vector& vector)
{
	m_position += vector;
}

void dm2::Object::setMovable(const bool movable)
{
	m_movable = movable;
}

void dm2::Object::setRotable(const bool rotable)
{
	m_rotable = rotable;
}

dm2::Vector dm2::Object::getPosition() const
{
	return m_position;
}

dm2::Vector dm2::Object::getVelocity() const
{
	return m_velocity;
}

dm2::Vector dm2::Object::getForce() const
{
	return m_force;
}

float dm2::Object::getMass() const
{
	return m_mass;
}

float dm2::Object::getRotation() const
{
	return m_rotation;
}

float dm2::Object::getAngularVelocity() const
{
	return m_angularVelocity;
}

float dm2::Object::getTorque() const
{
	return m_torque;
}

bool dm2::Object::isMovable() const
{
	return m_movable;
}

bool dm2::Object::isRotable() const
{
	return m_rotable;
}

void dm2::Object::updateMotion(const float dt)
{
	if (m_constrained)
	{
		m_position = m_parent->getPosition() + dm2::Vector(0, 10);
		m_rotation = m_parent->getRotation();
		return;
	}

	if (!isMovable()) return;
	m_velocity += ((m_force * (1.0 / m_mass)) * dt);
	m_position += (m_velocity * dt);
	if (!isRotable()) return;
	m_rotation += (m_angularVelocity * dt);
}

dm2::Vector dm2::Object::localToWorld(const dm2::Vector& vector) const
{
	float x = cos(m_rotation) * vector.x - sin(m_rotation) * vector.y + m_position.x;
	float y = sin(m_rotation) * vector.x + cos(m_rotation) * vector.y + m_position.y;
	return dm2::Vector(x, y);
}

//	--------------------------------------------------------------------------------------

dm2::ConvexShape::ConvexShape(const dm2::Vector& position)
	: dm2::Object(position) {}

void dm2::ConvexShape::addVertex(const dm2::Vector& vertex)
{
	m_verticesList.push_back(vertex);
}

void dm2::ConvexShape::draw(sf::RenderWindow& window)
{
	m_drawable.setRotation(dm2::RadToDeg(m_rotation));
	m_drawable.setPosition(dm2::ConvertToSfVector(m_position));
	window.draw(m_drawable);
}

void dm2::ConvexShape::updateDrawableShape()
{
	m_drawable.setFillColor(sf::Color::Transparent);
	m_drawable.setOutlineThickness(2);
	m_drawable.setOutlineColor(sf::Color::Red);
	m_drawable.setPointCount(m_verticesList.size());

	for (int i = 0; i < m_verticesList.size(); i++)
	{
		m_drawable.setPoint(i, dm2::ConvertToSfVector(m_verticesList[i]));
	}
}

std::vector<dm2::Vector>& dm2::ConvexShape::getVerticesList()
{
	return m_verticesList;
}

void dm2::ConvexShape::scaleShape(const float scaleFactor)
{
	for (int i = 0; i < m_verticesList.size(); i++)
	{
		m_verticesList[i] = m_verticesList[i] * scaleFactor;
	}
}

void dm2::ConvexShape::changeOriginPoint(const dm2::Vector& vector)
{
	for (dm2::Vector& vec : m_verticesList)
		vec = vec - vector;
	updateDrawableShape();
}

dm2::Circle::Circle(const dm2::Vector& position)
	: dm2::Object(position)
{
	m_radius = 0;
}

void dm2::Circle::draw(sf::RenderWindow& window)
{
	m_drawable.setRotation(dm2::RadToDeg(m_rotation));
	m_drawable.setPosition(dm2::ConvertToSfVector(m_position));
	window.draw(m_drawable);
}

void dm2::Circle::updateDrawableShape()
{
	m_drawable.setFillColor(sf::Color::Transparent);
	m_drawable.setOutlineThickness(2);
	m_drawable.setOutlineColor(sf::Color::Red);
	m_drawable.setRadius(getRadius());
	m_drawable.setOrigin(sf::Vector2f(getRadius(), getRadius()));
}

void dm2::Circle::setRadius(const float radius)
{
	m_radius = radius;
}

float dm2::Circle::getRadius() const
{
	return m_radius;
}